#pragma once
#include <cstdint>
#include "SceneData.pb.h"
#include "SceneData.grpc.pb.h"
#include "IETThread.h"
#include "ThreadPool.h"
class SceneServer final: public MeshStream::Service, public IETThread
{
private:
	ThreadPool* threadPool;
public:
	SceneServer();

	void run() override;
	grpc::Status StreamMesh(grpc::ServerContext* context, const MeshRequest* request, grpc::ServerWriter<MeshReply>* writer) override;
	static void RunServer(uint16_t port);
};

