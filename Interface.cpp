#include "Interface.h"

bool Interface::Menu()
{
	system("cls");
	std::cout << message;
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
	default :
		return false;
	}
}

void Interface::Register() 
{
	system("cls");
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
					Interface::message = "Account with such login already exists\n\n";
					return;
				}
			}
			std::cout << "Enter password for you account : ";
			std::cin >> password;
			std::cout << "Enter password for your account again to confirm : ";
			std::cin >> password_2;
			if (password != password_2)
			{
				Interface::message = "Passwords do not match\n\n";
				return;
			}
			int row = sheet->lastFilledRow();
			std::wstring w_login(login.begin(), login.end());
			sheet->writeStr(row, 1, w_login.data());
			std::wstring w_password(password.begin(), password.end());
			sheet->writeStr(row, 2, w_password.data());
			Interface::message = "Account created succsefully\n\n";
			credentials->save(L"credentials.xlsx");
			credentials->release();
			return;
		}
	}
}

void Interface::Login()
{
	system("cls");
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
					if (password == s_password) Interface::AccountMenu(login);
					else Interface::message = "Wrong password\n\n";
					return;
				}
			}
		}
		
	}
	credentials->release();
	Interface::message = "No account matches that login\n\n";
}

void Interface::AccountMenu(std::string login)
{
	Interface::message = "";
}


