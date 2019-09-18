#ifndef FFIELD_H
#define FFIELD_H

#include <iostream>
#include "Algorithm.h"

using namespace std;

template <int N>
class FField{
	private:
		int val;
	public:
		//constructors
		FField (){val = 0;}
		FField (int n){val = n % N; if( val < 0){val = val + N;}}
		
		//at each step, we keep 0<=val<N 
		bool isZero() const{return !(val);}
		
		//operations
		FField<N> operator + (const FField<N>& b) const {return FField(val+b.val);}
		FField<N> operator - (const FField<N>& b) const {return FField(val-b.val);}
		FField<N> operator * (const FField<N>& b) const {return FField(val*b.val);}
		void neg() {if(val == 0){return;} val = -val % N + N;}

		FField<N> inverse() const {
			int x, y;
			int d = gcd(val, N, x, y);
			if (d != 1) {cout << "inverse does not exist\n"; return FField<N>(0);}
			return FField<N>(x);
		}
		FField<N> operator / (const FField<N>& b) const{
			if (b.isZero()) {cout << "dividing zero error\n"; return FField<N>(0);}
			return (*this)*(b.inverse());
		}

		void Print() const{cout << val;}

};

#endif
