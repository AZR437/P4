//#include "SceneServer.h"
//#include "SceneClient.h"
#include "BaseRunner.h"

#define Client
#ifdef Server
int main()
{
	//SceneServer server;
	server.run();
	while (true)
	{

	}
	return 0;
}
#else
int main()
{
	//SceneClient::runClient();
	BaseRunner baseRunner = BaseRunner();
	baseRunner.run();

	return 0;
}
#endif // !Server

