#include "SceneClient.h"
#include <grpcpp/create_channel.h>
#include "MeshManager.h"
#include "tiny_obj_loader.h"

StreamMeshClient::StreamMeshClient(std::shared_ptr<grpc::ChannelInterface> channel)
{
	this->stub_ = MeshStream::NewStub(channel);
}

std::string StreamMeshClient::StreamMesh(std::string objName)
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
    MeshManager::getInstance()->loadMeshDataAsync(objName, meshReply.data());

    return "Loading of OBJ Data Done";
}

void SceneClient::runClient()
{
    StreamMeshClient streamMeshClient(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    std::string obj("Bunny");
    std::string reply = streamMeshClient.StreamMesh(obj + ".obj");
    std::cout << "Mesh received: " << reply << std::endl;

}
