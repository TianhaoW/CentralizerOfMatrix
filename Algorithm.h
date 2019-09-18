#ifndef ALGORITHM_H
#define ALGORITHM_H

using namespace std;

//finding gcd(a, b) in the PID D and return x,y such that ax+by=d;

template <class D>
D gcd(const D& a, const D& b, D& x, D& y){
	if(a.isZero()) {
		x = D(0);
		y = D(1);
		return b;
	}
	
	D x1,y1,q,r;
	b.divide(a, q, r);	
	D d = gcd(r, a, x1, y1);

	x = y1 - q * x1;
	y = x1;

	return d;

}

int gcd(int a, int b, int& x, int& y){
	if (a == 0) {
		x=0;
		y=1;
		return b;
	}

	int x1,y1;
	int d = gcd(b%a, a, x1, y1);

	x = y1 - (b/a)*x1;
	y = x1;

	return d;
}


#endif
