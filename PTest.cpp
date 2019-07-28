#include "Poly.h"
#include <iostream>
#include <vector>

using namespace std;

int main(){
	Poly p1;
	cout << "Constructing the default polynomial \n";
	p1.Print();

	vector<bool> v;
	v.push_back(0);
	v.push_back(0);
	cout << "Checking construct the zero polynomial \n";
	Poly p2(v);
	p2.Print();

	vector<bool> v2;
	v2.push_back(1);
	v2.push_back(0);
	v2.push_back(1);
	cout << "Constructing another polynomial \n";
	Poly p3(v2);
	p3.Print();

	vector<bool> v3;
	v3.push_back(0);
	v3.push_back(1);
	v3.push_back(0);
	v3.push_back(1);
	v3.push_back(0);
	cout << "Another one\n";
	Poly p4(v3);
	p4.Print();

	Poly p5(p3.add(p4));
	cout << "Their sum \n";
	p5.Print();
	
	Poly p6(p3.multiply(p4));
	cout << "Their product \n";
	p6.Print();


}
