#include "cmatrix.h"
#include <math.h>
#include <stdarg.h>
#include <cstdlib>
#include <valarray>

// ===== PHASE ONE
CMatrix::CMatrix()
{
	nR = nC = 0; values = NULL;
}
CMatrix::~CMatrix()
{
	reset();
}
CMatrix::CMatrix(int nR, int nC, int initialization, double initializationValue) // Beshoy
{
	this->nR = nR;
	this->nC = nC;
	if ((nR*nC) == 0)
	{
		values = NULL; return;
	}
	values = new double*[nR];
	for (int iR = 0; iR<nR; iR++)
	{
		values[iR] = new double[nC];
		for (int iC = 0; iC<nC; iC++)
		{
			switch (initialization)
			{
			case MI_ZEROS: values[iR][iC] = 0;
				break;
			case MI_ONES: values[iR][iC] = 1;
				break;
			case MI_EYE: values[iR][iC] = (iR == iC) ? 1 : 0;
				break;
			case MI_RAND: values[iR][iC] = (rand() % 100);// / 100.0;
				break;
			case MI_VALUE: values[iR][iC] = initializationValue;
				break;
			}
		}
	}
}
CMatrix::CMatrix(int nR, int nC, double first, ...) // Beshoy
{
	this->nR = nR;
	this->nC = nC;
	if ((nR*nC) == 0)
	{
		values = NULL; return;
	}
	values = new double*[nR];
	va_list va;
	va_start(va, first);
	for (int iR = 0; iR<nR; iR++)
	{
		values[iR] = new double[nC];
		for (int iC = 0; iC<nC; iC++)
		{
			values[iR][iC] = (iC == 0 && iR == 0) ? first : va_arg(va, double);
		}
	}
	va_end(va);
}
CMatrix::CMatrix(CMatrix& m) // Beshoy
{
	nR = nC = 0;
	values = NULL;
	copy(m);
}
CMatrix::CMatrix(string s) // Beshoy
{
	nR = nC = 0;
	values = NULL;
	copy(s);
}

CMatrix::CMatrix(double d) // Beshoy
{
	nR = nC = 0;
	values = NULL;
	copy(d);
}


