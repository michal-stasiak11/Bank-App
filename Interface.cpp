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
		break;
	case 2 :
		Interface::Login();
		break;
	case 3 :
		return false;
	}
	return true;
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
				if (login == ToString(sheet->readStr(row, 1)))
				{
					Interface::MainMenuMessage = "Account with such login already exists.\n\n";
					return;
				}
			}
			std::cout << "Enter password for you account : ";
			std::cin >> password;
			std::cout << "Enter password for your account again to confirm : ";
			std::cin >> password_2;
			if (password != password_2)
			{
				Interface::MainMenuMessage = "Passwords do not match.\n\n";
				return;
			}
			std::string account_number;
			bool flag;
			do
			{
				flag = false;
				account_number = AccountNumber(5);
				for (int row = 1; row < sheet->lastFilledRow(); row++)
				{
					if (account_number == ToString(sheet->readStr(row, 3))) flag = true;
				}
			} while (flag);
			int account_row = sheet->lastFilledRow();
			sheet->writeStr(account_row, 1, ToWString(login).data());
			sheet->writeStr(account_row, 2, ToWString(password).data());
			sheet->writeStr(account_row, 3, ToWString(account_number).data());
			sheet->writeNum(account_row, 4, 0);
			Interface::MainMenuMessage = "Account created succsefully.\n\n";
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
				if (login == ToString(sheet->readStr(row, 1)))
				{
					std::cout << "Enter password : ";
					std::cin >> password;
					if (password == ToString(sheet->readStr(row, 2)))
					{
						Interface::AccountMenuMessage = "Login succesful.\n\n";
						while (Interface::AccountMenu(row));
					} 
					else Interface::MainMenuMessage = "Wrong password.\n\n";
					return;
				}
			}
		}
		
	}
	credentials->release();
	Interface::MainMenuMessage = "No account matches that login.\n\n";
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
		<< "[4] Account info\n"
		<< "[5] Money transfer\n"
		<< "[6] Delete account\n"
		<< "[7] Log out\n\n";
	std::cin >> option;
	switch (option)
	{
	case 1:
		Interface::ChangePassword(account_row);
		break;
	case 2 :
		Interface::Deposit(account_row);
		break;
	case 3 :
		Interface::Withdraw(account_row);
		break;
	case 4 :
		Interface::AccountInfo(account_row);
		break;
	case 5 :
		Interface::Transfer(account_row);
		break;
	case 6 :
		return Interface::DeleteAccount(account_row);
	case 7 :
		return false;
	}
	return true;
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
			std::cout << "Enter old password : ";
			std::cin >> old_password;
			if (old_password != ToString(sheet->readStr(account_row, 2)))
			{
				Interface::AccountMenuMessage = "Wrong password.\n\n";
				return;
			}
			std::cout << "Enter new password for you account : ";
			std::cin >> new_password;
			std::cout << "Enter new password for your account again to confirm : ";
			std::cin >> new_password_2;
			if (new_password != new_password_2)
			{
				Interface::AccountMenuMessage = "New passwords do not match.\n\n";
				return;
			}
			sheet->writeStr(account_row, 2, ToWString(new_password).data());
			Interface::AccountMenuMessage = "Password updated succsefully.\n\n";
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
			std::string password;
			std::cout << "Enter password : ";
			std::cin >> password;
			if (password != ToString(sheet->readStr(account_row, 2)))
			{
				Interface::AccountMenuMessage = "Wrong password.\n\n";
				return;
			}
			sheet->writeNum(account_row, 4, sheet->readNum(account_row, 4) + sum);
			Interface::AccountMenuMessage = "Deposit successfull\n\n";
			credentials->save(L"credentials.xlsx");
			credentials->release();
			return;
		}
	}
}

