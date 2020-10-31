#ifndef __RT_UTILITIES__
#define __RT_UTILITIES__

#include <string>
#include <thread>
#include <chrono>

void ToLowerString(std::string &str)
{
	for (auto &i : str)
		if (i >= 'A' && i <= 'Z') i += 32;
}

void inline sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#endif
