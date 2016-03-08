/**
 * @author S. Jack Gibson (100514556),
 * @date 2016-03-08
 * 
 * File input and output of the ATM back end
 */

class backFiles {
	String transactionFile, masterAccountsFile, currentAccountsFile;

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
}