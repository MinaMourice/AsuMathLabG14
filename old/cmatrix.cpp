#include "stdafx.h"
#include "cmatrix.h"
#include "pcomplexlib.h"
#include <math.h>
#include <cmath>
#include <stdarg.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
CMatrix::CMatrix()
{
	nR = nC = 0; values = NULL;
}
CMatrix::~CMatrix()
{
	reset();
}

CMatrix::CMatrix(int nR, int nC, int initialization, double initializationValue) 

{
	this->nR = nR;
	this->nC = nC;
	if ((nR*nC) == 0)
	{
		values = NULL; return;
	}

	values = new double*[nR];
	for (int iR = 0; iR < nR; iR++)
	{
		values[iR] = new double[nC];

		for (int iC = 0; iC < nC; iC++)
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

CMatrix::CMatrix(int nR, int nC, double first, ...) 

{
	this->nR = nR;
	this->nC = nC;
	if ((nR*nC) == 0)
	{
		values = NULL; return;
	}
	values = new complex*[nR];
	va_list va;
	va_start(va, first);
	for (int iR = 0; iR < nR; iR++)
	{

		values[iR] = new double[nC];

		for (int iC = 0; iC < nC; iC++)
		{
			values[iR][iC] = (iC == 0 && iR == 0) ? first : va_arg(va, complex);
		}
	}
	va_end(va);
}
CMatrix::CMatrix(CMatrix& m) 
{
	nR = nC = 0;
	values = NULL;
	copy(m);
}
CMatrix::CMatrix(string s)
{
	nR = nC = 0;
	values = NULL;
	copy(s);
}

CMatrix::CMatrix(double d) 
{
	nR = nC = 0;
	values = NULL;
	copy(d);
}


void CMatrix::reset() { 

	if (values) {
		for (int i = 0; i < nR; i++)
			delete[] values[i];
		delete[] values;
	}
	nR = nC = 0;
	values = NULL;
}
void CMatrix::copy(const CMatrix& m) { 
	reset();
	this->nR = m.nR;
	this->nC = m.nC;
	if ((nR*nC) == 0) { values = NULL; return; }

	values = new double*[nR];
	for (int iR = 0; iR < nR; iR++) {
		values[iR] = new double[nC];
		for (int iC = 0; iC < nC; iC++) values[iR][iC] = m.values[iR][iC];
	}
}
void CMatrix::copy(double d) { 

	reset();
	this->nR = 1;
	this->nC = 1;
	values = new complex*[1];
	values[0] = new complex[1];
	values[0][0] = d;
}
void CMatrix::copy(string s) { 
	reset();
	char buffer;

	// Cuts the string from [ to ]
	int indicator1 = s.find('[');
	int indicator2 = s.find(']');
	s = s.substr(indicator1, indicator2 + 1);

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
	for (int iR = 0; iR < nR; iR++)
	{
		values[iR] = new double[nC];

		for (int iC = 0; iC < nC; iC++)
		{
			values[iR][iC] = atof(temp_matrix[iR][iC].c_str());
		}
	}
}
/*template <typename T> string to_string(const T& t) {
ostringstream os;
os << t;
return os.str();
}*/

/*
string to_string(const int& t) {

	ostringstream os;
	os << t;
	return os.str();
}
string to_string(const complex& t) {
	ostringstream os;
	os << t;
	return os.str();
}*/

/*string to_string_with_precision(double value, int n = 6)

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
}*/
string CMatrix::getOriginalString() {
	string s = "[";
	for (int iR = 0; iR < nR; iR++) {
		for (int iC = 0; iC < nC; iC++) {
			s += " ";
			//s += to_string_with_precision(values[iR][iC], 2);
			s += to_string(values[iR][iC]);
		}
		s += ";";
	}
	s = "[" + s.substr(2, s.length() - 3) + "]";
	return s;
}

#include <windows.h>
string CMatrix::getString(const int columnsToPrintEachTimeIn) { // Boula
															  // support up to 99*99 matrix
	if (nR == 0 || nC == 0) return "\n        [empty]\n";

	int columnsToPrintEachTime = columnsToPrintEachTimeIn;
	int columnSize = 20 - 2 * columnsToPrintEachTime;
	if (columnsToPrintEachTimeIn < 1) {
		int maxElementWidth = to_string(values[0][0]).length();
		for (int iR = 0; iR < nR; iR++)
			for (int iC = 0; iC < nC; iC++)
				if (to_string(values[iR][iC]).length() > maxElementWidth) maxElementWidth = to_string(values[iR][iC]).length();

		int terminalColumns;
		This is here to give you an error!
		// Uncomment the code required per your operating system only!
		
		// If windows
		/*CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		terminalColumns = csbi.srWindow.Right - csbi.srWindow.Left + 1;*/
		
		// If linux
		/*struct winsize size;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		terminalColumnWidth = size.ws_col;*/

		columnSize = maxElementWidth + 1;
		int rowReservedSpace = 8 + 9 + 8;
		columnsToPrintEachTime = ((terminalColumns - rowReservedSpace) / columnSize);
		if (columnsToPrintEachTime < 1) columnsToPrintEachTime = 1;
	}


	int columnSize = 20 - 2 * columnsToPrintEachTime;
	int printedColumns = 0;
	string s = "\n";
	bool biggerThanSix = nC > columnsToPrintEachTime;
	while (printedColumns < nC) {

		if (biggerThanSix && ((nC - printedColumns) >= columnsToPrintEachTime)) s += "        Columns " + to_string(printedColumns + 1) + " through " + to_string(printedColumns + columnsToPrintEachTime) + ":\n";
		else
		{
			if (printedColumns + 1 != nC) s += "        Columns " + to_string(printedColumns + 1) + " through " + to_string(nC) + ":\n";
			else s += "        Column " + to_string(printedColumns + 1) + ":\n";

		}
		int columnsToPrint = ((nC - printedColumns) >= columnsToPrintEachTime) ? columnsToPrintEachTime : nC - printedColumns;
		for (int iR = 0; iR < nR; iR++)
		{

			if (biggerThanSix) s += "        Row " + to_string(iR + 1) + ": "; else s += "        Row " + to_string(iR + 1) + ": ";
			if (iR < 9 && nR >= 9) s += " "; // 9 is row number 10
			s += "        ";
    
			for (int iC = 0; iC < columnsToPrint; iC++)
			{
				string k;
				if (values[iR][printedColumns + iC] >= 0.00) k = " ";
				k += to_string(values[iR][printedColumns + iC]);
				int sLength = k.length();
				s += k;
				for (int i = sLength; i < columnSize && iC != columnsToPrint - 1; i++) s += " ";
			}
			s += "\n";
		}
		printedColumns += columnsToPrintEachTime; s += "\n";
	}
	return s;
}
CMatrix CMatrix::denominatorOfDiv(float f) { 
	CMatrix temp(nR, nC);
	for (int iR = 0; iR < temp.nR; iR++) {
		for (int iC = 0; iC < temp.nC; iC++) {
			temp.values[iR][iC] = f / values[iR][iC];
		}
	}
	return temp;
}



void CMatrix::add(CMatrix& m) 
{
	if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
	for (int iR = 0; iR < nR; iR++)
		for (int iC = 0; iC < nC; iC++)
			values[iR][iC] += m.values[iR][iC];
}
void CMatrix::sub(CMatrix& m) 

{
	if (nR != m.nR || nC != m.nC)
		throw("Invalid matrix dimension");
	for (int iR = 0; iR < nR; iR++)
		for (int iC = 0; iC < nC; iC++)
			values[iR][iC] -= m.values[iR][iC];
}

void CMatrix::mul(CMatrix& m) 
{
	//cout << nR << "*" << nC << " " << m.nR << "*" << m.nC << endl;
	if (nC != m.nR)
		throw("Invalid matrix dimension");
	CMatrix r(nR, m.nC);
	for (int iR = 0; iR < r.nR; iR++)
		for (int iC = 0; iC < r.nC; iC++)
		{
			r.values[iR][iC] = 0;
			for (int k = 0; k < m.nC; k++)
				r.values[iR][iC] += values[iR][k] * m.values[k][iC];
		}
	copy(r);
}
void CMatrix::div(CMatrix& m) {
	//complex Determinant = m.getDeterminant();
	//if (Determinant == 0) { cout << "No unique solution\n"; return; throw("No unique solution"); }
	CMatrix x;
	x.copy(m.getInverse());
	mul(x);

}
CMatrix CMatrix::lDiv(CMatrix& m) {
	double Determinant = this->getDeterminant();
	if (Determinant == 0) throw("No unique solution");
	if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
	CMatrix x;
	x.copy(this->getInverse());
	x.mul(m);
	return x;
}
CMatrix CMatrix::dotMul(CMatrix& m) {
	if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
	CMatrix M(nR, nC);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iR][iC] = (this->values[iR][iC])*(m.values[iR][iC]);
	return M;
}
CMatrix CMatrix::dotDiv(CMatrix& m) {
	if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
	CMatrix M(nR, nC);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iR][iC] = (this->values[iR][iC])/(m.values[iR][iC]);
	return M;
}
CMatrix CMatrix::dotPow(double d) {
	CMatrix M(nR, nC);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iR][iC] = pow(this->values[iR][iC], d);
	return M;
}

