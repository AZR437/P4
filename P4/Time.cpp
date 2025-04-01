#include "Time.h"

Time* Time::sharedInstance = NULL;

void Time::initialize()
{
    sharedInstance = new Time();
}

void Time::destroy()
{
    delete sharedInstance;
}

void Time::logFrameStart()
{
    sharedInstance->start = std::chrono::system_clock::now();
}

void Time::logFrameEnd()
{
    sharedInstance->end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = sharedInstance->end - sharedInstance->start;

    sharedInstance->unscaledDeltaTime = elapsedSeconds.count();
    sharedInstance->deltaTime = elapsedSeconds.count() * sharedInstance->timeScale;

    sharedInstance->time += sharedInstance->deltaTime;
    sharedInstance->unscaledTime += sharedInstance->unscaledDeltaTime;
}

double Time::getTime()
{
    return sharedInstance->time;
}

double Time::getDeltaTime()
{
    return sharedInstance->deltaTime;
}

double Time::getUnscaledTime()
{
    return sharedInstance->unscaledTime;
}

double Time::getUnscaledDeltaTime()
{
    return sharedInstance->unscaledDeltaTime;
}

void Time::setTimeScale(double timeScale)
{
    sharedInstance->timeScale = timeScale;
}
