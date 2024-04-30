#include "Logger.h"

string Logger::GetTimestamp()
{
	struct tm newtime;
	time_t now = time(0);

	localtime_s(&newtime, &now);

	stringstream ss;
	ss << "[" << getYear(newtime, now) << "-" << getMonth(newtime, now) << "-" << getDay(newtime, now) << "][" << getHour(newtime, now) << ":" << getMinute(newtime, now) << ":" << getSecond(newtime, now) << "]";

	return ss.str();
}

string Logger::getYear(tm newtime, time_t now)
{
	string year = to_string(newtime.tm_year + 1900);
	return year;
}

string Logger::getMonth(tm newtime, time_t now)
{
	string month = to_string(newtime.tm_mon + 1);
	if (newtime.tm_mon < 10) return "0" + month;
	else return month;
}

string Logger::getDay(tm newtime, time_t now)
{
	string day = to_string(newtime.tm_mday);
	if (newtime.tm_mday < 10) return "0" + day;
	else return day;
}

string Logger::getHour(tm newtime, time_t now)
{
	string hour = to_string(newtime.tm_hour);
	if (newtime.tm_hour < 10) return "0" + hour;
	else return hour;
}

string Logger::getMinute(tm newtime, time_t now)
{
	string minute = to_string(newtime.tm_min);
	if (newtime.tm_min < 10) return "0" + minute;
	else return minute;
}

string Logger::getSecond(tm newtime, time_t now)
{
	string second = to_string(newtime.tm_sec);
	if (newtime.tm_sec < 10) return "0" + second;
	else return second;
}