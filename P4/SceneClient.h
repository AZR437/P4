#pragma once
#include <string>
#include "SceneData.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class SceneClient
{
public:
	SceneClient(std::shared_ptr<grpc::ChannelInterface> channel);
	std::string StreamMesh(std::string objName);

	static void runClient();
private:
	std::unique_ptr<MeshStream::Stub> stub_;
};

