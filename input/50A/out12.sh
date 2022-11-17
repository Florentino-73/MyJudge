while read rows
do
  ./test12 $rows >> output12.txt
  echo >> output12.txt
done < input.txt