while read rows
do
  ./test3 $rows >> output3.txt
done < input.txt