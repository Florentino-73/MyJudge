while read rows
do
  ./test11 $rows >> output11.txt
  echo >> output11.txt
done < input.txt