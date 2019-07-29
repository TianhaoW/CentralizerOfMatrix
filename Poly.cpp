#include "Poly.h"
#include <iostream>
#include <vector>

using namespace std;


Poly::Poly(vector<bool> p) {
	int index = p.size() - 1;
	while(index >= 0 && !p.at(index)){index--;}
	deg = index;
	if(deg == -1){pol.resize(1, 0); return;}
	pol.resize(index + 1, 0);
	while(index >= 0) {
		pol.at(index) = p.at(index);
		index--;
	}
}


Poly::Poly() {
	pol.push_back(0);
	deg = -1;
}

Poly::Poly(const Poly& copy){
	pol = copy.pol;
	deg = copy.deg;
}

Poly::Poly(unsigned int n) {
	pol.resize(n + 1, 0);
	pol.at(n) = 1;
	deg = n;
}

/*
Poly& Poly::operator=(Poly& y){
	pol = y.pol;
	deg = y.deg;
	return *this;
}
*/

void Poly::Print() const{
	if(deg == -1) {cout << "0 \n"; return;}
	int index = 1;
	if(pol[0]) {
		cout << "1";
	}
	else {
		while (!pol[index]) {index++;}
		cout << "x^" << index; index++;
	}
	while(index <= deg) {
		if(pol[index]) {cout << "+x^" << index;}
		index++;
	}
	cout <<'\n';
}

Poly Poly::add(const Poly& y) const{
	if(deg == -1) {return y;}
	if(y.deg == -1) {return *this;}
	
	vector<bool> res;
	vector<bool> small;
	vector<bool> big;
	int bsize;
	int index = 0;

	if(deg <= y.deg){bsize = y.deg + 1; small = pol; big = y.pol;}
	else {bsize = deg + 1; small = y.pol; big = pol;}
	
	small.resize(bsize, 0);
	res.resize(bsize, 0);
	
	for(int i = 0; i < bsize; i++) {
		res.at(i) = small.at(i)^big.at(i);
	}
	return Poly(res);
}
	
Poly Poly::multiply(const Poly& y) const{
	Poly res;
	if(deg == -1 || y.deg == -1) {return res;}
	
	vector<bool> small;
	vector<bool> big;
	vector<bool> tmp;

	if(deg <= y.deg){big = y.pol; small = pol;}
	else{big = pol; small = y.pol;}
	
	for(int i = 0; i<small.size(); i++) {
		if(small.at(i)){
			tmp.resize(big.size() + i, 0);
			for(int j = 0; j<big.size(); j++) {
				tmp.at(i+j) = big.at(j);
			}
			res = res.add(Poly(tmp));
			tmp.resize(1,0);
		}
	}
	return res;
}

void Poly::divide(const Poly& b, Poly& q, Poly& r) const{
	if(deg < b.deg){
		q = Poly();
		r = *this;
		return;
	}
	q = Poly(deg - b.deg);
	r = this->add(b.multiply(q));
	
	while(r.deg>=b.deg) {
		Poly qtmp(r.deg - b.deg);
		q = q.add(qtmp);
		r = r.add(b.multiply(qtmp));
	}
}

void Poly::gcd(const Poly& y, Poly& a, Poly& b, Poly& d) const{
	/*
	cout << "calling gcd with \n";
	this->Print();
	y.Print();
	cout << endl;
	*/

	if(this->deg == -1) {
		a = Poly();
		b = Poly(0);
		d = y;
		return;
	}
	Poly qtmp, rtmp, atmp, btmp;	
	y.divide(*this, qtmp, rtmp);
	rtmp.gcd(*this, atmp, btmp, d);	
	
	a =  btmp.add(qtmp.multiply(atmp));
	b =  atmp;

}

