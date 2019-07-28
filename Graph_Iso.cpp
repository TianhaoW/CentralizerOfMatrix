#include <iostream>
#include <vector>

using namespace std;

class Matrix {
    private:
	vector<vector<bool> > m;

    public:
	int size;
	Matrix(unsigned int s) {
	    m.resize(s, vector<bool>(s, true));
	    size = s;
	}

	bool get (unsigned int x, unsigned int y) {return m.at(x).at(y);}

	int Setup (unsigned int x, unsigned int y, bool value) {
	    if (x >= size || y >= size) { 
		cout << "out of range";
		return 1;
	    }
	    m.at(x).at(y) = value;
	    // cout << "setting up value at" << x << y <<endl; 
	    return 0;
	}

	Matrix(unsigned int s, vector<vector <bool> >ent) {
	    m.resize(s, vector<bool> (s,true));
	    size = s;
	    for (int i = 0; i<size ; i++) {
		for (int j = 0; j<size; j++) {
		    Setup(i,j, ent.at(i).at(j));
		}
	    }
	}

        class M_row{
            vector<bool>& row;
            public:
		M_row(vector<bool>& r) : row(r) { }
		bool operator[](unsigned int y){
		    return row.at(y);
		}
	};
	M_row operator[](unsigned int x) {
	    return M_row(m.at(x));
	}

	void Print() {
	    for(int i = 0; i<size; i++) {
		for(int j=0; j<size; j++) {
		    cout << m[i][j] << " ";
		}
		cout << '\n';
	    }
	}

	//1 for row, 0 for column TODO
	void Tovector(bool forrow, int num, vector<bool> res) {}

};


//TODO  can be faster
int Multiply (Matrix* x, Matrix* y, Matrix* result) {
	unsigned int size = x->size;	
	bool dot = false;
	for (int i = 0; i<size; i++) {
	    for(int j = 0; j<size; j++) {
		for(int k = 0; k < size; k++) {
		    dot = dot^(x->get(i, k) & y->get(j, k));	
		}
		result->Setup(i,j, dot);
		cout<< "product at " << i << "," << j << " is " << dot << endl;
		dot = false;
	    }
	}
}


class Poly{
	vector<bool> pol;
	int deg;

	public:

	//Asuumed the Input is valid i.e the last term is 1;
	Poly(vector<bool> p) {		
		deg = p.size()-1;
		pol.resize(p.size(), true);
		for(int i = 0; i<p.size(); i++) {
			pol[i] = p[i];
		}	
	}

	//Default polynomial is 0 polynomial
	Poly() {
		pol.push_back(false);
		deg = -1;
	}

	void Print(){
		if(deg == -1) {cout << "0 \n"; return;}

		//cout << "The Deg is" << deg << endl;

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


	//Assumed input is non-zero
	void add(Poly& p2, Poly& res) {
		vector<bool> b, s;
		int size;
		bool degchange = true;

		if(this->deg >= p2.deg){b = this->pol; s = p2.pol;} else {b = p2.pol; s = this->pol;}
		size = b.size();

		s.resize(size, false);
		res.pol.resize(size);

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
	

	void Tozero() {pol.resize(1, false); deg = -1;}

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
				//tmp.Print();

				tmp.add(res, res);
				//cout << "Currently res is";
				//res.Print();				
				index--;
			}
		}
	}
};

void ParseInputMatrix(Matrix& ret) {
	cout << "Please enter entries for each row, separated by space \n" << "Enter 2 to end\n";
	string str;
	


}

void SwitchFunction() {}

int main() {

	/*
	vector<bool> r1;
	r1.push_back(true);
	r1.push_back(false);
	vector<bool> r2;
	r2.push_back(1);
	r2.push_back(1);
	vector< vector<bool> > ent;
	ent.push_back(r1);
	ent.push_back(r2);
	Matrix a(2, ent);
	a.Print();

	Matrix b(2);
	b.Print();

        Matrix res(2);
	Multiply(&a,&b,&res);
	res.Print();

	vector<bool> p;
	p.push_back(true);
	p.push_back(false);
	p.push_back(true);
	p.push_back(true);
	vector<bool> p2;
	p2.push_back(true);
	p2.push_back(true);
	p2.push_back(true);
	p2.push_back(true);
	Poly pol(p);
	cout << "p1 = ";
	pol.Print();
	Poly pol2(p2);
	cout << "p2 = ";
	pol2.Print();
	Poly addres;
	pol.add(pol2, addres);
	addres.Print();	
	cout << '\n' << endl;
	Poly mulres;
	pol.Print();
	pol2.Print();	
	pol.multiply(pol2, addres);
	addres.Print();
*/

	cout << res;
	
}
