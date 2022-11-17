while read rows
do
  ./test8 $rows >> output8.txt
  echo >> output8.txt
done < input.txt