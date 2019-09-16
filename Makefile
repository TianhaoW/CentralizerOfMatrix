Ftest:
	g++ -o Ftest FFieldTest.cpp 

Mtest:
	g++ -o MTest MTest.cpp Matrix.cpp Poly.cpp
Ptest:
	g++ -o PTest PTest.cpp
gcdtest:
	g++ -o gcdTest Poly.cpp gcdTest.cpp
