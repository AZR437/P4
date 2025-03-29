#pragma once
#include "iostream"
#include "chrono"
#include "ctime"

class BaseRunner;

class Time
{
public:
	static Time* getInstance();

	double getTime();
	double getDeltaTime();
	double getUnscaledTime();
	double getUnscaledDeltaTime();
	void setTimeScale(double timeScale);

private:
	Time() {};
	Time(Time const&) {};
	Time& operator=(Time const&) {};
	static Time* sharedInstance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double time = 0.0;
	double deltaTime = 0.0;
	double unscaledTime = 0.0;
	double unscaledDeltaTime = 0.0;
	double timeScale = 1.0;

	void logFrameStart();
	void logFrameEnd();

	friend class BaseRunner;
};