void CMatrix::reset() { // Boula
	if (values) {
		for (int i = 0; i<nR; i++)
			delete[] values[i];
		delete[] values;
	}
	nR = nC = 0;
	values = NULL;
}
void CMatrix::copy(const CMatrix& m) { // Boula
	reset();
	this->nR = m.nR;
	this->nC = m.nC;
	if ((nR*nC) == 0) { values = NULL; return; }
	values = new double*[nR];
	for (int iR = 0; iR<nR; iR++) {
		values[iR] = new double[nC];
		for (int iC = 0; iC<nC; iC++) values[iR][iC] = m.values[iR][iC];
	}
}
void CMatrix::copy(double d) { // Boula
	reset();
	this->nR = 1;
	this->nC = 1;
	values = new double*[1];
	values[0] = new double[1];
	values[0][0] = d;
}
#include <iostream>
void CMatrix::copy(string s) { // Boula
	reset();
	char buffer;
	string temp_matrix[100][100]; // this limits the matrix to 100*100
	int c = 0, nr = 0, nc = 0;
	bool trueLine = false;
	bool trueColoum = false;
	for (unsigned int i = 0; i < s.length(); i++) {
		buffer = s[i];
		if (buffer == ' ' && temp_matrix[nr][c].length() != 0) { c++; trueColoum = false; if (c > nc) nc = c; }
		else if (buffer == ';') { if (!trueColoum) nc--; nr++; trueLine = false; c = 0; }
		else if (buffer == '[' || buffer == ']' || buffer == ' ');
		else {
			trueLine = true;
			trueColoum = true;
			temp_matrix[nr][c] += buffer;
		}
	}
	if (!trueLine) nr--;
	if (!trueColoum) nc--;
	nR = nr + 1; nC = nc + 1;
	values = new double*[nR];
	for (int iR = 0; iR<nR; iR++)
	{
		values[iR] = new double[nC];
		for (int iC = 0; iC<nC; iC++)
		{
			values[iR][iC] = atof(temp_matrix[iR][iC].c_str());
		}
	}
}
#include <sstream>
/*template <typename T> string to_string(const T& t) {
	ostringstream os;
	os << t;
	return os.str();
}*/
string to_string(const int& t) {
	ostringstream os;
	os << t;
	return os.str();
}
string to_string(const double& t) {
	ostringstream os;
	os << t;
	return os.str();
}
string to_string_with_precision(double value, int n = 6)
{
	
	string sValue = to_string(value);
	if (value < 0) {
		value *= -1;
		n++;
	}

	if (value>99999999.99999999) sValue = sValue.substr(0, n + 10);
	else if (value>9999999.99999999) sValue = sValue.substr(0, n + 9);
	else if (value>999999.99999999) sValue = sValue.substr(0, n + 8);
	else if (value>99999.99999999) sValue = sValue.substr(0, n + 7);
	else if (value>9999.99999999) sValue = sValue.substr(0, n + 6);
	else if (value>999.99999999) sValue = sValue.substr(0, n + 5);
	else if (value>99.99999999) sValue = sValue.substr(0, n + 4);
	else if (value>9.99999999) sValue = sValue.substr(0, n + 3);
	else sValue = sValue.substr(0, n + 2);
	return sValue;
}
#include <stdio.h>
//#include <time.h>
string CMatrix::getOriginalString() { // Boula
	string s = "[";
	for (int iR = 0; iR<nR; iR++) {
		for (int iC = 0; iC<nC; iC++) {
			s += " ";
			s += to_string_with_precision(values[iR][iC], 2);
		}
		s += ";";
	}
	s = "[" + s.substr(2, s.length() - 3) + "]";
	return s;
}
string CMatrix::getString() { // Boula
	//int t1 = clock();
	/*string ss = "[";
	for (int iR = 0; iR<nR; iR++) {
		for (int iC = 0; iC<nC; iC++) {
			ss += " ";
			ss += to_string_with_precision(values[iR][iC], 2);
		}
		ss += ";";
	}
	ss = "[" + ss.substr(2, ss.length() - 3) + "]";
	cout << clock() - t1 << endl;
	return s;*/
	//int t2 = clock();
	const int columnsToPrintEachTime = 7;
	int printedColumns = 0;
	string s = "\n";
	bool biggerThanSix = nC > columnsToPrintEachTime;
	while (printedColumns < nC) {
		if (biggerThanSix && ((nC - printedColumns) >= columnsToPrintEachTime)) s += "\tColumns " + to_string(printedColumns + 1) + " through " + to_string(printedColumns + columnsToPrintEachTime) + ":\n";
		else if (nC > columnsToPrintEachTime) s += "\tColumns " + to_string(printedColumns + 1) + " through " + to_string(nC) + ":\n";
		int columnsToPrint = ((nC - printedColumns) >= columnsToPrintEachTime)? columnsToPrintEachTime : nC - printedColumns;
		for(int iR=0;iR<nR;iR++)
		{
			if (biggerThanSix) s += "\t\t"; else s += "\t";
			for(int iC=0; iC<columnsToPrint; iC++)
			{
				char buffer[50];
				snprintf(buffer, 50, "%g\t", values[iR][printedColumns + iC]);
				s += buffer;
			}
			s += "\n";
		}
		printedColumns += columnsToPrintEachTime; s+= "\n";
	}
	//cout << clock() - t2 << endl;
	return s;
}
CMatrix CMatrix::denominatorOfDiv(float f) { // Boula
	CMatrix temp(nR, nC);
	for (int iR = 0; iR < temp.nR; iR++) {
		for (int iC = 0; iC < temp.nC; iC++) {
			temp.values[iR][iC] = f / values[iR][iC];
		}
	}
	return temp;
}

//core functions

void CMatrix::add(CMatrix& m) //peter
{
	if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			values[iR][iC] += m.values[iR][iC];
}


