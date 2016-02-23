/**
 * Front end terminal takes command line input to perform transactions
 * Outputs transaction logs to the transaction.trn file
 */

#include "console.h"

/**
 * Strings containing bank account information
 */
vector<string> accounts;

int main(int argc, const char* argv[]){
	/** 
	 * load bank account file to accounts vector
	 */
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

string lower(string str){
	for (int i=0; i<str.length(); i++){
		str.at(i) = tolower(str.at(i));
	}
	return str;
}

void Session::input(){
	printf("Enter a command:\n");
	getline(cin, command);
	command = lower(command);
	while(command.compare("logout") != 0){
		if(command.compare("deposit") == 0){
			deposit();
		} else if(command.compare("withdraw") == 0){
/**
 *			withdraw();
 */
		} else if(command.compare("create") == 0){
/**
 *			create();
 */
		} else if(command.compare("delete") == 0){
/**
 *			delete();
 */
		} else if(command.compare("enable") == 0){
/**
 *			enable();
 */
		} else if(command.compare("disable") == 0){
/**
 *			disable();
 */
		} else if(command.compare("paybill") == 0){
/**
 *			paybill();
 */
		} else if(command.compare("transfer") == 0){
/**
 *			transfer();
 */
		} else if(command.compare("changeplan") == 0){
/**
 *			changeplan();
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

bool Session::validHolder(string name){
	string account;
	for(int i=0; i<accounts.size(); i++){
		account = accounts.at(i).substr(6,name.length());
		if(account.compare(name) == 0){
			return true;
		}
	}

	return false;
}

bool Session::validNumber(string num, string holder){
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

void Session::createTransaction(string code, string name, string num, float val, string misc){
	/**
	 * Transaction code is only ever going to be length 2
	 */
	trans_str += code + " ";
	
	/**
	 * name will be less than or equal to 20 characters
	 */
	trans_str += name;
	for (int i=name.length(); i<=20; i++){
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

void Session::deposit(){
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

void Session::withdraw(){}

void Session::create(){
	if(admin){} else {
		printf("Error, standard users cannot use the 'create' transaction\n");
	}
}

void Session::delete(){
	if(admin){} else {
		printf("Error, standard users cannot use the 'delete' transaction\n");
	}
}

void Session::enable(){
	if(admin){} else {
		printf("Error, standard users cannot use the 'enable' transaction\n");
	}
}

void Session::disable(){
	if(admin){} else {
		printf("Error, standard users cannot use the 'disable' transaction\n");
	}
}

void Session::paybill(){}

void Session::transfer(){}

void Session::changeplan(){
	if(admin){} else {
		printf("Error, standard users cannot use the 'changeplan' transaction\n");
	}
}
 
void Session::logout(){
	createTransaction("00", "", "00000", 0.0, "  ");

	ofstream transfile;
	transfile.open("transactions.trn", ios_base::app);
	transfile << trans_str;

	return;
}

void Session::login(){
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
		this->user = command;
	} else {
		/**
		 * Successful admin login
		 */
		printf("You are now logged in as an admin\n");
	}

	if(admin){
		createTransaction("10", this->user, "00000", 0.0, "A ");
	} else {
		createTransaction("10", this->user, "00000", 0.0, "S ");
	}
	input();

	return;
}