CMatrix CMatrix::dotLDiv(CMatrix& m) {
	if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
	CMatrix M(nR, nC);
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			M.values[iR][iC] = (m.values[iR][iC])/(this->values[iR][iC]);
	return M;
}
CMatrix CMatrix::getCofactor(int r, int c) 
{
	if (nR <= 1 && nC <= 1)
		throw("Invalid matrix dimension");
	CMatrix m(nR - 1, nC - 1);
	for (int iR = 0; iR < m.nR; iR++)
		for (int iC = 0; iC < m.nC; iC++)
		{
			int sR = (iR < r) ? iR : iR + 1;
			int sC = (iC < c) ? iC : iC + 1;
			m.values[iR][iC] = values[sR][sC];
		}
	return m;
}
void CMatrix::swapRow(int row1, int row2) {
	complex tmp;

	if (row1 == row2) return;
	for (int i = 0; i < nC; i++) {
		tmp = values[row1][i];
		values[row1][i] = values[row2][i];
		values[row2][i] = tmp;
	}
}
complex CMatrix::getDeterminant() {
	CMatrix m = *this;

	if (m.nR != m.nC)throw("Invalid matrix dimension");
	if (m.nR == 1 && m.nC == 1)
		return m.values[0][0];

	//checking the cases of zero determenant 
	//first case
	for (int i = 0; i < nR; i++)
	{
		for (int k = i + 1; k < nR; k++)
		{
			int zeroflag = 1;
			complex Ratio = m.values[i][0] / m.values[k][0];
			int Ratioflag = 1;
			for (int j = 0; j < nC; j++)
			{
				if (Ratio != m.values[i][j] / m.values[k][j]) Ratioflag = 0;
				if (m.values[i][j] != 0) zeroflag = 0;
			}
			if (zeroflag == 1) return 0;
			if (Ratioflag == 1) return 0;
		}
	}
	//second case
	for (int i = 0; i < nR; i++)
	{
		for (int k = i + 1; k < nR; k++)
		{
			int zeroflag = 1;
			complex Ratio = m.values[0][i] / m.values[0][k];
			int Ratioflag = 1;
			for (int j = 0; j < nC; j++)
			{
				if (Ratio != m.values[j][i] / m.values[j][k]) Ratioflag = 0;
				if (m.values[j][i] != 0) zeroflag = 0;
			}
			if (zeroflag == 1) return 0;
			if (Ratioflag == 1) return 0;
		}
	}

	int maxRow;
	complex max, temp;
	int sign = 1;
	for (int dia = 0; dia < nR; dia++) {
		maxRow = dia, max = abs(m.values[dia][dia]);

		for (int iR = dia + 1; iR < nR; iR++) {
			temp = abs(m.values[iR][dia]);
			if (temp > max)
				maxRow = iR, max = temp;
		}

		if ((dia != maxRow) || (abs(m.values[dia][dia]) <= 0.0000000000000000001)) {
			m.swapRow(dia, maxRow);
			sign *= -1;
		}


		for (int iR = dia + 1; iR < nR; iR++) {
			temp = m.values[iR][dia] / m.values[dia][dia];
			for (int iC = dia + 1; iC < nC; iC++)
				m.values[iR][iC] -= temp * m.values[dia][iC];
			m.values[iR][dia] = 0;
		}
	}

	complex determinant = 1.0;
	for (int i = 0; i < nR; i++) determinant *= m.values[i][i];

	return sign * determinant;
}


