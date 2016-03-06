#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "iostream"
#include "string"
#include "vector"
#include "accounts.h"
#include "files.h"

using namespace std;

/**
 * @param name of bank accounts file and name of transaction file
 * 
 * Loads the accounts into memory
 * Reads input until a valid login is called
 */
int main(int argc, const char* argv[]);

/**
 * @param takes the string to be converted to lowercase
 * @return returns the lowercase string
 * 
 * Converts a string to lowercase
 */
string lower(string str);

/**
 * New session is created every Login and deleted on Logout
 */
class Session{
	bool admin;
	string user;
	string command;
	Files *file;
	Accounts *account;
	string payeeList[] = {"EC","CQ","TV"};

	/**
	 * handles standard input for transactions
	 */
	string standardInput();

	/** 
	 * Reads in commands to perform transactions
	 */
	void input();

	/**
	 * Deposits money into account.
	 */
	void deposit();

	/**
	 * Withdraws money from account
	 */
	void withdraw();

	/**
	 * Create new account which can't be used until next day
	 * Admin only
	 */
	void create();

	/**
	 * Deletes account
	 * Admin only
	 */
	void deleteAccount();

	/**
	 * Enables disabled account
	 * Admin only
	 */
	void enable();

	/**
	 * Disables account
	 * Admin only
	 */
	void disable();

	/**
	 * Pays bill
	 */
	void paybill();

	/**
	 * Transfer money to another account
	 */
	void transfer();

	/**
	 * Change account plan between student and normal
	 * Admin only
	 */
	void changeplan();

	/**
	 * Leaves current session
	 */
	void logout();

  public:
  	Session(Accounts *newAccount, Files *newFile){account = newAccount; file = newFile;}

	/**
	 * Login to session 
	 */
	void login();
};