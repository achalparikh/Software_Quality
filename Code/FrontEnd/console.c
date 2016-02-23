/**
 * Front end terminal
 */

#include <stdio.h>
#include <stdlib.h>
#include "iostream"
#include "string"
#include "fstream"
#include "vector"

using namespace std;

vector<string> accounts;

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
		/**
		 * Transaction code is only ever going to be length 2
		 */
		trans_str += code + " ";
		
		/**
		 * name will be less than or equal to 20 characters
		 */
		trans_str += name;
		for (int i=name.length(); i<=21; i++){
			trans_str += " ";
		}

		/**
		 * num is a string of length 5
		 */
		trans_str += num + " ";

		/**
		 * val is a float
		 * convert to string of length 8
		 * or fill with 8 "0"s
		 */
		if(code.compare("06") == 0 || code.compare("07") == 0 || 
			code.compare("08") == 0 || code.compare("09") == 0){
			trans_str += "00000000 ";
		} else {
			char str_c[8];
			sprintf(str_c, "%07.2f", val);
			string str(str_c);
			trans_str += str + " ";
		}

		/**
		 * misc is a string of length 2
		 */
		trans_str += misc + "\n";

		return;
	}

	/**
	 * @param account holder name to be validated
	 * 
	 * Validates account holder name
	 */
	bool validHolder(string name){
		string account;
		for(int i=0; i<accounts.size(); i++){
			account = accounts.at(i).substr(6,name.length());
			if(account.compare(name) == 0){
				return true;
			}
		}

		return false;
	}

	/**
	 * @param account number and account holder to validate
	 * 
	 * Validates account number matches account holder
	 */
	bool validNumber(string num, string holder){
		string account;
		for(int i=0; i<accounts.size(); i++){
			account = accounts.at(i).substr(0,holder.length()+6);
			if(account.substr(6).compare(holder) == 0 && 
				account.substr(0, 5).compare(num) == 0){
				return true;
			}
		}

		return false;
	}

	/**
	 * Deposits money into account.
	 */
	void deposit(){
		float val, balance;
		string num, str_val, name;
		/**
		 * admin users have extra information they must provide
		 */
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
			/**
			 * standard users can only deposit into their own accounts
			 */
			name = user;
			printf("COMMAND: deposit - enter account number:\n");
		}
		/**
		 * account number
		 */
		getline(cin, num);
		if(!validNumber(num, name)){
			printf("ERROR: Account number \"%s\" is not valid. Try again\n", num.c_str());
			return;
		}
		printf("Depositing to \"%s\" - enter amount:\n", num.c_str());
		/**
		 * amount of deposit
		 */
		getline(cin, str_val);
		val = stof(str_val);
		/**
		 * maximum deposit
		 */
		for(int i=0; i<accounts.size(); i++){
			if(accounts.at(i).substr(6, name.length()).compare(name) == 0 &&
				accounts.at(i).substr(0, 5).compare(num) == 0){
				balance = stof(accounts.at(i).substr(31, 8));
				break;
			}
		}
		if(val + balance >= 100000.00){
			printf("ERROR: Maximum balance exceeded. Try again\n");
			return;
		}

		/**
		 * create successful transaction code
		 */
		createTransaction("04", name, num, val, "  ");

		return;
	}
 
	/**
	 * prints trans_str to transaction file
	 */
	void logout(){
		createTransaction("00", "", "00000", 0.0, "  ");

		ofstream transfile;
		transfile.open("transactions.trn", ios_base::app);
		transfile << trans_str;

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
/**
 *				withdraw();
 */
			} else if(command.compare("create") == 0){
/**
 *				create();
 */
			} else if(command.compare("delete") == 0){
/**
 *				delete();
 */
			} else if(command.compare("enable") == 0){
/**
 *				enable();
 */
			} else if(command.compare("disable") == 0){
/**
 *				disable();
 */
			} else if(command.compare("paybill") == 0){
/**
 *				paybill();
 */
			} else if(command.compare("transfer") == 0){
/**
 *				transfer();
 */
			} else if(command.compare("changeplan") == 0){
/**
 *				changeplan();				
 */
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
		
		/**
		 * Returns to login if command is unrecognized
		 */
		if(command.compare("admin") != 0 && command.compare("standard") != 0){
			printf("Error, unrecognized command\n");
			return;
		}
		admin = command.compare("admin") == 0;

		if(!admin){
			/**
			 * Continue standard user login
			 */
			printf("Logging in as standard user - enter name:\n");
			getline(cin, command);
			/**
			 * Return to login if invalid user name
			 */
			if(!validHolder(command)){
				printf("ERROR: User \"%s\" does not exist. Try again\n", command.c_str());
				return;
			}

			/**
			 * Successful standard user login
			 */
			printf("You are now logged in as \"%s\"\n", command.c_str());
			user = command;
		} else {
			/**
			 * Successful admin login
			 */
			printf("You are now logged in as an admin\n");
		}

		if(admin){
			createTransaction("10", user, "00000", 0.0, "A ");
		} else {
			createTransaction("10", user, "00000", 0.0, "S ");
		}
		input();

		return;
	}
};

/**
 * @param name of text file to use as command input 
 * or nothing (if intended for terminal)
 * 
 * Loads the accounts into memory
 * Reads input until a valid login is called
 */
int main(int argc, const char* argv[]){
	ifstream bankAccounts("currentBankAccountsFile");
	if(bankAccounts.is_open()){
		for(string accountLine; getline(bankAccounts, accountLine); ){
			accounts.push_back(accountLine);
		}
	} else {
		printf("Bank accounts file could not be opened.\n");
		return 0;
	}

	string input = "";
	printf("Login to start:\n");
	getline(cin, input);
	input = lower(input);
	/**
	 * Console terminates when "quit" is entered
	 */
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