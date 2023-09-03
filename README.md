# Bank-App
Terminal-based banking application

Currently, the app uses LibXL library to modify .xlsx files to store credentials of the accounts.

Application is a loose simulator of a bank account management. Users can create accounts and log onto them. Upon creation, user's account is given a randomly generated account number. After logging in, the following funtions are implemented :
- money deposit
- money withdrawal
- cheking the account balance and its account number
- transfering money to another account
- account deletion

Every action done concerning an account is registred in a .log files with a date of action.

Additionally, the Tools.cpp file contains functions and macros essential for the clearance of code.
