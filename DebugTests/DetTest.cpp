#include "Matrix.h"
#include "FField.h"
#include "Poly.h"
#include <iostream>
#include <vector>

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

	Matrix<FField<mod> > min;

	cout << "Printing the orginal Matrix\n";
	A.Print();

	cout << "Printing the minor\n";

	min = A.mminor(1,2);
	min.Print();

	FField<mod> d = A.det();
	d.Print();
	cout << "\n";

	cout << "Finding the inverse\n";
	Matrix<FField<mod> > Ainv = A.inverse();
	Ainv.Print();

}
