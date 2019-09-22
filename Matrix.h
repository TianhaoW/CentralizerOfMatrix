#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include "Poly.h"

using namespace std;

// D is a PID 
template <class D>
class Matrix{
	private:
		vector<vector<D> > entry;
		unsigned int dim;
	public:
		//constructors
		Matrix(unsigned int n = 1); //constructor for I_n, default is I_1
		Matrix(unsigned int n, D a); //constructor for aI_n
		Matrix(vector<vector <D> >ent);//construct matrix from a double array, no check for validity
		Matrix(const Matrix<D>& copy);
		Matrix(const Poly<D>& f); //construct the companian matrix C(f)

		//modifier
		void setEnt(unsigned int i, unsigned int j, D val){entry.at(i).at(j) = val;}

		//accessor
		vector< vector<D> > getEnt() const {return entry;}
		unsigned int getDim() const {return dim;} 
		vector<D> getCol(unsigned int j) const;

		//operations
		Matrix<D> operator * (const Matrix<D>& b) const;
		vector<D> operator * (const vector<D>& b) const;
		Matrix<D> operator + (const Matrix<D>& b) const;
		Matrix<D> operator - (const Matrix<D>& b) const;	
		Matrix<D> exp(unsigned int n) const;

		Matrix<D> mminor(unsigned int i, unsigned int j) const;
		Matrix<D> inverse() const;
		D det() const;

		//Simith Normal Form, return L,R diag such that L*this*R = diag()
		//This is not the general algorithm, this only supports matrix of the form xI-A\in M_n(k[x])
		void SNF(Matrix<D>& L, Matrix<D>& R);

		//D is assumed as a field here, the returned matrix is the transformation matrix
		Matrix<D> Invf(vector<Poly<D> >& inv) const;

