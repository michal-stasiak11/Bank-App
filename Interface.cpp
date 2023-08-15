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
		<< "[3] Exit\n";
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

void Interface::Register() { return; }

void Interface::Login()
{
	system("cls");
	std::fstream credentials;
	credentials.open("Credentials.csv");
	std::string login, password, user_login, user_password, temp;
	std::cout << "Enter login : ";
	std::cin >> login;
	while (credentials >> temp)
	{
		std::stringstream user_data(temp);
		std::getline(user_data, user_login, ',');
		if(login == user_login)
		{
			std::cout << "Enter password : ";
			std::cin >> password;
			std::getline(user_data, user_password);
			if (password == user_password) 
			{
				Interface::AccountMenu(login);
			}
			else
			{
				Interface::message = "Wrong password\n\n";
			}
			return;
		}
	}
	Interface::message = "No account matches that login\n\n";
}

void Interface::AccountMenu(std::string login){};


