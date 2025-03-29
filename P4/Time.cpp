#include "Time.h"

Time* Time::sharedInstance = NULL;

Time* Time::getInstance()
{
    if (sharedInstance == NULL)
    {
        sharedInstance = new Time();
    }

    return sharedInstance;
}

void Time::logFrameStart()
{
    this->start = std::chrono::system_clock::now();
}

void Time::logFrameEnd()
{
    this->end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = this->end - this->start;

    this->unscaledDeltaTime = elapsedSeconds.count();
    this->deltaTime = elapsedSeconds.count() * this->timeScale;

    this->time += this->deltaTime;
    this->unscaledTime += this->unscaledDeltaTime;
}

double Time::getTime()
{
    return this->time;
}

double Time::getDeltaTime()
{
    return this->deltaTime;
}

double Time::getUnscaledTime()
{
    return this->unscaledTime;
}

double Time::getUnscaledDeltaTime()
{
    return this->unscaledDeltaTime;
}

void Time::setTimeScale(double timeScale)
{
    this->timeScale = timeScale;
}
