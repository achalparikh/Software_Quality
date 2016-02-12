for file in ./* ; do 
	if cmp -s $file $1 ; then
		echo "F and $file are the same!" 
	else 
		diff $1 $file >> diffs.txt
	fi
done