/**
 * @author S. Jack Gibson (100514556),
 * @date 2016-03-08
 *
 * @arguments takes 3 (optional) file names as arguments
 * 		input transactions file, master bank accounts, and current bank accounts
 * @output outputs new master/current bank accounts files
 * 
 * Main functionality of ATM back end
 */

class backEnd {
	backData data;
	backFiles files;

	/**
	 * @param backData and backFiles objects
	 * 
	 * Assigns objects provided to local copies for use by backEnd
	 * Calls files to load input data and passes this to the data object
	 */
	public backEnd(backData data, backFiles files){
		this.data = data;
		this.files = files;
	}

	public static void main(String args[]){
		/**
		 * handle file input/and output
		 */
		backFiles files;
		/**
		 * store and organize data used by the back end
		 */
		backData data = new backData();
		/**
		 * Object which handles transactions
		 */
		backEnd back;

		/**
		 * Read command line arguments into variables
		 */
		String transactionFile, masterAccountsFile, currentAccountsFile;
		if (args.length > 0) {
			transactionFile = args[0];
		} else {
			transactionFile = "transactions.trn";
		}
		if (args.length > 1) {
			masterAccountsFile = args[1];
		} else {
			masterAccountsFile = "masterBankAccounts.txt";
		}
		if (args.length > 2) {
			currentAccountsFile = args[2];
		} else {
			currentAccountsFile = "currectBankAccounts.txt";
		}

		files = new backFiles(transactionFile, masterAccountsFile, currentAccountsFile);
		back = new backEnd(data, files);
	}
}