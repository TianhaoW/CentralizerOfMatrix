#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

using namespace std;

// D is a PID 
template <class D>
class Matrix{
	private:
		vector<vector<D> > entry;
		unsigned int dim;
	public:
		//constructor
		Matrix(unsigned int n = 1); //constructor for I_n, default is I_1
		Matrix(vector<vector <D> >ent); //construct matrix from a double array, no check for validity
		Matrix(const Matrix<D>& copy);

		//modifier
		void setEnt(unsigned int i, unsigned int j, D val){entry.at(i).at(j) = val;}

		//accessor
		vector<D> getRow(unsigned int x) const;
		vector<D> getColumn(unsigned int y) const;
		vector< vector<D> > getEnt() const {return entry;}
		unsigned int getDim() const {return dim;} 

		//operations
		Matrix<D> operator * (const Matrix<D>& b) const;
		Matrix<D> operator + (const Matrix<D>& b) const;	
		//Matrix<D> operator ^ (unsigned int n) const;

		//Simith Normal Form, return L,R diag such that this = L*diag*R
		//This is not the general algorithm, this only supports matrix of the form xI-A\in M_n(k[x])
		void SNF(Matrix<D>& L, Matrix<D>& R);

		void Print() const;
};

template<class D>
Matrix<D>::Matrix(unsigned int n) {
	dim = n;
	entry.resize(n);
	for(int i = 0; i < n; i++){
		entry.at(i).resize(n, D(0));
		entry.at(i).at(i) = (D(1));
	}
}

template<class D>
Matrix<D>::Matrix(vector< vector<D> > ent){
	entry = ent;
	dim = ent.size();
}

template<class D>
Matrix<D>::Matrix(const Matrix<D>& copy){
	entry = copy.getEnt();
	dim = copy.getDim();
}

template<class D>
Matrix<D> Matrix<D>::operator + (const Matrix<D>& b) const{
	if(dim != b.getDim()) {cout << "Error: Dimension does not match\n"; return Matrix<D>(1);}
	Matrix<D> res(dim);
	for(int i = 0; i < dim; i++) {
		for(int j = 0; j < dim; j++) {
			res.setEnt(i, j, entry.at(i).at(j) + b.getEnt().at(i).at(j));
		}
	}
	return res;
	
}

template<class D>
Matrix<D> Matrix<D>::operator * (const Matrix<D>& b) const{
	if(dim != b.getDim()) {cout << "Error: Dimension does not match\n"; return Matrix<D>(1);}
	Matrix<D> res(dim);
	for(int i = 0; i < dim; i++) {
		for(int j = 0; j < dim; j++) {
			D tmp(0);
			for (int k = 0; k < dim; k++) {
				tmp = tmp + (entry.at(i).at(k)*b.getEnt().at(k).at(j));
			}
			res.setEnt(i, j, tmp);
		}
	}
	return res;
}

template<class D>
void Matrix<D>::Print() const {
	for (int i = 0; i< dim; i++) {
		for(int j = 0; j < dim; j++){
			entry.at(i).at(j).Print();
			cout << "        ";
		}
		cout << "\n";
	}
}


