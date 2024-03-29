#include "Poly.h"
#include "FField.h"
#include <iostream>
#include <vector>

#define DEBUG

using namespace std;

int main(){
	const int mod = 2;
	cout << "In mod" << mod << "\n";

	Poly<FField<mod> > p1;
	cout << "Constructing Zero polynomial \n";
	p1.Print();
	cout << "\n";

	Poly< FField<mod> > p2 (3);
	cout << "Constructing default deg 2 polynomial \n";
	p2.Print();
	cout << "\n";

	vector<FField<mod> > vec;
	vec.push_back(FField<mod>(2));
	vec.push_back(FField<mod>(3));
	vec.push_back(FField<mod>(5));
	cout << "Constructing 2+3x+5x^2\n";
	Poly<FField<mod> > p3(vec);
	p3.Print();
	cout << "\n";

	Poly<FField<mod> > p4;
	p4 = p2+p3;
	cout << "adding p2 and p3 :\n";
	p4.Print();
	cout << "\n";

	Poly<FField<mod> > p5;
	p5 = p2*p3;
	cout << "multiplying p2 and p3: \n";
	p5.Print();
	cout << "\n";

	Poly<FField<mod> > p6 = p3.neg();
	cout << "negating p3: \n";
	p6.Print();
	cout << "\n";

	Poly<FField<mod> >p7;
	p7 = p2-p3;
	cout << "p2-p2 = : \n";
	p7.Print();
	cout << "\n";


	vector<FField<mod> > vec2;
	vec2.push_back(FField<mod>(1));
	vec2.push_back(FField<mod>(2));
	cout << "Constructing 1+2x\n";
	Poly<FField<mod> > p8(vec2);
	p8.Print();
	cout << "\n";

	vector<FField<mod> > vec3;
	vec3.push_back(FField<mod>(2));
	vec3.push_back(FField<mod>(3));
	vec3.push_back(FField<mod>(5));
	vec3.push_back(FField<mod>(6));
	cout << "Constructing 2+3x+5x^2+6x^3\n";
	Poly<FField<mod> > p9(vec3);
	p9.Print();
	cout << "\n";

	Poly<FField<mod> > q,r;
	cout << "finding q,r such that 2+3x+5x^2+6x^3 = (1+2x)q +r\n";
	p9.divide(p8, q,r);
	q.Print();
	cout << "\n";
	r.Print();
	cout << "\n";

	vector<FField<mod> > vec4;
	vec4.push_back(FField<mod>(1));
	vec4.push_back(FField<mod>(2));
	vec4.push_back(FField<mod>(1));
	cout << "Constructing 1+2x+x^2\n";
	Poly<FField<mod> > p10(vec4);
	p10.Print();
	cout << "\n";
	
	vector<FField<mod> > vec5;
	vec5.push_back(FField<mod>(3));
	vec5.push_back(FField<mod>(4));
	vec5.push_back(FField<mod>(1));
	cout << "Constructing 3+4x+x^2\n";
	Poly<FField<mod> > p11(vec5);
	p11.Print();
	cout << "\n";

	Poly<FField<mod> > x,y,d;
	p10.egcd(p11, x,y,d);
	cout << "Runging gcd with (1+2x+x^2, 3+4x+x^2)\n";
	x.Print();
	cout << "\n";
	y.Print();
	cout << "\n";
	d.Print();
	cout << "\n";

	vector<FField<mod> > vec10;
	vec10.push_back(FField<mod>(1));
	vec10.push_back(FField<mod>(1));
	Poly<FField<mod> > p12(vec10);
	Poly<FField<mod> > p14 = p12*p12;
	p14.Print();

}
