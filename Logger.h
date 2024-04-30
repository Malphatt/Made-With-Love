#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;
using namespace chrono;

#ifndef Logger_h
#define Logger_h

class Logger
{
public:
	static string GetTimestamp();
private:
	static string getYear(tm newtime, time_t now);
	static string getMonth(tm newtime, time_t now);
	static string getDay(tm newtime, time_t now);
	static string getHour(tm newtime, time_t now);
	static string getMinute(tm newtime, time_t now);
	static string getSecond(tm newtime, time_t now);
};

#endif // !Logger_h
