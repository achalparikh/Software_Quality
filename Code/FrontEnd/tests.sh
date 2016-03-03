for t in "Login" "Logout" "deposit" "Withdraw" "paybill" "transfer" "Changeplan" "Create" "Delete" "Enable" "Disable" "Misc"
  do
	echo "Running tests for: $t"
	for i in ../../Tests/Front_End/$t/*.txt
	  do
		cat "$i" | ./console > out.out
		echo "${i%.txt}"
		diff out.out "${i%.txt}.out"
		diff transactions.trn "${i%.txt}.trn"
		rm out.out
		rm transactions.trn
		touch out.out
		touch transactions.trn
	done
done