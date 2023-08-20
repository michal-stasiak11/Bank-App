#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "libxl.h"

#define CLEAR system("cls")

namespace Interface {

	static std::string MainMenuMessage = "";
	static std::string AccountMenuMessage = "";

	bool MainMenu();

	void Register();

	void Login();

	bool AccountMenu(int account_row);

	void ChangePassword(int account_row);

	void Deposit(int account_row);

	void Withdraw(int account_row);

	void AccountInfo(int account_row);

	void Transfer(int account_row);

};

std::wstring AccountNumber(int length);