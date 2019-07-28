#include<iostream>
#include "Matrix.h"
#include<vector>

using namespace std;

int main(){
	cout<<"Constructing Default Matrix\n";
	Matrix m1;
	m1.Print();

	cout<<"Constructing Default Matrix with size 3\n";
	Matrix m2(3);
	m2.Print();

	vector<bool> r1;
	vector<bool> r2;
	r1.push_back(1);
	r1.push_back(0);
	r2.push_back(0);
	r2.push_back(1);
	
	vector<vector<bool> > m;
	m.push_back(r1);
	m.push_back(r2);

	Matrix m3(m);
	cout<<"Contructing the Identity Matrix\n";
	m3.Print();
	
}
