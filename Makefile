Ftest:
	g++ -o Ftest FFieldTest.cpp 
Mtest:
	g++ -o MTest MTest.cpp 
Ptest:
	g++ -o PTest PTest.cpp
clean:
	rm Ftest MTest PTest
