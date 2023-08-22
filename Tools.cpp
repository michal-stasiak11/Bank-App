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