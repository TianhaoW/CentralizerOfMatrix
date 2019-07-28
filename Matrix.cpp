#include "Matrix.h"
#include<iostream>
#include<string>

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