		//D is assumed as a field here
		//return the k-basis for the centralizer
		vector<Matrix<D> > Cent() const;

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
Matrix<D>::Matrix(unsigned int n, D a) {
	dim = n;
	entry.resize(n);
	for(int i = 0; i < n; i++){
		entry.at(i).resize(n, D(0));
		entry.at(i).at(i) = a;
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
Matrix<D>::Matrix(const Poly<D>& f){
	dim = f.getDeg();
	entry.resize(dim);
	for (int i = 0; i < dim; i++) {
		entry.at(i).resize(dim, D(0));
		entry.at(i).at(dim-1) = f.getPoly().at(i).neg();
	}
	for (int i = 1; i < dim; i++) {
		entry.at(i).at(i-1) = D(1);
	}
}

template<class D>
vector<D> Matrix<D>::getCol(unsigned int j) const{
	vector<D> ret;
	if(j >= dim){cout << "out of bounds\n"; return ret;}
	for (int i = 0; i < dim; i++) {
		ret.push_back(entry.at(i).at(j));
	}
	return ret;
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
Matrix<D> Matrix<D>::operator - (const Matrix<D>& b) const{
	if(dim != b.getDim()) {cout << "Error: Dimension does not match\n"; return Matrix<D>(1);}
	Matrix<D> res(dim);
	for(int i = 0; i < dim; i++) {
		for(int j = 0; j < dim; j++) {
			res.setEnt(i, j, entry.at(i).at(j) - b.getEnt().at(i).at(j));
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
vector<D> Matrix<D>::operator * (const vector<D>& b) const{
	vector<D> res;
	if(dim != b.size()) {cout << "Error: Dimension does not match\n"; return res;}
	for (int i = 0; i < dim; i++) {
		D tmp(0);
		for(int j = 0; j < dim; j++){
			tmp = tmp + (entry.at(i).at(j) * b.at(j));
		}
		res.push_back(tmp);
	}
	return res;
}

template<class D>
Matrix<D> Matrix<D>::exp(unsigned int n) const{
	if (n == 0) {return Matrix<D>(dim);}
	Matrix<D> res = (*this);
	n--;
	while (n > 0) {
		res = res * (*this);
		n--;
	}
	return res;
}

template<class D>
Matrix<D> Matrix<D>::mminor(unsigned int i, unsigned int j) const{
	Matrix<D> ret(dim-1);
	if (i > dim || j > dim) {cout << "Error: Finding minor, out of range\n"; return ret;}
	
	int m = 0;
	int n = 0;

	while(m < dim - 1){
		while(n < dim - 1) {
			if(m < i){
				if (n < j ) {ret.setEnt(m,n, entry.at(m).at(n));}
				else {ret.setEnt(m,n, entry.at(m).at(n+1));}
			}
			else{
				if (n < j) {ret.setEnt(m,n, entry.at(m+1).at(n));}
				else {ret.setEnt(m,n, entry.at(m+1).at(n+1));}
			}
			n++;
		}
		m++;
		n = 0;
	}
	return ret;
}

template<class D>
D Matrix<D>::det() const {
	if (dim == 1){return entry.at(0).at(0);}
	D tmp(0);
	
	for (int i = 0; i < dim; i++) {
		if(entry.at(0).at(i).isZero()){continue;}
		if(i % 2){
			tmp = tmp - (entry.at(0).at(i)) * (*this).mminor(0,i).det();
		}
		else {
			tmp = tmp + (entry.at(0).at(i)) * (*this).mminor(0,i).det();
		}
	}
	return tmp;
}

template<class D>
Matrix<D> Matrix<D>::inverse() const{
	D det = (*this).det();
	if (!det.isUnit()){cout << "The matrix is not invertible\n";}
	D fac = det.inverse();
	
	Matrix<D> ret(dim);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			if((i+j)%2){
				ret.setEnt(j,i, fac * (*this).mminor(i,j).det().neg());
			}
			else {
				ret.setEnt(j,i, (fac * (*this).mminor(i,j).det()));
			}
		}
	}
	return ret;
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
		entry.at(i+1).at(i+1).divide(entry.at(i).at(i), q, r);
		if (r.isZero()){cout << "Rearranging: divide case\n"; continue;}
		
		cout << "Rearranging: not divide case\n";

		Matrix<D> Rtmp(dim);
		Matrix<D> Ltmp(dim);

		Rtmp.setEnt(i+1, i, D(1));

		cout << "Printing the Rtmp\n";
		Rtmp.Print();

		(*this) = (*this) * Rtmp;
		R = R * Rtmp;

		cout << "Printing the result matrix\n";
		(*this).Print();

		D x, y, d;
		entry.at(i).at(i).egcd(entry.at(i+1).at(i), x, y, d);
				
		if(d.isUnit()){
			Ltmp.setEnt(i,i, x);
			Ltmp.setEnt(i,i+1, y);
			Ltmp.setEnt(i+1,i, D(0)-entry.at(i+1).at(i));
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

		if(entry.at(i).at(i+1).isZero()){cout << "isZero for eliminating\n"; continue;}
		else {
			Matrix<D> Rtmp(dim);
			D q,r;

			entry.at(i).at(i+1).divide(entry.at(i).at(i), q, r);
			Rtmp.setEnt(i,i+1, D(0)-q);
			R = R * Rtmp;
			(*this) = (*this) * Rtmp;
			cout << "Printing the Rtmp for eliminating matrices\n";
			Rtmp.Print();
			cout << "Printing the result matrix after row elimination\n";
			(*this).Print();
		}
	}
	cout << "Printing the final matrix L\n";
	L.Print();
	cout << "Printing the final matrix R\n";
	R.Print();
	cout << "Printing the result matrix \n";
	(*this).Print();
}

template<class D>
Matrix<D> Matrix<D>::Invf(vector<Poly<D> >& inv) const{
	inv.clear();

	vector<int> deg;

	//Converting *this to a matrix in D[x]
	Matrix<Poly<D> > conv(dim);
	for (int i = 0; i< dim; i++){
		for(int j = 0; j< dim; j++){
			conv.setEnt(i,j,Poly<D>(0, entry.at(i).at(j)));
		}
	}

	//Finding the Smith Normal Form of xI-A
	Matrix<Poly<D> > tmp = Matrix<Poly<D> >(dim, Poly<D>(2)) - conv;	
	Matrix<Poly<D> > L, R;
	tmp.SNF(L, R);
	
	int index = 0;

	//Obtaining the Invariant Factors
	for(int i = 0; i < dim ; i++){
		if (tmp.getEnt().at(i).at(i).isUnit()){deg.push_back(0); index++; continue;}
		else {
			inv.push_back(tmp.getEnt().at(i).at(i));
			deg.push_back(tmp.getEnt().at(i).at(i).getDeg());
			cout << "Printing the saved degree\n";
			cout << tmp.getEnt().at(i).at(i).getDeg();
			cout << "\n";
		}
	}

	cout << "index is " << index << "\n";

	//Constructing the transformation matrix
	Matrix<Poly<D> > Linv = L.inverse();
	Matrix<D> P(dim);
	int j = 0; // the column index 

	while(index < dim){
		vector<Poly<D> > y = Linv.getCol(index);
		vector<D> col;

		// the phi function
		for (int i = 0; i < dim; i++){
			col.push_back(y.at(i).getPoly().at(0));
		}
		for (int i = 1; i < dim; i++) {
			int counter = 0;
			vector<D> coltmp;
			for(int j = 0; j < dim; j++){
				if (i >= y.at(j).getPoly().size()) {
					counter++;
					coltmp.push_back(D(0));
				}
				else {
					coltmp.push_back(y.at(j).getPoly().at(i));
				}
			}
			if(counter == dim) {break;}
			coltmp = ((*this).exp(i)) * coltmp;

			for(int i = 0; i < dim; i++){
				col.at(i) = col.at(i)+coltmp.at(i);
			}
		}
		
		// updating the matrix P
		for (int i = 0; i < deg.at(index); i++){
			cout << deg.at(index);
			cout << "Updating P\n";
			for (int k = 0; k < dim; k++) {
				P.setEnt(k, j, col.at(k));
			}
			col = (*this) * col;
			j++;
		}
		index++;
	}

	return P;
}


template <class D>
vector<Matrix<D> > Matrix<D>::Cent() const{
	vector<Poly<D> > inv;
	Matrix<D> P = (*this).Invf(inv);
	Matrix<D> Pinv = P.inverse();

	//dimension of the centralizer as k-vector space
	int Cdim = 0;
	for(int i = 0; i < inv.size(); i++){
		Cdim = Cdim + (2 * i + 1) * inv.at(inv.size() - i - 1).getDeg();
	}
	cout << "The k-dimension of the centralizer is " << Cdim << "\n";

	//constructing the k-basis for each block
	vector<vector< vector <Matrix<D> > > >block;
	for(int i = 0; i < inv.size(); i++) {
		vector<vector<Matrix<D> > >row;
		for(int j = 0; j < inv.size(); j++){
			vector<Matrix<D> > basis;
			Matrix<D> cf = Matrix<D>(inv.at(i));

			if (i == j){
				basis.push_back(Matrix<D>(inv.at(i).getDeg()));
				for(int k = 0; k < inv.at(i).getDeg() - 1; k++){
					basis.push_back(cf);
					cf = cf * cf;
				}
			}
			else if(i < j){
				//constructing the generating vector
				vector<D> q;
				q.resize(inv.at(i).getDeg(), D(0));
				q.at(0) = D(1);
				
				//constructing the generating matrix
				Matrix<D> qm(inv.at(j).getDeg());
				for(int c = 0; c < inv.at(j).getDeg(); c++) {
					for(int r = 0; r < inv.at(i).getDeg(); r++){
						qm.setEnt(r, c, q.at(r));
					}
					q = cf * q;
				}

				//constructing the basis
				for(int k = 0; k < inv.at(i).getDeg(); k++) {
					basis.push_back(qm);

					for(int c = 0; c < inv.at(j).getDeg() - 1; c++) {
						for(int r = 0; r < inv.at(i).getDeg(); r++) {
							qm.setEnt(r,c, qm.getEnt().at(r).at(c+1));
						}
					}
					for(int r = 0; r < inv.at(i).getDeg(); r++) {
						qm.setEnt(r, inv.at(j).getDeg() - 1, q.at(r));
					}
					q = cf * q;
				}
			}
			else {
				//constructing the generating vector

				Poly<D> qtmp, rtmp;

				inv.at(i).divide(inv.at(j), qtmp, rtmp);

				vector<D> q;
				q.resize(inv.at(i).getDeg(), D(0));
				for (int k = 0; k <= qtmp.getDeg(); k++) {
					q.at(k) = qtmp.getPoly().at(k);
				}
				
				//constructing the generating matrix
				Matrix<D> qm(inv.at(i).getDeg());
				for(int c = 0; c < inv.at(i).getDeg(); c++) {
					for(int r = 0; r < inv.at(i).getDeg(); r++){
						qm.setEnt(r, c, q.at(r));
					}
					q = cf * q;
				}

				//constructing the basis
				for(int k = 0; k < inv.at(j).getDeg(); k++) {
					basis.push_back(qm);
					qm = cf * qm;
				}
			}
			row.push_back(basis);
		}
		block.push_back(row);
	}

	cout << "finished constructing the block\n";
	cout << "The size of block is \n" << block.size() << " * " << block.back().size() << "\n";
	cout << "The deg of the minimal polynomial is " << inv.back().getDeg() << "\n";

	//constructing the basis for Cent(A)
	vector<Matrix<D> > basis;
	Matrix<D> cent(dim);
		
	int r = 0;
	int c = 0;
		
	for(int i = 0; i < inv.size(); i++) {
		for(int j = 0; j < inv.size(); j++) {
			for(int k = 0; k < block.at(i).at(j).size(); k++) {	
	
				Matrix<D> cent(dim, D(0));	
				Matrix<D> tocopy = block.at(i).at(j).at(k);

				cout << "Printing the block\n";
				tocopy.Print();

				for(int a = 0; a < inv.at(i).getDeg(); a++) {
					for(int b = 0; b < inv.at(j).getDeg(); b++){
						cent.setEnt(r + a,c + b, tocopy.getEnt().at(a).at(b));
					}
				}
				basis.push_back(P * cent * Pinv);
			}
			c = c+inv.at(j).getDeg();
		}
		r = r + inv.at(i).getDeg();
		c = 0;
	}
	cout << "add basis\n";

	return basis;

}

#endif
