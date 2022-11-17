while read rows
do
  ./test1 $rows >> output1.txt
  echo >> output1.txt
done < input.txt

