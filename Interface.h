#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include "libxl.h"

namespace Interface {

	static std::string message = "";

	bool Menu();

	void Register();

	void Login();

	void AccountMenu(std::string login);

};