while read rows
do
  ./test2 $rows >> output2.txt
done < input.txt

