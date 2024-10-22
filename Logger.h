#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#ifndef Logger_h
#define Logger_h

class Logger
{
public:
	/// <summary>
	/// Returns the current timestamp in the format of "[YYYY-MM-DD][HH:MM:SS]"
	/// </summary>
	/// <returns>string</returns>
	static string GetTimestamp();
private:
	/// <summary>
	/// Returns the current year
	/// </summary>
	/// <param name="newtime"></param>
	/// <param name="now"></param>
	/// <returns>string</returns>
	static string getYear(tm newtime, time_t now);
	/// <summary>
	/// Returns the current month
	/// </summary>
	/// <param name="newtime"></param>
	/// <param name="now"></param>
	/// <returns>string</returns>
	static string getMonth(tm newtime, time_t now);
	/// <summary>
	/// Returns the current day
	/// </summary>
	/// <param name="newtime"></param>
	/// <param name="now"></param>
	/// <returns>string</returns>
	static string getDay(tm newtime, time_t now);
	/// <summary>
	/// Returns the current hour
	/// </summary>
	/// <param name="newtime"></param>
	/// <param name="now"></param>
	/// <returns>string</returns>
	static string getHour(tm newtime, time_t now);
	/// <summary>
	/// Returns the current minute
	/// </summary>
	/// <param name="newtime"></param>
	/// <param name="now"></param>
	/// <returns>string</returns>
	static string getMinute(tm newtime, time_t now);
	/// <summary>
	/// Returns the current second
	/// </summary>
	/// <param name="newtime"></param>
	/// <param name="now"></param>
	/// <returns>string</returns>
	static string getSecond(tm newtime, time_t now);
	/// <summary>
	/// Returns the current millisecond
	/// </summary>
	/// <param name="newtime"></param>
	/// <param name="now"></param>
	/// <returns>string</returns>
	static string getMilliseconds();
};

#endif // !Logger_h
