while read rows
do
  ./test4 $rows >> output4.txt
  echo >> output4.txt
done < input.txt