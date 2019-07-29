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
	Poly(unsigned int n); //poly x^n
	
	void Print() const;
	
	Poly add(const Poly& y) const;
	Poly multiply(const Poly& y) const;

	//a = bq+r
	void divide(const Poly& b, Poly& q, Poly& r) const;


	//find a,b,d such that ax+by=d where d=gcd(x,y)
	void gcd(const Poly& y, Poly& a, Poly& b, Poly& d) const;

};

#endif
