while read rows
do
  ./test6 $rows >> output6.txt
  echo >> output6.txt
done < input.txt