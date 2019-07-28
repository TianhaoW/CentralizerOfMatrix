#include "Poly.h"
#include <iostream>

using namespace std;


//Asuumed the Input is valid i.e the last term is 1;
Poly::Poly(vector<bool> p) {
	deg = p.size()-1;
	pol.resize(p.size(), 0);
	for(int i = 0; i<p.size(); i++) {
		pol[i] = p[i];
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


void Poly::Print(){
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
}

Poly Poly::add(const Poly& y) {
	vector<bool> b, s, res;
	int size;
	bool degchange = true;

	if(this->deg >= y.deg){b = this->pol; s = y.pol;} else {b = y.pol; s = this->pol;}
	size = b.size();

	s.resize(size, 0);
	res.resize(size);

	int index = size-1;
	while(index >=0 && (!(b.at(index)^s.at(index)))){
		index--;		
	}
		
	if(index < 0 ) {res.pol.resize(1, false); res.deg = -1; cout << "result is 0 \n"; return;}
	res.pol.resize(index+1);
	res.deg = index;
	while(index>=0) {
		res.pol.at(index) = b.at(index)^s.at(index);
		index--;
	}		
}
	


	void multiply(Poly& p2, Poly& res) {
		vector<bool> b,s;
		vector<bool> tmp1;
		int index;
		
		res.Tozero();	
	
		// when one of the polynomial is 0
		if(this->deg == -1 || p2.deg == -1) {res.pol.resize(1,false); res.deg = -1; return;}

		if(this->deg >= p2.deg){b = this->pol; s = p2.pol;} else {b = p2.pol; s=this->pol;}
		index = s.size()-1;
		
		while(index >= 0) {
			if(s[index]) {
				tmp1.resize(b.size()+index, false);
				for(int i = 0; i<b.size(); i++) {
					tmp1.at(index + i) = b.at(i);
				}
				Poly tmp(tmp1);

				//cout << "tmp is";

