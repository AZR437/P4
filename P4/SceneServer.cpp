#include "SceneServer.h"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include "MeshLoader.h"
#include <fstream>
SceneServer::SceneServer()
{
	this->threadPool = new ThreadPool("ThreadPool", 8);
}
void SceneServer::run()
{
	RunServer(50051);
}

grpc::Status SceneServer::StreamMesh(grpc::ServerContext* context, const MeshRequest* request, grpc::ServerWriter<MeshReply>* writer)
{
	std::string path = "C:/Users/theas/Documents/Acads/P4/P4/Assets/";
	std::ifstream file(path + request->file_name(), std::ios::in);
	if (!file.is_open()) {
		return grpc::Status(grpc::StatusCode::NOT_FOUND, "File not found");
	}

    MeshReply meshReply;
    std::string line;

    // Temporary vectors for storing vertices and indices
    std::vector<Float3> vertices;
    std::vector<int32_t> indices;

    while (std::getline(file, line)) {
        if (line.substr(0, 2) == "v ") { // Vertex line
            Float3 vertex;
            std::istringstream s(line.substr(2)); // Skip the "v " prefix
            float x, y, z;
            s >> x >> y>> z;
            vertex.set_x(x);
            vertex.set_y(y);
            vertex.set_z(z);
            vertices.push_back(vertex);
        }
        else if (line.substr(0, 2) == "f ") { // Face line
            std::istringstream s(line.substr(2)); // Skip the "f " prefix
            int32_t idx;
            while (s >> idx) {
                indices.push_back(idx - 1); // OBJ indices are 1-based, so subtract 1
            }
        }
    }

    // Add vertices and indices to the message
    for (const auto& vertex : vertices) {
        meshReply.add_vertices()->set_x(vertex.x());
        meshReply.add_vertices()->set_y(vertex.y());
        meshReply.add_vertices()->set_z(vertex.z());
    }
    for (int32_t index : indices) {
        meshReply.add_indices(index);
    }
    std::cout <<"vertices: " << meshReply.vertices().size() << std::endl;
    std::cout << "indices: "<< meshReply.indices().size()<<std::endl;
    // Send the data in chunks
    if (!writer->Write(meshReply)) {
        return grpc::Status(grpc::StatusCode::UNKNOWN, "Error while streaming");
    }

    return grpc::Status::OK;
}


void SceneServer::RunServer(uint16_t port)
{
	std::string serverAddress = absl::StrFormat("localhost:%d", port);
	SceneServer service;

	grpc::EnableDefaultHealthCheckService(true);
	grpc::reflection::InitProtoReflectionServerBuilderPlugin();
	grpc::ServerBuilder builder;
	// Listen on the given address without any authentication mechanism.
	builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
	// Register "service" as the instance through which we'll communicate with
	// clients. In this case it corresponds to an *synchronous* service.
	builder.RegisterService(&service);
	// Finally assemble the server.
	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << serverAddress << std::endl;
	// Wait for the server to shutdown. Note that some other thread must be
	// responsible for shutting down the server for this call to ever return.
	server->Wait();
}
