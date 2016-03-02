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
	bool checkAmount(float amount, bool deposit, string name, string num){
		float balance;
		if(deposit){
			/**
			 * deposit amount checking
			 */
			for(int i=0; i<this->accounts.size(); i++){
				if(this->accounts.at(i).substr(6, name.length()).compare(name) == 0 &&
					this->accounts.at(i).substr(0, 5).compare(num) == 0){
					balance = stof(this->accounts.at(i).substr(31, 8));
					break;
				}
			}
			if(amount + balance >= 100000.00){
				return false;
			}
			return true;
		} else {
			/**
			 * withdraw amount checking
			 */
			return false;
		}
	}
};