template<class D>
void Matrix<D>::SNF(Matrix<D>& L, Matrix<D>& R){

	L = Matrix<D>(dim);
	R = Matrix<D>(dim);

	for(int i = 0; i < dim - 1; i++){
		for(int j = i+1; j < dim; j++){
			//improving pivots for columns
			D q,r;
			Matrix<D> Ltmp(dim);

			if(entry.at(i).at(i).isUnit()){
				cout << "unit case\n";
				break;
			}

			entry.at(j).at(i).divide(entry.at(i).at(i), q, r);
			if(r.isZero()){
				cout << "divide case \n";
				continue;
			}
			else{
				cout << "not divide case\n";
				D x, y, d;
				entry.at(i).at(i).egcd(entry.at(j).at(i), x, y, d);
				
				if(d.isUnit()){
					Ltmp.setEnt(i,i, x);
					Ltmp.setEnt(i,j, y);
					Ltmp.setEnt(j,i, D(0)-entry.at(j).at(i));
					Ltmp.setEnt(j,j, entry.at(i).at(i));
				}
				else {
					cout << "herehere\n";
					D q1, r1, q2, r2;
					entry.at(i).at(i).divide(d, q1, r1);
					entry.at(j).at(i).divide(d, q2, r2);
					Ltmp.setEnt(i, i, x);
					Ltmp.setEnt(i, j, y);
					Ltmp.setEnt(j, i, D(0)-q2);
					Ltmp.setEnt(j, j, q1);
				}
			}
			L = Ltmp * L;
			cout<< "Printing the Ltmp Matrix\n";
			Ltmp.Print();
			cout << "Printing the matrix before improving pivots\n";
			(*this).Print();
			(*this) = Ltmp * (*this);
			cout << "Printing the result matrix after improving pivots\n";
			(*this).Print();
		}
		//Eliminating Column Entries
		for (int j = i + 1; j < dim; j++) {
			if(entry.at(j).at(i).isZero()){cout << "isZero for eliminating\n"; continue;}
			else {
				Matrix<D> Ltmp(dim);
				D q,r;

				entry.at(j).at(i).divide(entry.at(i).at(i), q, r);
				
				cout << "Printing the q for eliminating\n";
				q.Print();
				cout << "\n";

				Ltmp.setEnt(j,i, D(0)-q);
				L = Ltmp * L;
				(*this) = Ltmp * (*this);
				cout << "Printing the Ltmp for eliminating matrices\n";
				Ltmp.Print();
				cout << "Printing the result matrix\n";
				(*this).Print();
			}
		}
		
		//Improving Pivots for Rows
		for(int j = i + 1; j < dim; j++){
			D q,r;
			Matrix<D> Rtmp(dim);

			if(entry.at(i).at(i).isUnit()){
				cout << "unit case for improving pivots for rows\n";
				break;
			}

			entry.at(i).at(j).divide(entry.at(i).at(i), q, r);
			if(r.isZero()){
				cout << "divide case for improving pivots for rows\n";
				continue;
			}
			else{
				cout << "not divide case for improving pivots for rows\n";
				D x, y, d;
				entry.at(i).at(i).egcd(entry.at(i).at(j), x, y, d);
				
				if(d.isUnit()){
					Rtmp.setEnt(i,i, x);
					Rtmp.setEnt(j,i, y);
					Rtmp.setEnt(i,j, D(0)-entry.at(i).at(j));
					Rtmp.setEnt(j,j, entry.at(i).at(i));
				}
				else {
					D q1, r1, q2, r2;
					entry.at(i).at(i).divide(d, q1, r1);
					entry.at(i).at(j).divide(d, q2, r2);
					Rtmp.setEnt(i,i, x);
					Rtmp.setEnt(j,i, y);
					Rtmp.setEnt(i, j, D(0)-q2);
					Rtmp.setEnt(j, j, q1);
				}
			}
			R = R * Rtmp ;
			cout<< "Printing the Rtmp Matrix\n";
			Rtmp.Print();
			(*this) =(*this) * Rtmp;
			cout << "Printing the next matrix\n";
			(*this).Print();
		}
		//Eliminating Row Entries
		for (int j = i + 1; j < dim; j++) {
			if(entry.at(i).at(j).isZero()){cout << "isZero for eliminating\n"; continue;}
			else {
				Matrix<D> Rtmp(dim);
				D q,r;

				entry.at(i).at(j).divide(entry.at(i).at(i), q, r);
				Rtmp.setEnt(i,j, D(0)-q);
				R = R * Rtmp;
				(*this) = (*this) * Rtmp;
				cout << "Printing the Rtmp for eliminating matrices\n";
				Rtmp.Print();
				cout << "Printing the result matrix after row elimination\n";
				(*this).Print();
			}
		}	
	}
	cout << "Printing L\n";
	L.Print();
	cout << "Printing R\n";
	R.Print();

	//Re-arranging diagonals
	for (int i = 0; i < dim - 1; i++){
		if (entry.at(i).at(i).isUnit()){cout << "Rearranging: Unit case\n"; continue;}
		D q,r;
		entry.at(i).at(i).divide(entry.at(i+1).at(i+1), q, r);
		if (r.isZero()){cout << "Rearranging: divide case\n"; continue;}
		
		cout << "Rearranging: not divide case\n";

		Matrix<D> Rtmp(dim);
		Matrix<D> Ltmp(dim);

		Rtmp.setEnt(i+1, i, D(1));
		(*this) = (*this) * Rtmp;
		R = R * Rtmp;

		D x, y, d;
		entry.at(i).at(i).egcd(entry.at(i+1).at(i), x, y, d);
				
		if(d.isUnit()){
			Ltmp.setEnt(i,i, x);
			Ltmp.setEnt(i,i+1, y);
			Ltmp.setEnt(i+1,i, D(0)-entry.at(i).at(i+1));
			Ltmp.setEnt(i+1,i+1, entry.at(i).at(i));
		}
		else {
			D q1, r1, q2, r2;
			entry.at(i).at(i).divide(d, q1, r1);
			entry.at(i+1).at(i).divide(d, q2, r2);
			Ltmp.setEnt(i, i, x);
			Ltmp.setEnt(i, i+1, y);
			Ltmp.setEnt(i+1, i, D(0)-q2);
			Ltmp.setEnt(i+1, i+1, q1);
		}

		L = Ltmp * L;
		cout<< "Printing the Ltmp Matrix\n";
		Ltmp.Print();
		(*this) = Ltmp * (*this);
		cout << "Printing the next matrix\n";
		(*this).Print();

		//Eliminating Column Entries
		if(entry.at(i+1).at(i).isZero()){cout << "isZero for eliminating\n"; continue;}
		else {
			Matrix<D> Ltmp(dim);
			D q,r;

			entry.at(i+1).at(i).divide(entry.at(i).at(i), q, r);
			Ltmp.setEnt(i+1,i, D(0)-q);
			L = Ltmp * L;
			(*this) = Ltmp * (*this);	
			cout << "Printing the Ltmp for eliminating matrices\n";
			Ltmp.Print();
			cout << "Printing the result matrix\n";
			(*this).Print();
		}
	}
}


#endif
