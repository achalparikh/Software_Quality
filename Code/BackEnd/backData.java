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
	 * @return returns bank accounts
	 */
	public List<String> getAccounts(){return accounts;}
}