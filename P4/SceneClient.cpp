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

    context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds(10));

    std::unique_ptr<grpc::ClientReader<MeshReply>> reader(
        stub_->StreamMesh(&context, request));

    std::string objData;
    MeshReply meshReply;
    int retries = 3;
    bool success = false;

    while (retries > 0 && !success)
    {
        while (reader->Read(&meshReply))
        {
            objData.append(meshReply.data());
        }
        if (reader->Finish().ok())
        {
            success = true;
            MeshManager::getInstance()->loadMeshDataAsync(objName, meshReply.data(), NULL, true);
            return "Loading of OBJ Data Done";
        }
        else
        {
            // Retry in case of failure
            std::cerr << "Failed to stream mesh data, retrying..." << std::endl;
            --retries;
            std::cerr << retries<< std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5)); // Exponential backoff can be added here
        }
    }
    return "Failed to stream mesh data after retries.";
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

    //context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds(10));

    Status status = this->stub_->LoadScene(&context, request, &reply);
    if (status.ok()) {
        std::cout << "Loaded Scene: " << sceneName << std::endl;
        std::cout << "Meshes in scene:" << std::endl;
        for (int i = 0; i < reply.meshids_size(); ++i) {
            std::string mesh_id = reply.meshids(i);
            std::cout << "Mesh ID: " << mesh_id << " at Position: "
                << "x: " << reply.positions(i).x() << ", "
                << "y: " << reply.positions(i).y() << ", "
                << "z: " << reply.positions(i).z() << " with a Scale: "
                << "x: " << reply.scales(i).x() << ", "
                << "y: " << reply.scales(i).y() << ", "
                << "z: " << reply.scales(i).z() << std::endl;
               

            int retries = 3;
            bool success = false;
            while (retries > 0 && !success)
            {
                StreamMeshClient streamMeshClient(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
                std::string reply = streamMeshClient.StreamMesh(mesh_id);
                if (reply == "Loading of OBJ Data Done") {
                    std::cout << "Mesh received: " << mesh_id << std::endl;
                    success = true;
                }
                else {
                    std::cerr << "Failed to stream mesh " << mesh_id << ", retrying..." << std::endl;
                    --retries;
                    std::this_thread::sleep_for(std::chrono::seconds(2)); // Exponential backoff can be added here
                }
            }

            if (!success) {
                std::cerr << "Failed to load mesh: " << mesh_id << std::endl;
            }
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