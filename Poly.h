#ifndef POLY_H
#define POLY_H

#include<vector>
#include<iostream>

using namespace std;

template <class K>
class Poly{
	private:
		vector<K> pol;
		int deg;
	public:	
		//constructors
		Poly(vector<K> p); //k^n \mapsto k[x]
		Poly(); //zero polynomial
		Poly(const Poly<K>& copy);
		Poly(unsigned int n); //poly x^n
		Poly(unsigned int n, K a); //poly ax^n
	
		//outputs
		void Print() const;	
	
		//accessor
		int getDeg() const {return deg;}
		const vector<K>& getPoly() const{return pol;}
		bool isZero() const {return !(deg + 1);}

		//operations
		Poly<K> neg() const {
			vector<K> res = pol; 
			for(int i=0; i<=deg; i++){res.at(i).neg();} 
			return Poly<K>(res);
		}
		//void neg(){for(int i = 0; i<=deg; i++) {pol.at(i).neg();}}
		Poly<K> operator + (const Poly<K>& b) const;
		Poly<K> operator - (const Poly<K>& b) const {return *this+b.neg();}
		Poly<K> operator * (const Poly<K>& b) const;
		
		void divide(const Poly<K>& b, Poly<K>& q, Poly<K>& r) const; //this=bq+r

		//find a,b,d such that ax+by=d where d=gcd(x,y)
		//void gcd(const Poly<K>& y, Poly<K>& a, Poly<K>& b, Poly<K>& d) const;

};

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
Poly<K>::Poly(unsigned int n, K a) {
	pol.resize(n+1, K(0));
	pol.at(n) = a;
	deg = n;
}

template <class K>
void Poly<K>::Print() const{
	if(deg == -1) {cout << "0 "; return;}
	int index = 1;
	if(!pol[0].isZero()) {
		#ifdef DEBUG
			cout << "The initial term is not 0\n";
		#endif
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
}

template <class K>
Poly<K> Poly<K>::operator + (const Poly<K>& b) const {
	if(deg == -1) {return b;}
	if(b.getDeg() == -1) {return *this;}
	
	vector<K> res;
	vector<K> small;
	vector<K> big;
	int bsize = 0;
	int index = 0;

	if(deg <= b.getDeg()){bsize = b.getDeg() + 1; small = pol; big = b.getPoly();}
	else {bsize = deg + 1; small = b.getPoly(); big = pol;}
	
	small.resize(bsize, K(0));
	res.resize(bsize, K(0));
	
	for(int i = 0; i < bsize; i++) {
		res.at(i) = small.at(i)+big.at(i);
	}
	return Poly<K>(res);
}

template <class K>
Poly<K> Poly<K>::operator * (const Poly<K>& b) const{
	Poly<K> res;
	if(deg == -1 || b.getDeg() == -1) {return res;}
	
	vector<K> small;
	vector<K> big;
	vector<K> tmp;

	if(deg <= b.getDeg()){big = b.getPoly(); small = pol;}
	else{big = pol; small = b.getPoly();}
	
	for(int i = 0; i<small.size(); i++) {
		if(!small.at(i).isZero()){
			tmp.resize(big.size() + i, K(0));
			for(int j = 0; j<big.size(); j++) {
				tmp.at(i+j) = small.at(i)*big.at(j);
			}
			res = res+(Poly(tmp));
			tmp.resize(1,K(0));
		}
	}
	return res;
}


template <class K>
void Poly<K>::divide(const Poly<K>& b, Poly<K>& q, Poly<K>& r) const{
	if(deg < b.getDeg()){
		q = Poly<K>();
		r = *this;
		return;
	}

	// the inverse of the initial term of b
	K ini = b.getPoly().back().inverse();

	q = Poly<K>(deg - b.getDeg(), pol.back() * ini);
	r = (*this)-(b * q);

	while(r.getDeg() >= b.getDeg()) {
		Poly<K> qtmp(r.getDeg() - b.getDeg(), r.getPoly().back() * ini);
		q = q + qtmp;
		r = r - (b * qtmp);
	}
}
/*
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
*/
#endif
