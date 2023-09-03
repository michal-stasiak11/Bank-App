#include "Tools.h"

std::string AccountNumber(int length)
{
	srand(time(NULL));
	std::string numbers = "0123456789";
	std::string result;
	for (int i = 0; i < length; i++)
	{
		result += numbers[rand() % 10];
	}
	return result;
}

std::string ToString(std::wstring w_string)
{
	return std::string(w_string.begin(), w_string.end());
}

std::wstring ToWString(std::string string)
{
	return std::wstring(string.begin(), string.end());
}

std::string GetTime()
{
	time_t current_time = time(NULL);
	tm* local_time = localtime(&current_time);
	std::string time_str;

	if (local_time->tm_mday < 10) time_str += "0";
	time_str += std::to_string(local_time->tm_mday) + ".";
	if (local_time->tm_mon < 10) time_str += "0";
	time_str += std::to_string(local_time->tm_mon) + ".";
	time_str += std::to_string(local_time->tm_year + 1900) + " ";
	time_str += std::to_string(local_time->tm_hour) + ":";
	if (local_time->tm_min < 10) time_str += "0";
	time_str += std::to_string(local_time->tm_min) + ":";
	if (local_time->tm_sec < 10) time_str += "0";
	time_str += std::to_string(local_time->tm_sec);

	return time_str;
}