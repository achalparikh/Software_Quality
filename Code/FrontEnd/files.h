#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "iostream"
#include "string"
#include "fstream"
#include "vector"

using namespace std;

class Files{
	string fileIn, fileOut;
	string trans_str = "";

  public:
  	Files(string fileIn, string fileOut){this->fileIn = fileIn; this->fileOut = fileOut;}

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

	/**
	 * Prints trans_str to transaction file
	 */
	void writeTransactions(){
		ofstream transfile;
		transfile.open(fileOut, ios_base::app);
		transfile << trans_str;
	}

	/**
	 * @return vector of account information
	 * 
	 * Loads account information into memory
	 */
	vector<string> loadAccounts(){
		/** 
		 * load bank account file to accounts vector
		 */
		vector<string> accounts;
		ifstream bankAccounts(fileIn);
		int i = 0;
		if(bankAccounts.is_open()){
			for(string accountLine; getline(bankAccounts, accountLine); ){
				if(accountLine.substr(0, 5).compare("00000") != 0){
					while(stoi(accountLine.substr(0, 5)) - 1 > i){
						char temp[50];
						sprintf(temp, "%05d                      D 00000.00 D", ++i);
						accounts.push_back(string(temp));
					}
					accounts.push_back(accountLine);
					i++;
				}
			}
		} else {
			printf("Bank accounts file could not be opened.\n");
		}
		return accounts;
	}
};