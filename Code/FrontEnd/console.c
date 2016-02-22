#include <stdio.h>
#include <stdlib.h>
#include "iostream"
#include "string"
#include "fstream"

using namespace std;

/**
 * @param takes the string to be converted to lowercase
 * @return returns the lowercase string
 * 
 * Converts a string to lowercase
 */
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
	string trans_str = "";

	/**
	 * @param 5 components of the transaction file lines
	 * 
	 * adds transactions to the session's transaction string (trans_str)
	 */
	void createTransaction(string code, string name, string num, float val, string misc){
		return;
	}

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
	 * Validates account number matches account holder
	 */
	bool validNumber(string num, string holder){
		ifstream bankAccounts("currentBankAccountsFile");
		if(bankAccounts.is_open()){
			for(string accountLine; getline(bankAccounts, accountLine); ){
				accountLine = accountLine.substr(0,holder.length()+6);
				if(accountLine.substr(6).compare(holder) == 0 && 
					accountLine.substr(0, 5).compare(num) == 0){
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
	 * Deposits money into account.
	 */
	void deposit(){
		float val;
		string num, str_val, name;
		// admin users have extra information they must provide
		if(admin){
			printf("COMMAND: deposit - enter user:\n");
			getline(cin, name);
			if(!validHolder(name)){
				printf("ERROR: User \"%s\" does not exist. Try again\n", 
					name.c_str());
				return;
			}
			printf("Depositing to \"%s\" - enter account number:\n", name.c_str());
		} else {
			// standard users can only deposit into their own accounts
			name = user;
			printf("COMMAND: deposit - enter account number:\n");
		}
		// account number
		getline(cin, num);
		if(!validNumber(num, name)){
			printf("ERROR: Account number \"%s\" is not valid. Try again\n", num.c_str());
			return;
		}
		printf("Depositing to \"%s\" - enter amount:\n", num.c_str());
		// amount of deposit
		getline(cin, str_val);
		val = stof(str_val);
		// maximum deposit
		if(val >= 1000.00){
			printf("ERROR: Maximum balance exceeded. Try again\n");
			return;
		}

		// create successful transaction code
		createTransaction("04", name, num, val, "");

		return;
	}

	/**
	 * prints trans_str to transaction file
	 */
	void logout(){
		createTransaction("00", "", "", 0.0, "");
		return;
	}

	/** 
	 * Reads in commands to perform transactions
	 */
	void input(){
		printf("Enter a command:\n");
		getline(cin, command);
		command = lower(command);
		while(command.compare("logout") != 0){
			if(command.compare("deposit") == 0){
				deposit();
			} else if(command.compare("withdraw") == 0){
//				withdraw();
			} else if(command.compare("create") == 0){
//				create();
			} else if(command.compare("delete") == 0){
//				delete();
			} else if(command.compare("enable") == 0){
//				enable();
			} else if(command.compare("disable") == 0){
//				disable();
			} else if(command.compare("paybill") == 0){
//				paybill();
			} else if(command.compare("transfer") == 0){
//				transfer();
			} else if(command.compare("changeplan") == 0){
//				changeplan();				
			} else {
				printf("Error, unrecognized command\n");
			}
			printf("Enter a command:\n");
			getline(cin, command);
			command = lower(command);
		}

		logout();

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

		createTransaction("01", user, "", 0.0, "");
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