CMatrix CMatrix::getInverse() 
{
	if (nR != nC)throw("Invalid matrix dimension");
	complex Determinant = getDeterminant();
	if (Determinant == 0) throw("Invalid matrix Inverse");
	CMatrix r(nR, nC);
	int m = 1;
	for (int iC = 0; iC < nC; iC++)
	{
		for (int iR = 0; iR < nR; iR++)
		{
			r.values[iC][iR] = m* (getCofactor(iR, iC).getDeterminant()) / Determinant;
			/*//comment
			if (isnan(r.values[iC][iR])) {
			cout << "element " << iC << " " << iR << " is nan! with determinant = " << getCofactor(iR, iC).getDeterminant() << endl;
			cout << getCofactor(iR, iC).getOriginalString() << endl;
			}
			else if (isinf(r.values[iC][iR])) {
			cout << "element " << iC << " " << iR << " is inf! with determinant = " << getCofactor(iR, iC).getDeterminant() << endl;
			cout << getCofactor(iR, iC).getOriginalString() << endl;
			}
			//comment*/
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
	for (int iR = 0; iR < nR; iR++)
		for (int iC = 0; iC < nC; iC++)
			M.values[iC][iR] = values[iR][iC];
	return M;
}


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
CMatrix sin(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = sin(m.values[iR][iC]);
	return M;

}
CMatrix cos(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = cos(m.values[iR][iC]);
	return M;

}
CMatrix tan(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = tan(m.values[iR][iC]);
	return M;

}
CMatrix csc(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = 1.0 / sin(m.values[iR][iC]);
	return M;

}
CMatrix sec(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = 1.0 / cos(m.values[iR][iC]);
	return M;

}
CMatrix cot(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = 1.0 / tan(m.values[iR][iC]);
	return M;

}

CMatrix asin(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = asin(m.values[iR][iC]);
	return M;

}
CMatrix acos(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = acos(m.values[iR][iC]);
	return M;

}
CMatrix atan(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = atan(m.values[iR][iC]);
	return M;

}
CMatrix acsc(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = asin(1.0 / m.values[iR][iC]);
	return M;

}
CMatrix asec(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = acos(1.0 / m.values[iR][iC]);
	return M;

}
CMatrix acot(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = atan(1.0 / m.values[iR][iC]);
	return M;

}
CMatrix sinh(const CMatrix& m)
{
	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC < m.nC; iC++)
			M.values[iR][iC] = sinh(m.values[iR][iC]);
	
	return M;

}
CMatrix cosh(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = cosh(m.values[iR][iC]);
	return M;

}
CMatrix tanh(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = tanh(m.values[iR][iC]);
	return M;

}
CMatrix csch(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = 1.0 / sinh(m.values[iR][iC]);
	return M;

}
CMatrix sech(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = 1.0 / cosh(m.values[iR][iC]);
	return M;

}
CMatrix coth(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = 1.0 / tanh(m.values[iR][iC]);
	return M;

}

CMatrix asinh(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = asinh(m.values[iR][iC]);
	return M;

}
CMatrix acosh(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = acosh(m.values[iR][iC]);
	return M;

}
CMatrix atanh(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = atanh(m.values[iR][iC]);
	return M;

}
CMatrix acsch(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = asinh(1.0 / m.values[iR][iC]);
	return M;

}
CMatrix asech(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = acosh(1.0 / m.values[iR][iC]);
	return M;

}
CMatrix acoth(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = atanh(1.0 / m.values[iR][iC]);
	return M;

}
CMatrix exp(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = exp(m.values[iR][iC]);
	return M;

}
CMatrix log(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = log(m.values[iR][iC]);
	return M;

}
CMatrix log10(const CMatrix& m)
{

	CMatrix M(m.nR, m.nC);
	for (int iR = 0; iR<m.nR; iR++)
		for (int iC = 0; iC<m.nC; iC++)
			M.values[iR][iC] = log10(m.values[iR][iC]);
	return M;

}

