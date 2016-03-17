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

import java.util.*;

class backEnd {
	/**
	 * objects containing the back end's data and file input/output
	 */
	private backData data;
	private backFiles files;

	/**
	 * @param backFiles object
	 * 
	 * Assigns objects provided to local copies for use by backEnd
	 * Calls files to load input data and passes this to the data object
	 */
	public backEnd(backFiles files){
		this.files = files;
		data = new backData(files.loadAccounts(), files.loadTransactions());
	}

	public static void main(String args[]){
		/**
		 * handle file input/and output
		 */
		backFiles files;
		/**
		 * Object which handles transactions
		 */
		backEnd back;

		/**
		 * Read command line arguments into variables
		 */
		String masterAccountsFile, currentAccountsFile;
		List<String> transactionFile = new ArrayList<String>();
		if (args.length > 2) {
			for (int i=2; i<args.length; i++) {
				transactionFile.add(args[i]);
			}
		} else {
			transactionFile.add("transactions.trn");
		}
		if (args.length > 0) {
			masterAccountsFile = args[0];
		} else {
			masterAccountsFile = "masterBankAccounts.txt";
		}
		if (args.length > 1) {
			currentAccountsFile = args[1];
		} else {
			currentAccountsFile = "currectBankAccounts.txt";
		}

		files = new backFiles(transactionFile, masterAccountsFile, currentAccountsFile);
		back = new backEnd(files);
	}

	/**
	 * Performs and verifies transactions
	 */
	private void processTransactions(){
		String user = "";
		List<String> trans;

		while(true){
			trans = data.getTransaction();
			if(trans == null){
				files.writeAccounts(data.getAccounts());
				break;
			} else if(trans.get(0).substring(0,5).equals("ERROR")){
				System.out.println(trans.get(0));
				break;
			}

			int transType = Integer.parseInt(trans.get(0).substring(0,2));

			switch (transType) {
				case 0:
					user = "";
					break;
				case 1:
					//data.withdraw(trans.get(0));
					break;
				case 2:
					//data.withdraw(trans.get(0));
					//data.deposit(trans.get(1));
					break;
				case 3:
					//data.withdraw(trans.get(0));
					break;
				case 4:
					//data.deposit(trans.get(0));
					break;
				case 5:
					//data.create(trans.get(0));
					break;
				case 6:
					// data.delete(trans.get(0));
					break;
				case 7:
					data.enable(trans.get(0), true);
					break;
				case 8:
					data.changeplan(trans.get(0));
					break;
				case 9:
					data.enable(trans.get(0), false);
					break;
				case 10:
					if(trans.get(0).substring(40,41).equals("A")){
						user = "--admin--";
					} else {
						user = trans.get(0).substring(3,24);
					}
					break;
			}
		}
	}
}