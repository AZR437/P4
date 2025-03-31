#include "SceneClient.h"
#include <grpcpp/create_channel.h>
#include "MeshManager.h"
#include "tiny_obj_loader.h"

SceneClient::SceneClient(std::shared_ptr<grpc::ChannelInterface> channel)
{
	this->stub_ = MeshStream::NewStub(channel);
}

std::string SceneClient::StreamMesh(std::string objName)
{
    MeshRequest request;
    request.set_file_name(objName);
    grpc::ClientContext context;
    std::unique_ptr<grpc::ClientReader<MeshReply>> reader(
        stub_->StreamMesh(&context, request));

    std::string objData;
    MeshReply meshReply;
    while (reader->Read(&meshReply))
    {
        objData.append(meshReply.data());
    }

    // Now that we've received all chunks, load it with tinyobjloader
    std::istringstream objStream(objData);
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warning, error;

    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &materials,
        &warning,
        &error,
        &objStream
    );
    if (!success) 
    {
        return "Failed to load OBJ data: " + error;;
    }

    return "Successfully loaded the OBJ data!";
}

void SceneClient::runClient()
{
    SceneClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    std::string obj("Bunny");
    std::string reply = client.StreamMesh(obj + ".obj");
    std::cout << "Mesh received: " << reply << std::endl;

}
