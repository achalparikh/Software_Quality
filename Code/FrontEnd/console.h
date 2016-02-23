#ifndef CONSOLE_H_
#define CONSOLE_H_
#include <stdio.h>
#include <stdlib.h>
#include "iostream"
#include "string"
#include "fstream"
#include "vector"
#endif

using namespace std;

/**
 * @param name of text file to use as command input 
 * or nothing (if intended for terminal)
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
	string trans_str = "";

	/** 
	 * Reads in commands to perform transactions
	 */
	void input();

	/**
	 * @param account holder name to be validated
	 * 
	 * Validates account holder name
	 */
	bool validHolder(string name);

	/**
	 * @param account number and account holder to validate
	 * 
	 * Validates account number matches account holder
	 */
	bool validNumber(string num, string holder);

	/**
	 * @param 5 components of the transaction file lines
	 * 
	 * adds transactions to the session's transaction string (trans_str)
	 */
	void createTransaction(string code, string name, string num, float val, string misc);

	/**
	 * Deposits money into account.
	 */
	void deposit();

	/**
	 * prints trans_str to transaction file
	 */
	void logout();

  public:
	/**
	 * Login to session 
	 */
	void login();
};