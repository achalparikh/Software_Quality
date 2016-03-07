#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "iostream"
#include "string"
#include "vector"
#include "files.h"

using namespace std;

class Accounts{
	Files *file;
	/**
	 * Strings containing bank account information
	 */
	vector<string> accounts;

	/**
	 * Store account data in vector
	 */
	void storeAccounts(){
		this->accounts = file->loadAccounts();
	}

  public:
  	/**
  	 * @param files object to be used
	 *
  	 * assigns files object
  	 */
  	Accounts(Files *newFile){file = newFile; storeAccounts();}

  	/**
	 * @param account holder name to be validated
	 * 
	 * Validates account holder name
	 */
	bool validHolder(string name){
		string account;
		for(int i=0; i<this->accounts.size(); i++){
			account = accounts.at(i).substr(6,name.length());
			if(account.compare(name) == 0 && 
				available((i + 1) + "").find("exist") != 0){
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
		for(int i=0; i<this->accounts.size(); i++){
			account = this->accounts.at(i).substr(0,holder.length()+6);
			if(account.substr(6).compare(holder) == 0 && 
				account.substr(0, 5).compare(num) == 0){
				return true;
			} else if(holder.compare("") == 0 && account.substr(0, 5).compare(num) == 0){
				return true;
			}
		}

		return false;
	}

	/**
	 * @param float amount and boolean deposit/transfer to (false for withdraw/transfer from)
	 * 			string name of account holder and string account number
	 */
	bool checkAmount(float amount, bool deposit, string name, string num, bool admin){
		float balance;
		float fee;
		for(int i=0; i<this->accounts.size(); i++){
			if(this->accounts.at(i).substr(6, name.length()).compare(name) == 0 &&
					this->accounts.at(i).substr(0, 5).compare(num) == 0){
				balance = stof(this->accounts.at(i).substr(31, 8));
				if(this->accounts.at(i).substr(39, 1).compare("S")){
					fee = 0.05;
				} else {
					fee = 0.10;
				}
				break;
			}
		}
		if(admin){
			fee = 0;
		}
		if(deposit){
			/**
			 * deposit amount checking
			 */
			if((balance + amount) - fee >= 100000.00){
				return true;
			}
			return false;
		} else {
			/**
			 * withdraw amount checking
			 */
			if((balance - amount) - fee > 0.00){
				return false;
			}
			return true;
		}
	}

	/**
	 * @param account holder name and the initial account balance
	 * @return returns the number of the new account
	 * 
	 * adds a new account to the current accounts vector
	 */
	string newAccount(string name, float val){
		char temp[40];
		string num;
		string accountInfo;
		for(int i=0; i<this->accounts.size(); i++){
			if(this->accounts.at(i).at(39) == 'D'){
				sprintf(temp, "%05d", i + 1);
				num = string(temp);
				sprintf(temp, "%s %s A %07.2f N", 
					num.c_str(), name.c_str(), val);
				accountInfo = string(temp);
				this->accounts.at(i) = accountInfo;
				return num;
			}
		}
		sprintf(temp, "%05d", (int) this->accounts.size() + 1);
		num = string(temp);
		sprintf(temp, "%s %s A %07.2f C", 
			num.c_str(), name.c_str(), val);
		accountInfo = string(temp);
		this->accounts.push_back(accountInfo);
		return num;
	}

	/**
	 * @param number of account to be deleted
	 * 
	 * Marks the account as deleted for future transactions
	 */
	void removeAccount(string num){
		int accountNum = stoi(num);
		this->accounts.at(accountNum-1).at(39) = 'D';
	}

	/**
	 * @param number of account to verify if it is disabled, newly created, or deleted
	 * @return returns string of reason the account can't be used or an empty string if it can
	 *
	 * Checks if the specified account is available for use
	 */
	string available(string num){
		char reason[200];
		int accountNum = stoi(num);
		if(this->accounts.at(accountNum-1).at(39) == 'D'){
			sprintf(reason, "Error, account %s does not currently exist and cannot perform any transactions", num.c_str());
		} else if(this->accounts.at(accountNum-1).at(39) == 'C'){
			sprintf(reason, "Error, account %s cannot perform any transactions for the remainder of the day", num.c_str());
		} else if(this->accounts.at(accountNum-1).at(26) == 'D'){
			sprintf(reason, "Error, account %s is currently disabled and cannot perform any transactions", num.c_str());
		} else {
			return "";
		}
		return string(reason);
	}

	/**
	 * @param string number of the account to swap the plan of
	 * 
	 * Switches Normal plans to Student plans on account provided
	 */
	void switchPlan(string num){
		int accountNum = stoi(num);
		if(this->accounts.at(accountNum-1).at(39) == 'N'){
			this->accounts.at(accountNum-1).at(39) = 'S';
		} else {
			this->accounts.at(accountNum-1).at(39) = 'N';
		}
	}

	void testAccounts(){
		for(int i=0; i<this->accounts.size(); i++){
			printf("%s\n", this->accounts.at(i).c_str());
		}
	}

	/**
	 * @param string number of account to enable/disable and which action it is performing
	 * 
	 * switches account to active or disabled
	 */
	void switchActive(string num, bool enable){
		int accountNum = stoi(num);
		if(enable){
			this->accounts.at(accountNum-1).at(26) = 'A';
		} else {
			this->accounts.at(accountNum-1).at(26) = 'D';
		}
	}
};