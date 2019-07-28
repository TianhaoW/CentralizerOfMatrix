#ifndef POLY_H
#define POLY_H

#include<vector>

using namespace std;

class Poly{

	public:	
	vector<bool> pol;
	int deg;

	Poly(vector<bool> p);
	Poly();
	Poly(const Poly& copy);
	
	void Print();
	
	Poly add(const Poly& y);
	Poly multiply(const Poly& y);

};

#endif
