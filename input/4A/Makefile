input:
	@ touch input.txt
	@ g++ -g standard_input.cpp -o input
	@ ./input

output:
	@ g++ -g 48762087.cpp -o test1
	@ sudo ./out1.sh

	@ g++ -g 84822638.cpp -o test2
	@ sudo ./out2.sh

	@ g++ -g 84822639.cpp -o test3
	@ sudo ./out3.sh

	@ g++ -g 101036360.cpp -o test4
	@ sudo ./out4.sh

	@ g++ -g 117364748.cpp -o test5
	@ sudo ./out5.sh
	
	@ g++ -g 127473352.cpp -o test6
	@ sudo ./out6.sh
	
	@ g++ -g 134841308.cpp -o test7
	@ sudo ./out7.sh
	
	@ g++ -g 173077807.cpp -o test8
	@ sudo ./out8.sh

judge:
	@ g++ -g myjudge.cpp -o myjudge
	@ ./myjudge

clean:
	@ rm -rf input
	@ rm -rf test*
	@ rm -rf myjudge

remove:
	@ rm -rf output*