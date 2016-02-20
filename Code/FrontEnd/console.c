#include <stdio.h>
#include "iostream"
#include "string"
#include "fstream"

using namespace std;

string lower(string str){
	for (int i=0; i<str.length(); i++){
		str.at(i) = tolower(str.at(i));
	}
	return str;
}

/**
 * New session is created every Login and deleted on Logout
 */
class Session{
	bool admin;
	string user;
	string command;

	/**
	 * @param account holder name to be validated
	 * 
	 * Validates account holder name
	 */
	bool validHolder(string name){
		ifstream bankAccounts("currentBankAccountsFile");
		if(bankAccounts.is_open()){
			for(string accountLine; getline(bankAccounts, accountLine); ){
				accountLine = accountLine.substr(6,name.length());
				printf("%s\n", accountLine.c_str());
				if(accountLine.compare(name) == 0){
					bankAccounts.close();
					return true;
				}
			}
		} else {
			printf("File could not be opened.\n");
		}

		return false;
	}

	/** 
	 * Reads in commands to perform transactions
	 */
	void input(){
		printf("Enter a command:\n");
		getline(cin, command);
		command = lower(command);
		while(command.compare("logout") != 0){
			printf("Enter a command:\n");
			getline(cin, command);
			command = lower(command);
		}

		return;
	}

  public:
	/**
	 * Login to session
	 */
	void login(){
		printf("Enter type of account: \"standard\" or \"admin\"\n");
		getline(cin, command);
		command = lower(command);
		
		// Returns to login if command is unrecognized
		if(command.compare("admin") != 0 && command.compare("standard") != 0){
			printf("Error, unrecognized command\n");
			return;
		}
		admin = command.compare("admin") == 0;

		if(!admin){
			// Continue standard user login
			printf("Logging in as standard user - enter name:\n");
			getline(cin, command);
			// Return to login if invalid user name
			if(!validHolder(command)){
				printf("ERROR: User \"%s\" does not exist. Try again\n", command.c_str());
				return;
			}

			// Successful standard user login
			printf("You are now logged in as \"%s\"\n", command.c_str());
			user = command;
		} else {
			// Successful admin login
			printf("You are now logged in as an admin\n");
		}

		input();

		return;
	}
};

/**
 * @param name of text file to use as command input 
 * or nothing (if intended for terminal)
 * 
 * Reads input until a valid login is called
 */
int main(int argc, const char* argv[]){
	string input = "";
	printf("Login to start:\n");
	getline(cin, input);
	input = lower(input);
	while(input.compare("quit") != 0){
		if(input.compare("login") == 0){
			Session session;
			session.login();
		} else {
			printf("ERROR: Not logged in\n");
		}
		printf("Login to start:\n");
		getline(cin, input);
		input = lower(input);
	}

	return 0;
}