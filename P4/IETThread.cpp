#include "IETThread.h"

IETThread::IETThread()
{
}

IETThread::~IETThread()
{
}

void IETThread::start()
{
	std::thread(&IETThread::run, this).detach(); //detach thread for independent execution. without this, join() function must be called.
}

void IETThread::sleep(unsigned int ms)
{
	std::cout << "sleeping for " << ms << " milliseconds" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	std::cout << "done"<<std::endl;
}
