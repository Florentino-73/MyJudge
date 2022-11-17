while read rows
do
  ./test10 $rows >> output10.txt
  echo >> output10.txt
done < input.txt