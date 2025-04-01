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
}
void SceneServer::run()
{
	RunServer(50051);
}

grpc::Status MeshStreamImpl::StreamMesh(grpc::ServerContext* context, const MeshRequest* request, grpc::ServerWriter<MeshReply>* writer)
{
	std::string path = "C:/Users/theas/Documents/Acads/P4/P4/Assets/";
	std::ifstream file(path + request->file_name(), std::ios::in);
	if (!file.is_open()) {
		return grpc::Status(grpc::StatusCode::NOT_FOUND, "File not found");
	}

	const size_t chunkSize = 1024;
	char buffer[chunkSize];

	while (!file.read(buffer, chunkSize))
	{
		MeshReply meshReply;
		meshReply.set_data(buffer,file.gcount());
		writer->Write(meshReply);
	}
   
   
    return grpc::Status::OK;
}
grpc::Status SceneLoadImpl::LoadScene(grpc::ServerContext* context, const SceneRequest* request, SceneReply* reply)
{
	return grpc::Status::OK;
}
void SceneServer::RunServer(uint16_t port)
{
	std::string serverAddress = absl::StrFormat("localhost:%d", port);
	MeshStreamImpl service;

	grpc::EnableDefaultHealthCheckService(true);
	grpc::reflection::InitProtoReflectionServerBuilderPlugin();
	grpc::ServerBuilder builder;

	builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());

	builder.RegisterService(&service);
	// Finally assemble the server.
	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << serverAddress << std::endl;

	server->Wait();
}