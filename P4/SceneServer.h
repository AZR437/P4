#pragma once
#include <nlohmann/json.hpp> 
#include <cstdint>
#include "SceneData.pb.h"
#include "SceneData.grpc.pb.h"
#include "IETThread.h"
#include "ThreadPool.h"

class MeshStreamImpl final :public MeshStream::Service
{
	grpc::Status StreamMesh(grpc::ServerContext* context, const MeshRequest* request, grpc::ServerWriter<MeshReply>* writer) override;
};
class SceneLoadImpl final :public SceneLoad::Service
{
private:
	typedef nlohmann::json json;
	struct Position {
		float x, y, z;
	};
public:
	bool loadSceneFromFile(const std::string& scene_id, std::vector<std::string>& meshIDs, std::vector<Position>& positions);
	grpc::Status LoadScene(grpc::ServerContext* context, const SceneRequest* request, SceneReply* reply) override;
};
class SceneServer final: public IETThread
{
public:
	SceneServer();

	void run() override;
	
	static void RunServer(uint16_t port);
};

