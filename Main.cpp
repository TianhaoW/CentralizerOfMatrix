#include <iostream>
#include "Matrix.h"
#include "FField.h"
#include <vector>
#include <string>
#include <sstream>


#define mod 5

int main() {
	cout << "Program credit to Tianhao Wang \n";
        cout << string(100, '-') << endl;	
	cout << "Currently works in field k=Z/" <<mod << "Z\n";
	cout << "Due to the feature of generic programing(template), if you want"
	       <<" to mod out a different prime, please edit the source code.\n";
        cout << string(100, '-') << endl;	

	cout << "Select which function to proceed: \n";
	cout << "1) Find Rational Canonical Form            2) Find Invariant Factors\n";
	cout << "3) Find k-basis for the centralizer\n";

	string input;
	int choice = 0;
	while(true){
		getline(cin, input);
		if(input.size() != 1) {cout << "Invalid input\n"; continue;}
		stringstream(input) >> choice;
		if(choice != 1 && choice != 2 && choice != 3){cout << "Invalid input\n";}
		else {break;}
	}

	cout << "Please enter the dimension of the matrix\n";
	int dim = 0;
	while(true){
		getline(cin, input);
		if(input.size() != 1) {cout << "Invalid input\n"; continue;}
		stringstream(input) >> dim;
		if(dim < 1){cout << "Invalid input\n";}
		else {break;}
	}

	cout << "Please enter the matrix row by row\n";
	
	vector< vector<FField<mod> > > mat;
	vector<FField<mod> > row;
	for(int i = 0; i < dim; i++) {
		bool badinput = false;
		do {
			row.clear();
			badinput = false;
			int counter = 0;
			int entry = 0;

			cout << "Please enter the entries for row " << i + 1 << " separated by space," 
			       	<< " only the first " << dim << " numbers will be recorded\n";
			getline(cin, input);
			istringstream iss(input);
			while(!iss.eof() && !iss.fail() && counter < dim){
				iss >> entry;
				if(iss.fail()) {cout << "Invalid Input\n"; badinput = true; break;}
				row.push_back(FField<mod>(entry));
				counter++;
			}
		        if(counter < dim) {cout << "Invalid Input\n"; badinput = true;}	
		} while(badinput);
		mat.push_back(row);
	}

	cout << "The matrix you entered is: \n";
	Matrix<FField<mod> > A(mat);
	A.Print();
        
	cout << string(100, '-') << "\n";	
	switch(choice) {
		case 1:{
			cout << "Finding the Rational Canonical Form: \n";
			Matrix<FField<mod> > P;
			vector<Poly<FField<mod> > > inv;
			P = A.Invf(inv);
			Matrix<FField<mod> >D;
			D = (P.inverse()) * A * P;
			cout << "The Rational Canonical Form is: \n";
			D.Print();
			cout << "with transformation matrix P \n";
			P.Print();
			cout << "such that A = P*diag(C(f_1),..., C(f_m))*P^{-1} \n";
		}
		break;
		case 2: {
			cout << "Finding the Invariant Factors: \n";
			Matrix<FField<mod> > P;
			vector<Poly<FField<mod> > > inv;
			P = A.Invf(inv);
			cout << "The Invariant factors are: \n";
			for(int i = 0; i< inv.size(); i++){
				inv.at(i).Print();
				cout << endl;
			}
		}
		break;
		case 3: {
			cout << "Finding the basis for the centralizer: \n";
			vector<Matrix<FField<mod> > > basis;
			basis = A.Cent();
			for(int i = 0; i < basis.size(); i++) {
				basis.at(i).Print();
				cout << endl;
			}
		}
		break;
		default:
			cout << "Error\n";
	}
}
