#include<iostream>
#include "FField.h"
#define DEBUG

int main() {
	const int mod = 2;

	FField<mod> a;
	cout << "constructing 0\n";
	a.Print();
	cout << "\n";

	FField<mod> b(11);
	cout << "constructing 11\n";
	b.Print();
	cout << "\n";

	FField<mod> c(2);
	cout << "constructing 2\n";
	c.Print();
	cout << "\n";

	cout << "adding 11, 4 \n";
	FField<mod> d = b+c;
	d.Print();
	cout << "\n";

	cout << "Is the result zero?\n";
	cout << d.isZero();
	cout << "\n";

	cout << "finding inverse of 2\n";
	FField<mod> e = c.inverse();
	e.Print();
	cout << "\n";
}
