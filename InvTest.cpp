#include "Matrix.h"
#include "Poly.h"
#include "FField.h"
#include <vector>
#include <iostream>

using namespace std;

int main() {
	const int mod = 5;
	
	vector<vector <FField<mod> > > entry;

	vector<FField<mod> > vec1;
	vec1.push_back(FField<mod> (1));
	vec1.push_back(FField<mod> (0));
	vec1.push_back(FField<mod> (0));

	vector<FField<mod> > vec2;
	vec2.push_back(FField<mod> (0));
	vec2.push_back(FField<mod> (0));
	vec2.push_back(FField<mod> (-1));

	vector<FField<mod> > vec3;
	vec3.push_back(FField<mod> (0));
	vec3.push_back(FField<mod> (1));
	vec3.push_back(FField<mod> (2));

	entry.push_back(vec1);
	entry.push_back(vec2);
	entry.push_back(vec3);

	Matrix<FField<mod> > A(entry);
	vector<Poly <FField<mod> > > inv;
	Matrix<FField<mod> > T;

	A.Print();
	cout << "Finding the Invariant Factor: \n";
	T = A.Invf(inv);
	for (int i = 0; i < inv.size(); i++) {
		inv.at(i).Print();
		cout << "\n";
	}

	cout << "Printing the transformation matrix: \n";

	T.Print();


	cout << "Testing Companian matrix\n";
	vector<FField<mod> > vec4;
	vec4.push_back(FField<mod> (1));
	vec4.push_back(FField<mod> (3));
	vec4.push_back(FField<mod> (2));
	vec4.push_back(FField<mod> (1));
	Poly<FField<mod> > f(vec4);
	Matrix<FField<mod> > Cf(f);
	Cf.Print();

}
