/**
 * @author S. Jack Gibson (100514556),
 * @date 2016-03-08
 * 
 * File input and output of the ATM back end
 */

import java.util.*;

class backFiles {
	private String transactionFile, masterAccountsFile, currentAccountsFile;

	/**
	 * @param strings containing the filenames for input/output
	 * 
	 * Assigns file names for use in input/outputs
	 */
	public backFiles(String trnF, String mAccounts, String cAccounts){
		transactionFile = trnF;
		masterAccountsFile = mAccounts;
		currentAccountsFile = cAccounts;
	}

	/**
	 * @return vector containing the accounts in the masterAccountsFile
	 * 
	 * Loads masterAccountsFile into a vector
	 */
	public Vector loadAccounts(){
		Vector accounts = new Vector();
		return accounts;
	}

	/**
	 * @return _____ containing the transactions in transactionFile
	 * 
	 * Loads the transactionFile into a _______
	 */
	//public ________ loadTransactions(){}
}