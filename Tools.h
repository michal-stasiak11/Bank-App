#pragma once

#include <string>
#include <stdlib.h>
#include <time.h>

#define CLEAR system("cls")

std::string AccountNumber(int length);

std::string ToString( std::wstring w_string);

std::wstring ToWString(std::string string);