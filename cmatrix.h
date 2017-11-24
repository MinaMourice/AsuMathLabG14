#ifndef CMATRIX_H
#define CMATRIX_H

#include <string>

using namespace std;

class CMatrix {
private:
	int nR, nC;    // Row & column Number
	double** values;  // pointer to pointer values (Matrix r*c)

public:
	/*constractors and destractors*/
	CMatrix(); // default Constructor 
	~CMatrix(); // Destructor
	enum MI { MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE }; // Constants

															  // Copy functions and all its dependencies - Boula
															  // ===
	void reset(); // makes the current matrix 0*0
	void copy(const CMatrix& m); // copies matrix m into current matrix
	void copy(double d); // copies the 1*1 matrix [d] into current matrix 
	void copy(string s); // copies the string matrix into current matrix
	string getOriginalString();
	string getString(const int columnsToPrintEachTime = 7); // generates current matrix's string
	CMatrix denominatorOfDiv(float f);
	// ===

	// Constructors With Different Passing Parameters - Beshoy
	CMatrix(int nR, int nC, int initialization = MI_ZEROS, double initializationValue = 0.0);
	CMatrix(int nR, int nC, double first, ...);
	CMatrix(CMatrix& m);
	CMatrix(double d);
	CMatrix(string s);

	/*operators*/
	CMatrix operator=(const CMatrix& m);
	void operator+=(CMatrix& m);
	CMatrix operator+(CMatrix& m);
	void operator-=(CMatrix& m);
	CMatrix operator-(CMatrix& m);
	void operator*=(CMatrix& m);
	CMatrix operator*(CMatrix& m);
	void operator/=(CMatrix& m);
	CMatrix operator/(CMatrix& m);

	////////////////////Core Operation Team/////////////////////
	void add(CMatrix& m);
	void sub(CMatrix& m);
	void mul(CMatrix& m);
	void div(CMatrix& m);
	CMatrix getCofactor(int r, int c);
	void swapRow(int row1, int row2);
	double getDeterminant();
	double getDeterminant2();
	CMatrix getTranspose();
	CMatrix getInverse();
};
#endif