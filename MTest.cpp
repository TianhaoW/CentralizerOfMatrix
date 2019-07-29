#include<iostream>
#include "Matrix.h"
#include "Poly.h"
#include<vector>

using namespace std;

int main(){
	cout<<"Constructing Default Matrix\n";
	Matrix m1;
	m1.Print();

	cout<<"Constructing Default Matrix with size 2\n";
	Matrix m2(2);
	m2.Print();

	vector<bool> r1;
	vector<bool> r2;
	r1.push_back(1);
	r1.push_back(1);
	r2.push_back(1);
	r2.push_back(1);
	vector<vector<bool> > m;
	m.push_back(r1);
	m.push_back(r2);

	Matrix m3(m);
	cout<<"Contructing the Identity Matrix\n";
	m3.Print();

	Matrix m6(m3);
	m6.setEntry(1,1,0);
	cout<<"Another Matrix\n";
	m6.Print();

	Matrix m4(m6.add(m3));
	cout<<"Addint the second matrix to the first Matrix \n";
	m4.Print();
	
	Matrix m5(m6.multiply(m3));
	cout<<"Multiplying the second matrix with the third Matrix \n";
	m5.Print();

	vector<bool> v;
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);	
	Poly p(v);
	p.Print();
	Matrix m7(v);
	m7.Print();

	Matrix m8(m7.multiply(m7));
	m8.Print();

	Matrix m10(m7.exp(2));
	Matrix m11(m7.exp(3));

	m10.Print();
	m11.Print();
}
