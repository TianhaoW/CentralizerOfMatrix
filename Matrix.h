#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
using namespace std;

class Matrix{
	public:
		vector<vector<bool> > m;
		int size;
		Matrix(unsigned int s = 1);
		Matrix(vector<vector <bool> >entry);

	
		inline bool getEntry (unsigned int x, unsigned int y){return m.at(x-1).at(y-1);}
		inline void setEntry (unsigned int x, unsigned int y, bool value){m.at(x-1).at(y-1) = value;}

		vector<bool> getRow(unsigned int x);
		vector<bool> getColumn(unsigned int y);

		void Print();
};

#endif
