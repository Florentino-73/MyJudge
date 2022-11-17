while read rows
do
  ./test9 $rows >> output9.txt
  echo >> output9.txt
done < input.txt