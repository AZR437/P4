#pragma once
#include <nlohmann/json.hpp> 
#include <cstdint>
#include "SceneData.pb.h"
#include "SceneData.grpc.pb.h"
#include "IETThread.h"
#include "ThreadPool.h"
class SceneServer;
class MeshStreamImpl final :public MeshStream::Service
{
public:
	explicit MeshStreamImpl(SceneServer* server)
		: server_(server) {}
	grpc::Status StreamMesh(grpc::ServerContext* context, const MeshRequest* request, grpc::ServerWriter<MeshReply>* writer) override;
private:
	SceneServer* server_;
};

class SceneLoadImpl final :public SceneLoad::Service
{
private:
	typedef nlohmann::json json;
	struct Position {
		float x, y, z;
	};
	struct Scale
	{
		float x, y, z;
	};
public:
	explicit SceneLoadImpl(SceneServer* server)
		: server_(server) {}
	bool retryLoadSceneFromFile(const std::string& scene_id, std::vector<std::string>& meshIDs, std::vector<Position>& positions, std::vector<Scale>& scales, int retries = 3);
	bool loadSceneFromFile(const std::string& scene_id, std::vector<std::string>& meshIDs, std::vector<Position>& positions, std::vector<Scale>& scales);
	grpc::Status LoadScene(grpc::ServerContext* context, const SceneRequest* request, SceneReply* reply) override;
private:
	SceneServer* server_;
};
class SceneServer final : public IETThread
{
public:
	SceneServer();

	void run() override;

	void RunServer(uint16_t port);
private:
	SceneLoadImpl scene_load_impl;
	MeshStreamImpl mesh_service;
};
