/**
 * @author S. Jack Gibson (100514556),
 * @date 2016-03-08
 * 
 * File input and output of the ATM back end
 */

import java.util.*;
import java.io.*;

class backFiles {
	private String masterAccountsFile, currentAccountsFile;
	private List<String> transactionFile;

	/**
	 * @param strings containing the filenames for input/output
	 * 
	 * Assigns file names for use in input/outputs
	 */
	public backFiles(List<String> trnF, String mAccounts, String cAccounts){
		transactionFile = trnF;
		masterAccountsFile = mAccounts;
		currentAccountsFile = cAccounts;
	}

	/**
	 * @return vector containing the accounts in the masterAccountsFile
	 * 
	 * Loads masterAccountsFile into a vector
	 */
	public List<String> loadAccounts(){
		List<String> accounts = new ArrayList<String>();

		try{
			String line;
			BufferedReader reader = new BufferedReader(new FileReader(masterAccountsFile));
			while((line = reader.readLine()) != null){
				if(!line.equals("00000 END OF FILE          A 00000000 N")){
					accounts.add(line);
				}
			}
		} catch(IOException e){
			System.out.println(e);
		}

		return accounts;
	}

	/**
	 * @return queue containing the transactions in transactionFile
	 * 
	 * Loads the transactionFile into a queue
	 */
	public Queue<String> loadTransactions(){
		Queue<String> transactions = new LinkedList<String>();

		try{
			String line;
			for(int i=0; i<transactionFile.size(); i++){
				BufferedReader reader = new BufferedReader(new FileReader(transactionFile.get(i)));
				while((line = reader.readLine()) != null){
					transactions.add(line);
				}
			}
		} catch(IOException e){
			System.out.println(e);
		}

		return transactions;
	}

	/**
	 * @param a list of bank account info
	 * 
	 * write the account info to the masterAccountsFile
	 */
	public void writeAccounts(List<String> accounts){
		try {
			PrintWriter writer = new PrintWriter(new FileWriter(masterAccountsFile));

			for(int i=0; i<accounts.size(); i++){
				writer.println(accounts.get(i));
			}
			writer.println("00000 END OF FILE          A 00000000 N");
		} catch (IOException e){
			System.out.println("ERROR: Could not print to master bank accounts file.");
		}
	}
}