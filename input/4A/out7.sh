while read rows
do
  ./test7 $rows >> output7.txt
  echo >> output7.txt
done < input.txt