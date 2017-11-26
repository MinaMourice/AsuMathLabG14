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
	
	// ===== PHASE TWO
	void dotMul(Const CMatrix& m); // Mina Magdy /* (*this) .* m is multiple element by element as general result(i,j)=(*this)(i,j)*m(i,j) */
	void dotDiv(CMatrix& m); // Mina Magdy /* is a dot divide operation as divide element by element */
	void dotPow(double d); // Mina Magdy /* is a pow of each element to power of d */
	void lDiv(const CMatrix& m); // Mina Magdy /* multiply of inverse(A)*B and is called left div */
	void dotLDiv(const CMatrix& m); // Mina Magdy /* Element by element multiply of inverse of *this and m */
	friend CMatrix sin(const CMatrix& m); // Mina Magdy /* Get sin for each element */
	friend CMatrix cos(const CMatrix& m); // Mina Magdy /* Get cos for each element */
	friend CMatrix tan(const CMatrix& m); // Mina Magdy /* Get tan for each element */
	friend CMatrix asin(const CMatrix& m); // Mina Magdy /* Get sin-1 for each element */
	friend CMatrix acos(const CMatrix& m); // Mina Magdy /* Get cos-1 for each element*/
	friend CMatrix atan(const CMatrix& m); // Mina Magdy /* Get tan-1 for each element */
	friend CMatrix exp(const CMatrix& m); // Mina Magdy /* Get expontial of each element */
	friend CMatrix log(const CMatrix& m); // Mina Magdy /* Get the ln of each element */
	friend CMatrix log10(const CMatrix& m); // Mina Magdy /* Get the log to base 10 of each element */


};
#endif
