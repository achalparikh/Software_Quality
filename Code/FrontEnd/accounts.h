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
		for(int i=0; i<this->accounts.size(); i++){
			account = this->accounts.at(i).substr(0,holder.length()+6);
			if(account.substr(6).compare(holder) == 0 && 
				account.substr(0, 5).compare(num) == 0){
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
			if(this->accounts.at(i).substr(39, 1).compare("D") == 0){
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
		sprintf(temp, "%s %s A %07.2f N", 
			num.c_str(), name.c_str(), val);
		accountInfo = string(temp);
		this->accounts.push_back(accountInfo);
		return num;
	}

	void removeAccount(string num){
		int accountNum = stoi(num);
		this->accounts.at(accountNum-1).at(39) = 'D';
	}

	void testAccounts(){
		for(int i=0; i<this->accounts.size(); i++){
			printf("%s\n", this->accounts.at(i).c_str());
		}
	}
};