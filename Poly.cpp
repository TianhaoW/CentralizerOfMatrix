#include "Poly.h"
#include <iostream>
#include <vector>

using namespace std;

/*
template <class K>
void Poly<K>::resize(int n, K val){
	if(val.isZero()){
		#ifdef DEBUG
			cout << "The value entered is zero, setting polynomial to zero now\n";	
		#endif

		pol.resize(1, val);
		deg = -1;
		return;		
	}
		pol.resize(n, val);
		deg = n;
}

*/

template <class K>
Poly<K>::Poly(vector<K> p) {
	int index = p.size() - 1;
	while(index >= 0 && p.at(index).isZero()){index--;}
	deg = index;
	if(deg == -1){pol.resize(1, K(0)); return;}
	pol.resize(index + 1, K(0));
	while(index >= 0) {
		pol.at(index) = p.at(index);
		index--;
	}
}


template <class K>
Poly<K>::Poly() {
	pol.push_back(K(0));
	deg = -1;
}

template <class K>
Poly<K>::Poly(const Poly& copy){
	pol = copy.pol;
	deg = copy.deg;
}

template <class K>
Poly<K>::Poly(unsigned int n) {
	pol.resize(n + 1, K(0));
	pol.at(n) = K(1);
	deg = n;
}

template <class K>
void Poly<K>::Print() const{
	if(deg == -1) {cout << "0 \n"; return;}
	int index = 1;
	if(!pol[0].isZero()) {
		pol[0].Print();
	}
	else {
		while (pol[index].isZero()) {index++;}
		pol[index].Print();
		cout << "x^" << index; index++;
	}
	while(index <= deg) {
		if(!pol[index].isZero()) {cout << "+"; pol[index].Print(); cout << "x^" << index;}
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


