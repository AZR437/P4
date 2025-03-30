#pragma once

#include "IETThread.h"
#include "IWorkerAction.h"

class IFinishedTask;

class PoolWorkerThread : public IETThread
{
public:
	PoolWorkerThread(int threadID, IFinishedTask* finishedTask);
	~PoolWorkerThread();

	void assignTask(IWorkerAction* action);

	int getThreadID() const;

private:
	void run() override;

	int threadID = 0;
	IWorkerAction* action;
	IFinishedTask* finishedTask;
};

