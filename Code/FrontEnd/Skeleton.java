import java.util.Scanner;
import java.io.*;

class Skeleton{

	/**
	 * @param name of text file to use as command input 
	 * or nothing (if intended for terminal)
	 * 
	 * Reads input until a valid login is called
	 */
	public static void main(String args[]){
		Scanner login;
		// terminal commands
		login = new Scanner(System.in);
		String input = "";
		Session session;
		System.out.println("Login to start:");
		while(!(input = login.nextLine()).toLowerCase().equals("quit")){
			input = input.toLowerCase();
			if(input.equals("login")){
				session = new Session(login);
			} else {
				System.out.println("ERROR: Not logged in");
			}
			System.out.println("Login to start:");
		}
		return;
	}
}

/**
 * New session is created every Login and deleted on Logout
 */
class Session{
	private boolean admin;
	private String user = "";
	private Scanner commandLine;
	private String command;
	private Scanner bankAccounts;
	private String accountLine;

	/**
	 * @param takes the scanner being used by the program (file input or terminal)
	 *
	 * Login
	 */
	public Session(Scanner login){
		commandLine = login;

		/**
		 * 
		 */
		System.out.println("Enter type of account: \"standard\" or \"admin\"");
		command = commandLine.nextLine().toLowerCase();
		
		// Returns to login if command is unrecognized
		if(!command.equals("admin") && !command.equals("standard")){
			System.out.println("Error, unrecognized command");
			return;
		}
		admin = command.equals("admin");

		if(!admin){
			// Continue standard user login
			System.out.println("Logging in as standard user - enter name:");
			command = commandLine.nextLine();
			// Return to login if invalid user name
			if(!validHolder(command)){
				System.out.println("ERROR: User \"" + 
					command + "\" does not exist. Try again");
				return;
			}

			// Successful standard user login
			System.out.println("You are now logged in as \"" + command + "\"");
			user = command;
		} else {
			// Successful admin login
			System.out.println("You are now logged in as an admin");
		}

		input();

		return;
	}

	/**
	 * @param account holder name to be validated
	 * 
	 * Validates account holder name
	 */
	private boolean validHolder(String name){
		try{
			bankAccounts = new Scanner(new File("currentBankAccountsFile"));

			while(bankAccounts.hasNextLine()){
				accountLine = bankAccounts.nextLine().substring(6,6+name.length());
				if(accountLine.equals(name)){
					bankAccounts.close();
					return true;
				}
			}
		} catch (FileNotFoundException e){
			System.out.println("File not found");
		}

		return false;
	}

	/** 
	 * Reads in commands to perform transactions
	 */
	private void input(){
		System.out.println("Enter a command:");
		while(!(input = login.nextLine()).toLowerCase().equals("logout")){
			System.out.println("Enter a command:");
		}

		return;
	}
}