void Interface::Withdraw(int account_row)
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
			if (sum > sheet->readNum(account_row, 4))
			{
				Interface::AccountMenuMessage = "Your account does not have enough money to withdraw.\n\n";
				return;
			}
			std::string password;
			std::cout << "Enter password : ";
			std::cin >> password;
			if (password != ToString(sheet->readStr(account_row, 2)))
			{
				Interface::AccountMenuMessage = "Wrong password\n\n";
				return;
			}
			sheet->writeNum(account_row, 4, sheet->readNum(account_row, 4) - sum);
			Interface::AccountMenuMessage = "Withdrawal successfull.\n\n";
			credentials->save(L"credentials.xlsx");
			credentials->release();
			return;
		}
	}
}

void Interface::AccountInfo(int account_row)
{
	CLEAR;
	libxl::Book* credentials = xlCreateXMLBook();
	if (credentials->load(L"credentials.xlsx"))
	{
		libxl::Sheet* sheet = credentials->getSheet(0);
		if (sheet)
		{
			Interface::AccountMenuMessage = "Your account number is : " + ToString(sheet->readStr(account_row, 3)) + "\n";
			Interface::AccountMenuMessage += "Your account balance is : " + std::to_string(sheet->readNum(account_row, 4)).substr(0, std::to_string(sheet->readNum(account_row, 4)).find(".") + 3) + "\n\n";
			credentials->save(L"credentials.xlsx");
			credentials->release();
			return;
		}
	}
}

void Interface::Transfer(int account_row)
{
	CLEAR;
	libxl::Book* credentials = xlCreateXMLBook();
	if (credentials->load(L"credentials.xlsx"))
	{
		libxl::Sheet* sheet = credentials->getSheet(0);
		if (sheet)
		{
			std::string account_number, password;
			int row;
			bool found = false;
			double sum;
			std::cout << "Enter account number you wish to transfer money to : ";
			std::cin >> account_number;
			for (row = 1; row < sheet->lastFilledRow(); row++)
			{
				if (account_number == ToString(sheet->readStr(row, 3)))
				{
					found = true; 
					break;
				}
			}
			if (!found)
			{

				Interface::AccountMenuMessage = "No account matches that account number.\n\n";
				return;
			}
			std::cout << "Enter the sum to transfer : ";
			std::cin >> sum;
			if (sum > sheet->readNum(account_row, 4))
			{
				Interface::AccountMenuMessage = "Your account does not have enough money to transfer.\n\n";
				return;
			}
			std::cout << "Enter password : ";
			std::cin >> password;
			if (password != ToString(sheet->readStr(account_row, 2)))
			{
				Interface::AccountMenuMessage = "Wrong password.\n\n";
				return;
			}
			sheet->writeNum(account_row, 4, sheet->readNum(account_row, 4) - sum);
			sheet->writeNum(row, 4, sheet->readNum(row, 4) + sum);
			Interface::AccountMenuMessage = "Transfer successfull.\n\n";
			credentials->save(L"credentials.xlsx");
			credentials->release();
			return;
		}
	}
}

bool Interface::DeleteAccount(int account_row)
{
	CLEAR;
	libxl::Book* credentials = xlCreateXMLBook();
	if (credentials->load(L"credentials.xlsx"))
	{
		libxl::Sheet* sheet = credentials->getSheet(0);
		if (sheet)
		{
			if (sheet->readNum(account_row, 4) > 0)
			{
				Interface::AccountMenuMessage = "You can only delete empty accounts. Withdraw money first.\n\n";
				return true;
			}
			std::string confirmation, password;
			std::cout << "Are you sure you want to delete this account?\n(Type yes) : ";
			std::cin >> confirmation;
			if (confirmation != "Yes" && confirmation != "yes")
			{
				Interface::AccountMenuMessage = "";
				return true;
			}
			std::cout << "Enter password : ";
			std::cin >> password;
			if (password != ToString(sheet->readStr(account_row, 2)))
			{
				Interface::AccountMenuMessage = "Wrong password.\n\n";
				return true;
			}
			sheet->removeRow(account_row, account_row);
			Interface::MainMenuMessage = "Account deleted succsessfully.\n\n";
			credentials->save(L"credentials.xlsx");
			credentials->release();
			return false;
		}
	}
}
