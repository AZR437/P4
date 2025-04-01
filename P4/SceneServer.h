#pragma once
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
	grpc::Status LoadScene(grpc::ServerContext* context, const SceneRequest* request, SceneReply* reply) override;
};
class SceneServer final: public IETThread
{
public:
	SceneServer();

	void run() override;
	
	static void RunServer(uint16_t port);
};

