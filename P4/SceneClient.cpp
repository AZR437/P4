#include "SceneClient.h"
#include <grpcpp/create_channel.h>
#include "MeshManager.h"
#include "tiny_obj_loader.h"
#include "SceneObjTransforms.h"
#include "SceneManager.h"
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

    std::string objData;
    MeshReply meshReply;
    int retries = 3;
    bool success = false;

    while (retries > 0 && !success)
    {

        std::unique_ptr<grpc::ClientReader<MeshReply>> reader(
            stub_->StreamMesh(&context, request));

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
    std::cout << "enter" << std::endl;
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
        int meshLoaded = 0;
        int meshNo = reply.meshids_size();
        for (int i = 0; i < reply.meshids_size(); ++i) {
            std::string meshID = reply.meshids(i);
            SceneObjTransforms objTransforms;
            objTransforms.setPos(reply.positions(i).x(), reply.positions(i).y(), reply.positions(i).z());
            objTransforms.setScale(reply.scales(i).x(), reply.scales(i).y(), reply.scales(i).z());
            SceneManager::getInstance()->cacheSceneTransforms(sceneName, meshID, objTransforms);
           
               

            int retries = 3;
            bool success = false;
            while (retries > 0 && !success)
            {
                StreamMeshClient streamMeshClient(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
                std::string reply = streamMeshClient.StreamMesh(meshID);
                if (reply == "Loading of OBJ Data Done") {
                    std::cout << "Mesh received: " << meshID << std::endl;
                    meshLoaded++;
                    std::cout << meshLoaded << "/" << meshNo << " meshes loaded from scene" << std::endl;
                    success = true;
                }
                else {
                    std::cerr << "Failed to stream mesh " << meshID << ", retrying..." << std::endl;
                    --retries;
                    std::this_thread::sleep_for(std::chrono::seconds(2)); // Exponential backoff can be added here
                }
            }

            if (!success) {
                std::cerr << "Failed to load mesh: " << meshID << std::endl;
            }
        }

        return "Scene Loading done";  
    }
    else
    {
        return "Scene Loading failed";
    }
}
SceneClient::SceneClient(std::shared_ptr<grpc::ChannelInterface> channel):client(channel)
{

}
std::string SceneClient::LoadScene(std::string sceneName)
{
    return this->client.LoadScene(sceneName);
}


