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
}
