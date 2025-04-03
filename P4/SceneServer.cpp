#include "SceneServer.h"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include "MeshLoader.h"
#include <fstream>
#include "csignal"
std::atomic<bool> server_running(true);

void signalHandler(int signum) {
	std::cout << "Interrupt signal (" << signum << ") received. Shutting down gracefully..." << std::endl;
	server_running = false;
}

grpc::Status MeshStreamImpl::StreamMesh(grpc::ServerContext* context, const MeshRequest* request, grpc::ServerWriter<MeshReply>* writer)
{
	std::string path = "C:/Users/theas/Documents/Acads/P4/P4/Assets/" + request->file_name() + ".obj";
	std::ifstream file(path, std::ios::binary);
	if (!file.is_open()) {
		return grpc::Status(grpc::StatusCode::NOT_FOUND, "File not found");
	}
	const size_t chunkSize = 1024;
	char buffer[chunkSize];

	try {
		while (file.read(buffer, chunkSize))
		{
			MeshReply meshReply;
			meshReply.set_data(buffer, file.gcount());
			if (!writer->Write(meshReply))
			{
				std::cerr << "Error: Failed to send mesh data to client" << std::endl;
				return grpc::Status(grpc::StatusCode::INTERNAL, "Failed to stream data");
			}
		}
		if (file.gcount() > 0) {
			MeshReply meshReply;
			meshReply.set_data(buffer, file.gcount()); // Set the remaining data
			if (!writer->Write(meshReply)) {
				std::cerr << "Error: Failed to send last chunk of mesh data to client" << std::endl;
				return grpc::Status(grpc::StatusCode::INTERNAL, "Failed to stream remaining data");
			}
		}
	}


	catch (const std::exception& e) {
		std::cerr << "Exception while streaming mesh: " << e.what() << std::endl;
		return grpc::Status(grpc::StatusCode::INTERNAL, "Failed to stream mesh");
	}
   
    return grpc::Status::OK;
}
bool SceneLoadImpl::retryLoadSceneFromFile(const std::string& scene_id, std::vector<std::string>& meshIDs, std::vector<Position>& positions, std::vector<Scale>& scales, int retries)
{
	for (int i = 0; i < retries; ++i) {
		if (loadSceneFromFile(scene_id, meshIDs, positions, scales)) {
			return true;
		}
		std::cerr << "Retrying to load scene file, attempt " << i + 1 << " of " << retries << "...\n";
		this->server_->sleep(1000);
	}
	return false;
}
bool SceneLoadImpl::loadSceneFromFile(const std::string& scene_id, std::vector<std::string>& meshIDs, std::vector<Position>& positions, std::vector<Scale>& scales)
{
	std::string path = "C:/Users/theas/Documents/Acads/P4/P4/Scenes/" + scene_id + ".json";
	std::ifstream file(path, std::ios::in);
	if (!file.is_open()) {
		std::cerr << "Failed to open scene file: " << path << std::endl;
		return false;
	}

	try {
		json j;
		file >> j;

		meshIDs = j["meshIDs"].get<std::vector<std::string>>();

		positions.clear();
		scales.clear();
		for (const auto& pos : j["positions"]) {
			positions.push_back({ pos["x"], pos["y"], pos["z"] });
		}
		for (const auto& scale : j["scales"]) {
			scales.push_back({ scale["x"], scale["y"], scale["z"] });
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Exception while loading scene file: " << e.what() << std::endl;
		return false;
	}
	return true;
}
grpc::Status SceneLoadImpl::LoadScene(grpc::ServerContext* context, const SceneRequest* request, SceneReply* reply)
{
	std::vector<std::string> meshIDs;
	std::vector<Position> positions;
	std::vector<Scale> scales;

	if (!retryLoadSceneFromFile(request->sceneid(), meshIDs, positions, scales)) {
		return grpc::Status(grpc::StatusCode::NOT_FOUND, "Scene not found");
	}

	for (const auto& meshID : meshIDs) {
		reply->add_meshids(meshID);
	}

	for (const auto& pos : positions) {
		Float3* position = reply->add_positions();
		position->set_x(pos.x);
		position->set_y(pos.y);
		position->set_z(pos.z);
	}
	for (const auto& sc : scales) {
		Float3* scale = reply->add_scales();
		scale->set_x(sc.x);
		scale->set_y(sc.y);
		scale->set_z(sc.z);
	}

	return grpc::Status::OK;
}

SceneServer::SceneServer() :scene_load_impl(this), mesh_service(this)
{
}
void SceneServer::run()
{
	RunServer(50051);
}

void SceneServer::RunServer(uint16_t port)
{
	std::string serverAddress = absl::StrFormat("localhost:%d", port);
	
	

	grpc::EnableDefaultHealthCheckService(true);
	grpc::reflection::InitProtoReflectionServerBuilderPlugin();

	grpc::ServerBuilder builder;

	builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());

	builder.RegisterService(&mesh_service);
	builder.RegisterService(&scene_load_impl);
	// Finally assemble the server.
	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << serverAddress << std::endl;
	signal(SIGINT, signalHandler);

	while (server_running) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	std::cout << "Shutting down the server..." << std::endl;
	server->Shutdown();
	server->Wait();
	std::cout << "Server has been shut down." << std::endl;
}