#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>

namespace Interface {

	static std::string message = "";

	bool Menu();

	void Register();

	void Login();

	void AccountMenu(std::string login);

};