/**
 * @author S. Jack Gibson (100514556),
 * @date 2016-03-08
 * 
 * Data handling for ATM back end
 */

import java.util.*;

class backData {
	List<String> accounts;
	Queue<String> transactions;

	/**
	 * @param Vector of accounts and a queue of the transactions (strings)
	 * 
	 * Accepts new Data
	 */
	public backData(List<String> accounts, Queue<String> transactions){
		this.accounts = accounts;
		this.transactions = transactions;
	}

	/**
	 * @return returns list of transaction(s)
	 * 
	 * retrieves transactions for processing
	 */
	public List<String> getTransaction(){
		List<String> trans = new ArrayList<String>();
		String newTrans = transactions.poll();
		if(newTrans == null){
			return null;
		}
		trans.add(newTrans);
		if(trans.get(0).substring(0,2).equals("02")){
			newTrans = transactions.peek();
			if(newTrans != null && newTrans.substring(0,2).equals("02")){
				trans.add(transactions.poll());
			} else {
				trans = new ArrayList<String>();
				trans.add("ERROR: Transfer started but not finished.");
				return trans;
			}
		}
		return trans;
	}

	/**
	 * @param string of transaction log
	 * @return integer >=0 of account number or -1 if not found
	 * 
	 * finds account in accounts list
	 */
	public int find(String trans){
		for(int i=0; i<accounts.size(); i++){
			if(accounts.get(i).substring(0,5).equals(trans.substring(24,29))){
				return i;
			}
		}
		return -1;
	}

	/**
	 * @param string of transaction log and boolean enable (disable on false)
	 * 
	 * enables or disables account
	 */
	public String enable(String trans,boolean enable){
		int accountNum = find(trans);
		if(accountNum > 0){
			if(enable){
				accounts.get(accountNum).substring() = "A";
			} else {
				accounts.get(accountNum).substring() = "D";
			}
			return null;
		} else {
			return "ERROR: Account number " + trans.substring(24,29) + " not found.";
		}
	}

	/**
	 * @param string of transaction log
	 * 
	 * switches account plan between Student and Normal
	 */
	public String changeplan(String trans){
		int accountNum = find(trans);
		if(accountNum > 0){
			if(accounts(accountNum).substring(38,39).equals("N")){
				accounts(accountNum).substring(38,39) = "S";
			} else {
				accounts(accountNum).substring(38,39) = "N";
			}
			return null;
		} else {
			return "ERROR: Account number " + trans.substring(24,29) + " not found.";
		}
	}

	/**
	 * @return returns bank accounts
	 */
	public List<String> getAccounts(){return accounts;}
}