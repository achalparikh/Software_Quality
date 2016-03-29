/**
 * @author S. Jack Gibson (100514556), @author Achal Parikh (100520618)
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

	public String account(String num){return accounts.get(find(num));}

	/**
	 * @param string of transaction log
	 * @return string containing any errors that occur
	 * 
	 * create new account
	 */
	public String create(String trans){
		int last = Integer.parseInt(accounts.get(0).substring(0,5));
		for(int i=1; i<accounts.size(); i++){
			int current = Integer.parseInt(accounts.get(i).substring(0,5));
			if(current - last > 1){
				accounts.add(accounts.get(accounts.size()-1));
				for(int j=accounts.size()-2; j>i; j++){
					accounts.set(j, accounts.get(j-1));
				}
				accounts.set(i, String.format("%5d %s A %s N", last+1, trans.substring(3, 23), trans.substring(30,38)));
				return null;
			}
		}
		accounts.add(String.format("%5d %s A %s N", last+1, trans.substring(3, 23), trans.substring(30,38)));
		return null;
	}

	/**
	 * @param string of transaction log
	 * @return string containing any errors that occur
	 * 
	 * deletes account
	 */
	public String delete(String trans){
		int accountNum = find(trans);
		if(accountNum >= 0){
			accounts.remove(accounts.get(accounts.size()-1));
			return null;
		} else {
			return "ERROR: Account number " + trans.substring(24,29) + " not found.";
		}
	}

	/**
	 * @param string of transaction log and boolean enable (disable on false)
	 * @return string containing any errors that occur
	 * 
	 * enables or disables account
	 */
	public String enable(String trans,boolean enable){
		int accountNum = find(trans);
		if(accountNum >= 0){
			if(enable){
				String tmp = accounts.get(accountNum);
				accounts.set(accountNum, tmp.substring(0,27) + "A" + tmp.substring(28));
			} else {
				String tmp = accounts.get(accountNum);
				accounts.set(accountNum, tmp.substring(0,27) + "D" + tmp.substring(28));
			}
			return null;
		} else {
			return "ERROR: Account number " + trans.substring(24,29) + " not found.";
		}
	}

	/**
	 * @param string of transaction log
	 * @return string containing any errors that occur
	 * 
	 * switches account plan between Student and Normal
	 */
	public String changeplan(String trans){
		int accountNum = find(trans);
		if(accountNum >= 0){
			if(accounts.get(accountNum).substring(38,39).equals("N")){
				String tmp = accounts.get(accountNum);
				accounts.set(accountNum, tmp.substring(0,38) + "S" + tmp.substring(38));
			} else {
				String tmp = accounts.get(accountNum);
				accounts.set(accountNum, tmp.substring(0,38) + "N" + tmp.substring(38));
			}
			return null;
		} else {
			return "ERROR: Account number " + trans.substring(24,29) + " not found.";
		}
	}
	
	/**
	 * @param string of transaction log 
	 **invalid deposit taken care of in front end*
	 */
	public String deposit (String trans)
	{
		int accountNum = find(trans);
		double balance, deposit;
		String newBal = "";
		if (accountNum >= 0)
		{
			balance = Double.parseDouble(accounts.get(accountNum).substring(30, 37));
			deposit = Double.parseDouble(trans.substring(31, 38));
			balance += deposit;
			newBal = "" + balance;
			while (newBal.length() < 8)
			{
				newBal = "0" + newBal;
			}
			String tmp = accounts.get(accountNum);
			accounts.set(accountNum, tmp.substring(0,30) + newBal + tmp.substring(38));
			return null;
		}
		else 
			return "ERROR: Account number " + trans.substring(25,29) + " not found.";
	}
	
	/**
	 * @param string of transaction log 
	 **invalid withdraw taken care of in front end*
	 */
	public String withdraw (String trans)
	{
		int accountNum = find(trans);
		double balance, withdraw;
		String newBal = "";
		if (accountNum >= 0)
		{
			balance = Double.parseDouble(accounts.get(accountNum).substring(30,37));
			withdraw = Double.parseDouble(trans.substring(31, 38));
			balance -= withdraw;
			newBal = "" + newBal;
			while (newBal.length() < 8)
			{
				newBal = "0" + newBal;
			}
			String tmp = accounts.get(accountNum);
			accounts.set(accountNum, tmp.substring(0, 30) + newBal + tmp.substring(38));
			return null;
		}
		else 
			return "ERROR: Account number " + trans.substring(25,29) + " not found.";
			
	}

	/**
	 * @return returns bank accounts
	 */
	public List<String> getAccounts(){return accounts;}
	
}