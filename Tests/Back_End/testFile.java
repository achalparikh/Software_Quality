import org.junit.Before;
import org.junit.After;
import org.junit.Test;
import static org.junit.Assert.*;
import java.io.*;
import java.util.List;
import java.util.ArrayList;

public class testFile {
	public final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
	public final ByteArrayOutputStream errContent = new ByteArrayOutputStream();

	public List<String> trnFiles = new ArrayList<String>();
	public backFiles files;
	public backData data;

	public testFile(){
		trnFiles.add("../../Code/BackEnd/transactions.trn");
	}

	@Before
	public void setUpStreams() {
		testFile tests = new testFile();
		files = new backFiles(trnFiles,"../../Code/BackEnd/masterBankAccountsFile", 
			"../../Code/BackEnd/currentBankAccountsFile");
		data = new backData(files.loadAccounts(), files.loadTransactions());
	}

	@Test
	public void testLoadAccounts() {
		assertFalse(files.loadAccounts() == null);
	}

	@Test
	public void testLoadTransactions() {
		assertFalse(files.loadTransactions().size() == 0);
	}

	@Test
	public void testFindT() {
		assertTrue(data.find("00                      00001 00000000   ") != -1);
	}

	@Test
	public void testFindF() {
		assertFalse(data.find("00                      00000 00000000   ") != -1);
	}

	@Test
	public void testEnable(){
		data.enable("00                      00014 00000000   ", true);
		assertTrue(data.account("00                      00014 00000000   "
			).substring(27,28).equals("A"));
	}

	@Test
	public void testDisable(){
		data.enable("00                      00012 00000000   ", false);
		assertTrue(data.account("00                      00012 00000000   "
			).substring(27,28).equals("D"));
	}

	@Test
	public void testChangeplanS(){
		data.changeplan("00                      00012 00000000   ");
		assertTrue(data.account("00                      00012 00000000   "
			).substring(38,39).equals("S"));
	}

	@Test
	public void testChangeplanN(){
		data.changeplan("00                      00011 00000000   ");
		assertTrue(data.account("00                      00011 00000000   "
			).substring(38,39).equals("N"));
	}
	
	
	//deposit tests 
		@Test
		public void testDepositValid() {
			String trans = "00                      00001 00001.00   ";
			String result = backData.deposit(trans), expected = null;
			assertEquals (expected, result);
		}
		
		@Test
		public void testDepositInvalid() {
			String trans = "00                      00020 00001.00   ";
			String result = backData.deposit(trans), expected = "ERROR: Account number 00020 not found.";
			assertEquals (expected, result);
		}
		
		//withdraw tests
		@Test
		public void testWithdrawValid () {
			String trans = "00                      00001 00001.00   ";
			String result = backData.withdraw(trans), expected = null;
			assertEquals (expected, result);
		}
		
		public void testWithdrawInvalid() {
			String trans = "00                      00020 00001.00   ";
			String result = backData.withdraw(trans), expected = "ERROR: Account number 00020 not found";
			assertEquals (expected, result);
		}
}