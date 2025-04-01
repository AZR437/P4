#pragma once
#include <string>
#include "SceneData.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class StreamMeshClient
{
public:
	StreamMeshClient(std::shared_ptr<grpc::ChannelInterface> channel);
	std::string StreamMesh(std::string objName);
private:
	std::unique_ptr<MeshStream::Stub> stub_;
};
class SceneClient
{
public:
	static void runClient();

};

