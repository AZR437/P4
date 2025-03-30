#include "PoolWorkerThread.h"
#include "ThreadPool.h"

PoolWorkerThread::PoolWorkerThread(int threadID, IFinishedTask* finishedTask) : threadID(threadID), finishedTask(finishedTask)
{
    this->action = nullptr;
}

PoolWorkerThread::~PoolWorkerThread()
{

}

void PoolWorkerThread::assignTask(IWorkerAction* action)
{
    this->action = action;
}

void PoolWorkerThread::run()
{
    this->action->onStartTask();
    this->finishedTask->onFinished(this->threadID);
}

int PoolWorkerThread::getThreadID() const
{
    return this->threadID;
}