void CMatrix::sub(CMatrix& m) //peter
{
	if (nR != m.nR || nC != m.nC)
		throw("Invalid matrix dimension");
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			values[iR][iC] -= m.values[iR][iC];
}


void CMatrix::mul(CMatrix& m) //peter
{
	//cout << nR << "*" << nC << " " << m.nR << "*" << m.nC << endl;
	if (nC != m.nR)
		throw("Invalid matrix dimension");
	CMatrix r(nR, m.nC);
	for (int iR = 0; iR<r.nR; iR++)
		for (int iC = 0; iC<r.nC; iC++)
		{
			r.values[iR][iC] = 0;
			for (int k = 0; k<m.nC; k++)
				r.values[iR][iC] += values[iR][k] * m.values[k][iC];
		}
	copy(r);
}

void CMatrix::div(CMatrix& m) {
	double Determinant = m.getDeterminant();
	if (Determinant == 0) throw("No unique solution");
	CMatrix x;
	x.copy(m.getInverse());
	mul(x);
	
}
CMatrix CMatrix::getCofactor(int r, int c) //peter
{
	if (nR <= 1 && nC <= 1)
		throw("Invalid matrix dimension");
	CMatrix m(nR - 1, nC - 1);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
		{
			int sR = (iR<r) ? iR : iR + 1;
			int sC = (iC<c) ? iC : iC + 1;
			m.values[iR][iC] = values[sR][sC];
		}
	return m;
}
#include <cmath>
double CMatrix::getDeterminant() //peter
{
	CMatrix m = *this;
	if (nR != nC)throw("Invalid matrix dimension");
	if (nR == 1 && nC == 1)
		return m.values[0][0];

	//checking the cases of zero determenant 
	//first case
	for (int i = 0; i<nR; i++)
	{
		for (int k = i + 1; k<nR; k++)
		{
			int zeroflag = 1;
			double Ratio = values[i][0] / values[k][0];
			int Ratioflag = 1;
			for (int j = 0; j<nC; j++)
			{
				if (Ratio != values[i][j] / values[k][j]) Ratioflag = 0;
				if (values[i][j] != 0) zeroflag = 0;
			}
			if (zeroflag == 1) return 0;
			if (Ratioflag == 1) return 0;
		}
	}
	//second case
	for (int i = 0; i<nR; i++)
	{
		for (int k = i + 1; k<nR; k++)
		{
			int zeroflag = 1;
			double Ratio = values[0][i] / values[0][k];
			int Ratioflag = 1;
			for (int j = 0; j<nC; j++)
			{
				if (Ratio != values[j][i] / values[j][k]) Ratioflag = 0;
				if (values[j][i] != 0) zeroflag = 0;
			}
			if (zeroflag == 1) return 0;
			if (Ratioflag == 1) return 0;
		}
	}

	int i, k, j, flag = 0;
	for (i = 0; i<nR; i++)                    //Pivotisation
		for (k = i + 1; k<nR; k++)
			if (abs(values[i][i])<abs(values[k][i])) {
				flag++;
				for (j = 0; j<nR; j++) {
					double temp = m.values[i][j];
					m.values[i][j] = m.values[k][j];
					m.values[k][j] = temp;
				}
			}

	//cout << "\nThe matrix after Pivotisation is:\n";
	/*for (i = 0; i<nR; i++)            //print the new matrix
	{
	for (j = 0; j<nR; j++)
	cout << m.values[i][j] ;
	cout << "\n";
	}*/
	for (i = 0; i<nR - 1; i++)            //loop to perform the gauss elimination
		for (k = i + 1; k<nR; k++)
		{
			double t = m.values[k][i] / m.values[i][i];
			for (j = 0; j<nR; j++)
				m.values[k][j] = m.values[k][j] - t*m.values[i][j];    //make the elements below the pivot elements equal to zero or elimnate the variables
		}

	/*cout << "\n\nThe matrix after gauss-elimination is as follows:\n";
	for (i = 0; i<nR; i++)            //print the new matrix
	{
	for (j = 0; j < nR; j++)
	cout << m.values[i][j];
	cout << "\n";
	}*/
	double det = 1;
	for (i = 0; i<nR; i++) {
		det = det*m.values[i][i];
	}
	if (flag % 2 == 0) {
		det = det;
	}
	else {
		det = -det;
	}


	return det;

	/*
	double value = 0, m = 1;
	for (int iR = 0; iR<nR; iR++)
	{
	value += m * values[0][iR] * getCofactor(0, iR).getDeterminant(); m *= -1;
	}
	return value;*/
}



