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
		Poly(unsigned int n); //poly x^{n-1}  Poly(0) will be 0, Poly(1) will be 1
		Poly(unsigned int n, K a); //poly ax^n
	
		//outputs
		void Print() const;	
	
		//accessor
		int getDeg() const {return deg;}
		const vector<K>& getPoly() const{return pol;}
		bool isZero() const {return !(deg + 1);}
		bool isUnit() const {return (deg == 0);}

		//bool operator ==(const Poly<K>& b) const;

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


		//void toMonic();

		void divide(const Poly<K>& b, Poly<K>& q, Poly<K>& r) const; //this=bq+r

		// extended gcd algorithm
		//find x,y,d such that this*x + by=d where d=gcd(this,d)
		void egcd(const Poly<K>& b, Poly<K>& x, Poly<K>& y, Poly<K>& d) const;

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
	if (n == 0) {pol.push_back(K(0)); deg = -1;}
	else {
		pol.resize(n, K(0));
		pol.at(n-1) = K(1);
		deg = n-1;
	}
}

template <class K>
Poly<K>::Poly(unsigned int n, K a) {
	if(a.isZero()){
		pol.push_back(K(0));
		deg = -1;
	}
	else {
		pol.resize(n+1, K(0));
		pol.at(n) = a;
		deg = n;
	}
}

template <class K>
void Poly<K>::Print() const{
	if(deg == -1) {cout << "0"; return;}
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

	if(deg <= b.getDeg()){big = b.getPoly(); small = pol;}
	else{big = pol; small = b.getPoly();}
	
	for(int i = 0; i<small.size(); i++) {
		vector<K> tmp;
		if(!small.at(i).isZero()){
			tmp.resize(big.size() + i, K(0));
			for(int j = 0; j<big.size(); j++) {
				tmp.at(i+j) = small.at(i)*big.at(j);
			}
			res = res+(Poly(tmp));
			//tmp.resize(1,K(0));
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

template <class K>
void Poly<K>::egcd(const Poly<K>& b, Poly<K>& x, Poly<K>& y, Poly<K>& d) const{
	d = gcd((*this), b, x, y);
	
	//make d to be monic
	K ini = d.getPoly().back().inverse();
	Poly<K> div (0, ini);
	d = d * div;
	x = x * div;
	y = y * div;
	
}

/*
template <class K>
void Poly<K>::toMonic() {
	K div = pol.back().inverse();
	for (int i = 0; i<= deg; i++) {
		pol.at(i) = pol.at(i) * div;
	}
}
*/

#endif
