#include "Matrix.h"
#include<iostream>
#include<string>
#include "Poly.h"

using namespace std;


Matrix::Matrix(unsigned int s){
	size = s;
	m.resize(s);
	for(int i = 0; i<size; i++){
		m.at(i).resize(s, 0);
	}
}

Matrix::Matrix(vector<vector<bool> >entry){
	size = entry.size();
	m.resize(size);
	for(int i = 0; i<size; i++){
		m.at(i).resize(size,0);
		for(int j = 0; j<size; j++){
			m.at(i).at(j) = entry.at(i).at(j);
		}
	}

}

Matrix::Matrix(const Matrix& copy) {
	size = copy.size;
	m = copy.m;
}

Matrix::Matrix(const Poly& p) {
	size = p.deg;
	m.resize(size);
	for(int i = 0; i < size; i++) {
		m.at(i).resize(size, 0);
	}
	for(int i = 0; i < size - 1; i++) {
		m.at(i + 1).at(i) = 1;
	}
	for(int i = 0; i < size; i++) {
		m.at(i).at(size - 1) = p.pol.at(i);
	}
}


vector<bool> Matrix::getRow(unsigned int x){
	vector<bool> res(size);
	for (int j = 0; j<size; j++){
		res.at(j) = m.at(x).at(j);
	}
	return res;
}
vector<bool> Matrix::getColumn(unsigned int y){
	vector<bool> res(size);
	for(int i=0; i<size; i++){
		res.at(i) = m.at(i).at(y);
	}
	return res;
}

void Matrix::Print(){
	for(int i = 0; i<size; i++) {
		for(int j=0; j<size; j++) {
			cout << m.at(i).at(j) << " ";
		}
		cout << '\n';
	}
}

Matrix Matrix::multiply(const Matrix& y) {
	Matrix res(size);
	if(y.size != size){cout << "The dimension does not match \n"; return res;}	

	bool dot = 0;
	for (int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			for(int k = 0; k < size; k++) {
		    		dot = dot^(m.at(i).at(k) & y.m.at(k).at(j));
			}
			res.m.at(i).at(j) = dot;
			dot = 0;
		}
	}
	return res;
}

Matrix Matrix::add(const Matrix& y){
	Matrix res(size);
	if(y.size != size) {cout << "The dimension does not match \n"; return res;}
	
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			res.m.at(i).at(j) = m.at(i).at(j)^y.m.at(i).at(j);
		}
	}
	return res;
}

Matrix Matrix::exp(unsigned int i){
	if(i == 0){
		Matrix id(size);
		for(int j = 0; j < size; j++){
			id.m.at(j).at(j) = 1;
		}
		return id;
	}
	Matrix res(*this);
	while(i > 1) {
		res = res.multiply(*this);
		i--;
	}	
	return res;
}