CMatrix CMatrix::getInverse() //peter
{
	if (nR != nC)throw("Invalid matrix dimension");
	double Determinant = getDeterminant();

	if (Determinant == 0) throw("Invalid matrix Inverse");
	CMatrix r(nR, nC);
	int m = 1;
	for (int iC = 0; iC<nC; iC++)
	{
		for (int iR = 0; iR<nR; iR++)
		{
			r.values[iC][iR] = m* (getCofactor(iR, iC).getDeterminant()) / Determinant;
			m *= -1;
		}
		if (nR % 2 == 0)
			m *= -1;
	}
	
	return r;
}

CMatrix CMatrix::getTranspose() //Mina Magdy
{
	CMatrix M(nC, nR);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iC][iR] = values[iR][iC];
	return M;
}

///////operators//////Hanaa
CMatrix CMatrix::operator=(const CMatrix& m)
{
	copy(m);
	return *this;
}
void CMatrix::operator+=(CMatrix& m)
{
	add(m);
}
CMatrix CMatrix::operator+(CMatrix& m)
{
	CMatrix r = *this;
	r += m;
	return r;
}
void CMatrix::operator-=(CMatrix& m)
{
	sub(m);
}
CMatrix CMatrix::operator-(CMatrix& m)
{
	CMatrix r = *this;
	r -= m;
	return r;
}
void CMatrix::operator*=(CMatrix& m)
{
	mul(m);
}
CMatrix CMatrix::operator*(CMatrix& m)
{
	CMatrix r = *this;
	r *= m;
	return r;
}
void CMatrix::operator/=(CMatrix& m)
{
	div(m);
}
CMatrix CMatrix::operator/(CMatrix& m)
{
	CMatrix r = *this;
	r /= m;
	return r;
}

// ===== PHASE TWO
void CMatrix::pow(double d) {} // Boula /* M^d is the d product of matrix M */
CMatrix sqrt(const CMatrix& m) {} // Boula /* Get square root of matrix m */

void CMatrix::dotMul(Const CMatrix& m) {
    if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
    CMatrix M(nR, nC);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iR][iC] *= this.values[iR][iC];
	
} // Mina Magdy /* (*this) .* m is multiple element by element as general result(i,j)=(*this)(i,j)*m(i,j) */
void CMatrix::dotDiv(CMatrix& m) {
    if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
    CMatrix M(nR, nC);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iR][iC] /= this.values[iR][iC];
	
} // Mina Magdy /* is a dot divide operation as divide element by element */
void CMatrix::dotPow(double d) {
    if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
    CMatrix M(nR, nC);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iR][iC] =  pow(M.values[iR][iC], this.values[iR][iC]);
	
} // Mina Magdy /* is a pow of each element to power of d */
void CMatrix::lDiv(const CMatrix& m) {
    double Determinant = m.getDeterminant();
	if (Determinant == 0) throw("No unique solution");
	if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
	m.copy(m.getInverse());
	this.mul(m);
    
} // Mina Magdy /* multiply of inverse(A)*B and is called left div */
void CMatrix::dotLDiv(const CMatrix& m) {} // Mina Magdy /* Element by element multiply of inverse of *this and m */
CMatrix sin(const CMatrix& m) {
    CMatrix M(nR, nC);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iR][iC] = this.sin(values[iR][iC]);
	return M;
} // Mina Magdy /* Get sin for each element */
CMatrix cos(const CMatrix& m) {
    CMatrix M(nR, nC);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iR][iC] = this.cos(values[iR][iC]);
	return M;
} // Mina Magdy /* Get cos for each element */
CMatrix tan(const CMatrix& m) {
    CMatrix M(nR, nC);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iR][iC] = this.tan(values[iR][iC]);
	return M;
} // Mina Magdy /* Get tan for each element */
CMatrix asin(const CMatrix& m) {
    CMatrix M(nR, nC);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iR][iC] = this.asin(values[iR][iC]);
	return M;
} // Mina Magdy /* Get sin-1 for each element */
CMatrix acos(const CMatrix& m) {
    CMatrix M(nR, nC);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iR][iC] = this.acos(values[iR][iC]);
	return M;
} // Mina Magdy /* Get cos-1 for each element*/
CMatrix atan(const CMatrix& m) {
    CMatrix M(nR, nC);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iR][iC] = this.atan(values[iR][iC]);
	return M;
} // Mina Magdy /* Get tan-1 for each element */
CMatrix exp(const CMatrix& m) {
    CMatrix M(nR, nC);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iR][iC] = this.exp(values[iR][iC]);
	return M;

} // Mina Magdy /* Get expontial of each element */
CMatrix log(const CMatrix& m) {
    CMatrix M(nR, nC);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iR][iC] = this.log(values[iR][iC]);
	return M;

} // Mina Magdy /* Get the ln of each element */
CMatrix log10(const CMatrix& m) {
    CMatrix M(nR, nC);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iR][iC] = this.log10(values[iR][iC]);
	return M;

} // Mina Magdy /* Get the log to base 10 of each element */

