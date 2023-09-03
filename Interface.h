#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include "libxl.h"
#include "Tools.h"

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

	bool DeleteAccount(int account_row);

};

