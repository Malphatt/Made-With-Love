#include "Logger.h"
#include <WTypesbase.h>

string Logger::GetTimestamp()
{
	// Get the current time
	struct tm newtime;
	time_t now = time(0);

	// Get the current time as local time
	localtime_s(&newtime, &now);

	// Construct the timestamp string in the format [YYYY-MM-DD][HH:MM:SS:mmm]
	stringstream ss;
	ss << "[" << getYear(newtime, now) << "-" << getMonth(newtime, now) << "-" << getDay(newtime, now) << "][" << getHour(newtime, now) << ":" << getMinute(newtime, now) << ":" << getSecond(newtime, now) << ":" << getMilliseconds() << "]";

	return ss.str();
}

string Logger::getYear(tm newtime, time_t now)
{
	// Get the current year
	string year = to_string(newtime.tm_year + 1900);
	return year;
}

string Logger::getMonth(tm newtime, time_t now)
{
	// Get the current month
	string month = to_string(newtime.tm_mon + 1);
	if (newtime.tm_mon < 10) return "0" + month;
	else return month;
}

string Logger::getDay(tm newtime, time_t now)
{
	// Get the current day
	string day = to_string(newtime.tm_mday);
	if (newtime.tm_mday < 10) return "0" + day;
	else return day;
}

string Logger::getHour(tm newtime, time_t now)
{
	// Get the current hour
	string hour = to_string(newtime.tm_hour);
	if (newtime.tm_hour < 10) return "0" + hour;
	else return hour;
}

string Logger::getMinute(tm newtime, time_t now)
{
	// Get the current minute
	string minute = to_string(newtime.tm_min);
	if (newtime.tm_min < 10) return "0" + minute;
	else return minute;
}

string Logger::getSecond(tm newtime, time_t now)
{
	// Get the current second
	string second = to_string(newtime.tm_sec);
	if (newtime.tm_sec < 10) return "0" + second;
	else return second;
}

string Logger::getMilliseconds()
{
	// Get the current millisecond
	SYSTEMTIME st;
	GetSystemTime(&st);
	string millisecond = to_string(st.wMilliseconds);
	if (st.wMilliseconds < 10) return "00" + millisecond;
	else if (st.wMilliseconds < 100) return "0" + millisecond;
	else return millisecond;
}