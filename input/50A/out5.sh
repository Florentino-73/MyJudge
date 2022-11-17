while read rows
do
  ./test5 $rows >> output5.txt
  echo >> output5.txt
done < input.txt