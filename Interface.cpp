#include "Interface.h"

bool Interface::MainMenu()
{
	CLEAR;
	std::cout << Interface::MainMenuMessage;
	int option;
	std::cout
		<< "Choose one of the following options : \n\n"
		<< "[1] Create an account\n"
		<< "[2] Log in\n"
		<< "[3] Exit\n\n";
	std::cin >> option;
	switch (option)
	{
	case 1 :
		Interface::Register();
		return true;
	case 2 :
		Interface::Login();
		return true;
	case 3 :
		return false;
	default :
		return true;
	}
}

void Interface::Register() 
{
	CLEAR;
	libxl::Book* credentials = xlCreateXMLBook();
	if (credentials->load(L"credentials.xlsx"))
	{
		libxl::Sheet* sheet = credentials->getSheet(0);
		if (sheet)
		{
			std::string login, password, password_2;
			std::cout << "Enter login for you account : ";
			std::cin >> login;
			for (int row = 1; row < sheet->lastFilledRow(); row++)
			{
				std::wstring w_login(sheet->readStr(row, 1));
				std::string s_login(w_login.begin(), w_login.end());
				if (login == s_login)
				{
					Interface::MainMenuMessage = "Account with such login already exists\n\n";
					return;
				}
			}
			std::cout << "Enter password for you account : ";
			std::cin >> password;
			std::cout << "Enter password for your account again to confirm : ";
			std::cin >> password_2;
			if (password != password_2)
			{
				Interface::MainMenuMessage = "Passwords do not match\n\n";
				return;
			}
			int row = sheet->lastFilledRow();
			sheet->writeStr(row, 1, std::wstring(login.begin(), login.end()).data());
			sheet->writeStr(row, 2, std::wstring(password.begin(), password.end()).data());
			sheet->writeNum(row, 3, 0);
			Interface::MainMenuMessage = "Account created succsefully\n\n";
			credentials->save(L"credentials.xlsx");
			credentials->release();
			return;
		}
	}
}

void Interface::Login()
{
	CLEAR;
	libxl::Book* credentials = xlCreateXMLBook();
	if(credentials->load(L"credentials.xlsx"))
	{
		libxl::Sheet* sheet = credentials->getSheet(0);
		if (sheet)
		{
			std::string login, password, temp;
			std::cout << "Enter login : ";
			std::cin >> login;
			for (int row = 1; row < sheet->lastFilledRow(); row++)
			{
				std::wstring w_login(sheet->readStr(row, 1));
				std::string s_login(w_login.begin(), w_login.end());
				if (login == s_login)
				{
					std::cout << "Enter password : ";
					std::cin >> password;
					std::wstring w_password(sheet->readStr(row, 2));
					std::string s_password(w_password.begin(), w_password.end());
					if (password == s_password) 
					{
						Interface::AccountMenuMessage = "Login succesful\n\n";
						while (Interface::AccountMenu(row));
					} 
					else Interface::MainMenuMessage = "Wrong password\n\n";
					return;
				}
			}
		}
		
	}
	credentials->release();
	Interface::MainMenuMessage = "No account matches that login\n\n";
}

bool Interface::AccountMenu(int account_row)
{
	CLEAR;
	std::cout << Interface::AccountMenuMessage;
	int option;
	std::cout
		<< "Choose one of the following options : \n\n"
		<< "[1] Change password\n"
		<< "[2] Deposit money\n"
		<< "[3] Withdraw money\n"
		<< "[4] Account balance\n"
		<< "[5] Log out\n\n";
	std::cin >> option;
	switch (option)
	{
	case 1:
		Interface::ChangePassword(account_row);
		return true;
	case 2 :
		Interface::Deposit(account_row);
		return true;
	case 3 :
		Interface::Withdraw(account_row);
		return true;
	case 4 :
		Interface::AccountBalance(account_row);
		return true;
	case 5 :
		return false;
	default :
		return true;
	}
}

void Interface::ChangePassword(int account_row)
{
	CLEAR;
	libxl::Book* credentials = xlCreateXMLBook();
	if (credentials->load(L"credentials.xlsx"))
	{
		libxl::Sheet* sheet = credentials->getSheet(0);
		if (sheet)
		{
			std::string old_password, new_password, new_password_2;
			std::wstring w_password(sheet->readStr(account_row, 2));
			std::cout << "Enter old password : ";
			std::cin >> old_password;
			if (old_password != std::string(w_password.begin(), w_password.end()))
			{
				Interface::AccountMenuMessage = "Wrong password\n\n";
				return;
			}
			std::cout << "Enter new password for you account : ";
			std::cin >> new_password;
			std::cout << "Enter new password for your account again to confirm : ";
			std::cin >> new_password_2;
			if (new_password != new_password_2)
			{
				Interface::AccountMenuMessage = "New passwords do not match\n\n";
				return;
			}
			sheet->writeStr(account_row, 2, std::wstring(new_password.begin(), new_password.end()).data());
			Interface::AccountMenuMessage = "Password updated succsefully\n\n";
			credentials->save(L"credentials.xlsx");
			credentials->release();
			return;
		}
	}
}

void Interface::Deposit(int account_row)
{
	CLEAR;
	libxl::Book* credentials = xlCreateXMLBook();
	if (credentials->load(L"credentials.xlsx"))
	{
		libxl::Sheet* sheet = credentials->getSheet(0);
		if (sheet)
		{
			std::cout << "Enter the sum to deposit : ";
			double sum;
			std::cin >> sum;
			sheet->writeNum(account_row, 3, sheet->readNum(account_row, 3) + sum);
			Interface::AccountMenuMessage = "Deposit successfull\n\n";
			credentials->save(L"credentials.xlsx");
			credentials->release();
			return;
		}
	}
}

void Interface::Withdraw(int account_row) 
{
	{
		CLEAR;
		libxl::Book* credentials = xlCreateXMLBook();
		if (credentials->load(L"credentials.xlsx"))
		{
			libxl::Sheet* sheet = credentials->getSheet(0);
			if (sheet)
			{
				std::cout << "Enter the sum to withdraw : ";
				double sum;
				std::cin >> sum;
				if (sum > sheet->readNum(account_row, 3))
				{
					Interface::AccountMenuMessage = "Your account does not have enough money to withdraw\n\n";
					return;
				}
				sheet->writeNum(account_row, 3, sheet->readNum(account_row, 3) - sum);
				Interface::AccountMenuMessage = "Withdrawal successfull\n\n";
				credentials->save(L"credentials.xlsx");
				credentials->release();
				return;
			}
		}
	}
}

void Interface::AccountBalance(int account_row)
{
	{
		CLEAR;
		libxl::Book* credentials = xlCreateXMLBook();
		if (credentials->load(L"credentials.xlsx"))
		{
			libxl::Sheet* sheet = credentials->getSheet(0);
			if (sheet)
			{
				Interface::AccountMenuMessage = "Your account balance is : " + std::to_string(sheet->readNum(account_row,3)).substr(0, std::to_string(sheet->readNum(account_row, 3)).find(".") + 3) + "\n\n";
				credentials->save(L"credentials.xlsx");
				credentials->release();
				return;
			}
		}
	}
}




