#include "SceneClient.h"
#include <grpcpp/create_channel.h>

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

    MeshReply meshReply;
    while (reader->Read(&meshReply)) {
        // Process vertices
        for (const auto& vertex : meshReply.vertices()) {
            std::cout << "Vertex: (" << vertex.x() << ", " << vertex.y() << ", " << vertex.z() << ")\n";
        }

        // Process indices
        for (int index : meshReply.indices()) {
            std::cout << "Index: " << index << "\n";
        }
    }
    return  "Stream Done";
}

void SceneClient::runClient()
{
    SceneClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    std::string obj("Bunny");
    std::string reply = client.StreamMesh(obj + ".obj");
    std::cout << "Mesh received: " << reply << std::endl;

}
