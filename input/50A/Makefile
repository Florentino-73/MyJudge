input:
	@ touch input.txt
	@ g++ -g standard_input.cpp -o input
	@ ./input

output:
	@ g++ -g 21508887.cpp -o test1
	@ sudo ./out1.sh

	@ g++ -g 21508898.cpp -o test2
	@ sudo ./out2.sh

	@ g++ -g 21715601.cpp -o test3
	@ sudo ./out3.sh

	@ g++ -g 29019948.cpp -o test4
	@ sudo ./out4.sh

	@ g++ -g 30534178.cpp -o test5
	@ sudo ./out5.sh
	
	@ g++ -g 31034693.cpp -o test6
	@ sudo ./out6.sh
	
	@ g++ -g 33794240.cpp -o test7
	@ sudo ./out7.sh
	
	@ g++ -g 36641065.cpp -o test8
	@ sudo ./out8.sh

	@ g++ -g 45851050.cpp -o test9
	@ sudo ./out9.sh

	@ g++ -g 138805414.cpp -o test10
	@ sudo ./out10.sh

	@ g++ -g 142890373.cpp -o test11
	@ sudo ./out11.sh

	@ g++ -g 164831265.cpp -o test12
	@ sudo ./out12.sh

judge:
	@ g++ -g myjudge.cpp -o myjudge
	@ ./myjudge

clean:
	@ rm -rf input
	@ rm -rf test*
	@ rm -rf myjudge

remove:
	@ rm -rf output*