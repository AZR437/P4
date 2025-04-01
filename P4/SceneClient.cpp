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



SceneLoadClient::SceneLoadClient(std::shared_ptr<grpc::ChannelInterface> channel)
{
    this->stub_ = SceneLoad::NewStub(channel);
}

std::string SceneLoadClient::LoadScene(std::string sceneName)
{
    SceneRequest request;
    request.set_sceneid(sceneName);

    SceneReply reply;
    ClientContext context;

    Status status = this->stub_->LoadScene(&context, request, &reply);
    if (status.ok()) {
        std::cout << "Loaded Scene: " << sceneName << std::endl;
        std::cout << "Meshes in scene:" << std::endl;
        for (int i = 0; i < reply.meshids_size(); ++i) {
            std::string mesh_id = reply.meshids(i);
            std::cout << "Mesh ID: " << mesh_id << " at Position: "
                << "x: " << reply.positions(i).x() << ", "
                << "y: " << reply.positions(i).y() << ", "
                << "z: " << reply.positions(i).z() << std::endl;
            StreamMeshClient streamMeshClient(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
            std::string reply = streamMeshClient.StreamMesh(mesh_id);
            std::cout << "Mesh received: " << reply << std::endl;
        }

        return "Scene Loading done";  
    }
    else
    {
        return "Scene Loading failed";
    }
}
void SceneClient::runClient()
{
   SceneLoadClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
   client.LoadScene("Scene_1");

}