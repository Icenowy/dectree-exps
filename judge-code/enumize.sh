#$1: file
#$2: column count
#assume input data have a id column

cat $1 | sed 1d > $1-nohead
lastcol=$(expr $2 + 1)
for num in `seq 2 $lastcol`
do
	cat $1-nohead | awk '{print $'"$num"';}' > $1-nohead-$num
	cat $1-nohead-$num | sort | uniq > $1-nohead-$num-items
	cp $1-nohead-$num $1-nohead-$num-enumized
	cat /dev/null > $1-$num-table
	i=0
	for item in $(cat $1-nohead-$num-items)
	do
		sed -i 's/^'$item'$/'$i'/g' $1-nohead-$num-enumized
		i=$(expr $i + 1)
		echo "$i $item" >> $1-$num-table
	done
done