CMatrix CMatrix::operator==(const CMatrix& m) {} // George /* Return matrix contain condition to check if each element in *this is equal to the corresponding element in m */
CMatrix CMatrix::operator!=(const CMatrix& m) {} // George /* If not equal*/
CMatrix CMatrix::operator<(const CMatrix& m) {} // George /* If less than */
CMatrix CMatrix::operator<=(const CMatrix& m) {} // George /* If less than or equal */
CMatrix CMatrix::operator>(const CMatrix& m) {} // George /* If larger than */
CMatrix CMatrix::operator>=(const CMatrix& m) {} // George /* If larger than or equal */

CMatrix CMatrix::operator\(const CMatrix& m) {} // George /* Left Divide opeartor */
CMatrix CMatrix::operator\=(const CMatrix& m) {} // George /* left divide and update the value of *this operator */

CMatrix CMatrix::operator&(const CMatrix& m) {} // George /* Element by element anding */
CMatrix CMatrix::operator|(const CMatrix& m) {} // George /* Element by element oring */
CMatrix CMatrix::operator~(const CMatrix& m) {} // George /* Element by element complement */

CMatrix CMatrix::operator.*(const CMatrix& m) {} // George /* Dot multipy */
CMatrix CMatrix::operator./(const CMatrix& m) {} // George /* Dot divide */
CMatrix CMatrix::operator.\(const CMatrix& m) {} // George /* Dot left divide */
CMatrix CMatrix::operator.^(const CMatrix& m) {} // George /* Dot power */
CMatrix CMatrix::operator.*=(const CMatrix& m) {} // George /* Dot multipy and update *this */
CMatrix CMatrix::operator./=(const CMatrix& m) {} // George /* Dot divide and update *this */
CMatrix CMatrix::operator.\=(const CMatrix& m) {} // George /* Dot left and update *this */
CMatrix CMatrix::operator.^=(const CMatrix& m) {} // George /* Dot power and update *this */

/* The next 8 is the same as previous but take double */
CMatrix CMatrix::operator.*(double& d) {} // George
CMatrix CMatrix::operator./(double& d) {} // George
CMatrix CMatrix::operator.\(double& d) {} // George
CMatrix CMatrix::operator.^(double& d) {} // George
CMatrix CMatrix::operator.*=(double& d) {} // George
CMatrix CMatrix::operator./=(double& d) {} // George
CMatrix CMatrix::operator.\=(double& d) {} // George
CMatrix CMatrix::operator.^=(double& d) {} // George
