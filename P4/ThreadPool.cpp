#include "ThreadPool.h"
#include "IWorkerAction.h"
#include "PoolWorkerThread.h"

ThreadPool::ThreadPool(String name, int numWorkers) : name(name), numWorkers(numWorkers)
{
	for (int i = 0; i < this->numWorkers; i++)
	{
		this->inactiveThreads.push(new PoolWorkerThread(i, this));
	}
}

ThreadPool::~ThreadPool()
{
	this->stopScheduler();
	this->activeThreads.clear();

	while (!this->inactiveThreads.empty())
		this->inactiveThreads.pop();
}

void ThreadPool::startScheduler()
{
	this->running = true;
	this->start();
}

void ThreadPool::stopScheduler()
{
	this->running = false;
}

void ThreadPool::scheduleTask(IWorkerAction* action)
{
	this->pendingActions.push(action);
}

void ThreadPool::run()
{
	while (this->running)
	{
		if (!this->pendingActions.empty() && !this->inactiveThreads.empty())
		{
			PoolWorkerThread* workerThread = this->inactiveThreads.front();
			this->inactiveThreads.pop();
			this->activeThreads[workerThread->getThreadID()] = workerThread;

			workerThread->assignTask(this->pendingActions.front());
			workerThread->start();
			this->pendingActions.pop();

			std::cout << "Pending actions remaining: " << this->pendingActions.size() << "\n";
		}
	}
}

void ThreadPool::onFinished(int threadID)
{
	if (this->activeThreads[threadID])
	{
		this->inactiveThreads.push(this->activeThreads[threadID]);
		this->activeThreads.erase(threadID);
	}
}
