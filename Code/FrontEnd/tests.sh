for t in "Login" "Logout" "deposit" "Withdraw" "paybill" "transfer" "Changeplan" "Create" "Delete" "Enable" "Disable" "Misc"
  do
	echo "Running tests for: $t"
	for i in ../../Tests/Front_End/$t/*.txt
	  do
		echo "${i%.txt}"
		cat "$i" | ./console currentBankAccountsFile transactions.trn > out.out
		diff out.out "${i%.txt}.out"
		diff transactions.trn "${i%.txt}.trn"
		rm out.out
		rm transactions.trn
		touch out.out
		touch transactions.trn
	done
done
rm out.out
rm transactions.trn