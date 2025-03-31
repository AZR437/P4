#include "SceneServer.h"
#include "SceneClient.h"
#define Client
#ifdef Server
int main()
{
	SceneServer server;
	server.run();
	while (true)
	{

	}
	return 0;
}
#else
int main()
{
	SceneClient::runClient();
	return 0;
}
#endif // !Server

