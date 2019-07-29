#include<iostream>
#include"Poly.h"

using namespace std;

int main(){
	vector<bool> v1;
	v1.push_back(1);
	v1.push_back(1);
	v1.push_back(1);
	Poly a(v1);
	cout << "a is ";
	a.Print();

	vector<bool> v2;
	v2.push_back(1);
	v2.push_back(1);
	//v2.push_back(0);
	//v2.push_back(1);
	Poly b(v2);
	cout << "b is ";
	b.Print();

	//Poly q,r;
	//a.divide(b,q,r);
	//q.Print();
	//r.Print();

	Poly x;
	Poly y;
	Poly d;
	
	a.gcd(b,x,y,d);
	x.Print();
	y.Print();
	d.Print();
}
