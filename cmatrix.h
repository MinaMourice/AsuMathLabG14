#ifndef CMATRIX_H
#define CMATRIX_H

#include <string>
#include "pcomplexlib.h"

using namespace std;

class CMatrix {
private:
	int nR, nC;    // Row & column Number
	complex** values;  // pointer to pointer values (Matrix r*c)

public:
	/*constractors and destractors*/
	CMatrix(); // default Constructor 
	~CMatrix(); // Destructor
	enum MI { MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE }; // Constants

															  // Copy functions and all its dependencies - Boula
															  // ===
	void reset(); // makes the current matrix 0*0
	void copy(const CMatrix& m); // copies matrix m into current matrix
	void copy(complex d); // copies the 1*1 matrix [d] into current matrix 
	void copy(string s); // copies the string matrix into current matrix
	string getOriginalString();
	string getString(const int columnsToPrintEachTime = 7); // generates current matrix's string
	CMatrix denominatorOfDiv(float f);
	// ===

	// Constructors With Different Passing Parameters - Beshoy
	CMatrix(int nR, int nC, int initialization = MI_ZEROS, complex initializationValue = 0.0);
	CMatrix(int nR, int nC, complex first, ...);
	CMatrix(CMatrix& m);
	CMatrix(complex d);
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
	complex getDeterminant();
	complex getDeterminant2();
	CMatrix getTranspose();
	CMatrix getInverse();

	// Strassen multiplaying
	CMatrix subMatrix(const int& rowToStartAt, const int& columnToStartAt, const int& rowsNo, const int& columnsNo);
	friend CMatrix concatinate(const CMatrix& mat11, const CMatrix& mat12, const CMatrix& mat21, const CMatrix& mat22);
	void smul(CMatrix& m);

	// Matrices powers
	void pow(const complex& d);

	friend bool isdiagonal(const CMatrix& mat);
	friend CMatrix diagPow(const CMatrix& mat, const complex& d);

	friend bool issymmetric(const CMatrix& mat);
	//friend void jacobiEigenAnalysis(const CMatrix matrix, const int& maxIterations, CMatrix& eigenVectors, complex eigenValues[], int &iteraNo, int &rotationsNo);
	//friend CMatrix symmPow(const CMatrix& mat, const complex& d);
	
	friend CMatrix subColumn(const CMatrix& mat, const int& C);
	friend complex innerProd(const CMatrix& mat1, const CMatrix& mat2);
	friend complex columnLength(const CMatrix& mat, const int& column);
	friend void qrDecomp(const CMatrix& mat, CMatrix& q, CMatrix& r);

	friend CMatrix generalPower(const CMatrix& eigenVectors, const CMatrix& eigenValues, const complex& d);

private:
	CMatrix CMatrix::posPower(const complex& d);
};
#endif