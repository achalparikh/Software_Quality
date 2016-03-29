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
		trnFiles.add("transactions.trn");
	}

	@Before
	public void setUpStreams() {
		testFile tests = new testFile();
		files = new backFiles(trnFiles,"masterBankAccountsFile", "currentBankAccountsFile");
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
	public void testFind() {
		assertFalse(data.find("00                      00001 00000000   ") == -1);
	}
}