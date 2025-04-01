#include "SceneServer.h"
#include "SceneClient.h"
#include "BaseRunner.h"

#define Client
#ifdef Server
int main()
{
	SceneServer server;
	server.start();
	while (true)
	{

	}
	return 0;
}
#else
int main()
{
	BaseRunner baseRunner = BaseRunner();
	SceneClient::runClient();
	baseRunner.run();

	return 0;
}
#endif // !Server

