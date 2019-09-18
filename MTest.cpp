#include<iostream>
#include "Matrix.h"
#include "Poly.h"
#include "FField.h"
#include<vector>

using namespace std;

int main(){
	const int mod = 2;

	/*
	cout<<"Constructing Default Matrix\n";
	Matrix<FField<mod> > m1;
	m1.Print();

	cout<<"Constructing Default Matrix with size 2\n";
	Matrix<FField<mod> > m2(2);
	m2.Print();

	cout << "Constructing Matrix from given double array\n";
	vector< vector<FField<mod> > > ent;
	vector<FField<mod> > vec1;
	vec1.push_back(FField<mod>(2));
	vec1.push_back(FField<mod>(1));
	vec1.push_back(FField<mod>(5));	
	vector<FField<mod> > vec2;
	vec2.push_back(FField<mod>(1));
	vec2.push_back(FField<mod>(2));
	vec2.push_back(FField<mod>(3));
	vector<FField<mod> > vec3;
	vec3.push_back(FField<mod>(2));
	vec3.push_back(FField<mod>(3));
	vec3.push_back(FField<mod>(11));
	ent.push_back(vec1);
	ent.push_back(vec2);
	ent.push_back(vec3);
	Matrix<FField<mod> > m3(ent);
	m3.Print();

	cout << "m3+m3 = \n";
	Matrix<FField<mod> > m4;
	m4 = m3+m3;
	m4.Print();

	cout << "m3*m3 = \n";
	Matrix<FField<mod> > m5;
	m5 = m3*m3;
	m5.Print();

	*/

	cout << "Constructing polynomial Matrix from given double array\n";
	vector< vector< Poly<FField<mod> > > > ent2;
	vector<Poly< FField<mod> > > vec4;

	vector<FField<mod> >v11;
	v11.push_back(FField<mod> (-2));
	v11.push_back(FField<mod> (1));
	Poly<FField<mod> > p11(v11);
	vec4.push_back(v11);
	vec4.push_back(Poly< FField<mod> >(0, FField<mod>(-1)));
	vec4.push_back(Poly< FField<mod> >(0, FField<mod>(0)));	
	vector<Poly< FField<mod> > >vec5;
	vec5.push_back(Poly< FField<mod> >(0, FField<mod>(-1)));
	vector<FField<mod> >v22;
	v22.push_back(FField<mod> (-2));
	v22.push_back(FField<mod> (1));
	Poly<FField<mod> > p22(v22);
	vec5.push_back(v22);
	vec5.push_back(Poly< FField<mod> >(0, FField<mod>(-3)));
	vector<Poly< FField<mod> > >vec6;
	vec6.push_back(Poly< FField<mod> >(0, FField<mod>(-2)));
	vec6.push_back(Poly< FField<mod> >(0, FField<mod>(-3)));
	vector<FField<mod> >v33;
	v33.push_back(FField<mod> (-1));
	v33.push_back(FField<mod> (1));
	Poly<FField<mod> > p33(v33);
	vec6.push_back(v33);
	ent2.push_back(vec4);
	ent2.push_back(vec5);
	ent2.push_back(vec6);
	Matrix<Poly<FField<mod> > > m6(ent2);
	m6.Print();

	cout << "Runging the Simith Normal Form Algorithm\n";	
	Matrix<Poly<FField<mod> > > L(3);
	Matrix<Poly<FField<mod> > > R(3);

	m6.SNF(L,R);
}

