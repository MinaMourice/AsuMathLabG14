#include "stdafx.h"
#include "cmatrix.h"
#include "pcomplexlib.h"
#include <iostream>

CMatrix CMatrix::subMatrix(const int& rowToStartAt, const int& columnToStartAt, const int& rowsNo, const int& columnsNo) {
	CMatrix temp(rowsNo, columnsNo);
	int temprow;
	for (int iR = 0; iR < rowsNo; iR++) {
		temprow = rowToStartAt + iR;
		for (int iC = 0; iC < columnsNo; iC++)
			temp.values[iR][iC] = values[temprow][columnToStartAt+iC];
	}
	return temp;
}
CMatrix concatinate(const CMatrix& mat11, const CMatrix& mat12, const CMatrix& mat21, const CMatrix& mat22) {
	int nR = mat11.nR + mat21.nR;
	int nC = mat11.nC + mat12.nC;
	if (nR != mat12.nR + mat22.nR || nC != mat21.nC + mat22.nC) throw("concatination failed!");
	CMatrix result(nR, nC);
	for (int iR = 0; iR < mat11.nR; iR++)
		for (int iC = 0; iC < mat11.nC; iC++)
			result.values[iR][iC] = mat11.values[iR][iC];
	for (int iR = 0; iR < mat12.nR; iR++)
		for (int iC = 0; iC < mat12.nC; iC++)
			result.values[iR][mat11.nC + iC] = mat12.values[iR][iC];
	for (int iR = 0; iR < mat21.nR; iR++)
		for (int iC = 0; iC < mat21.nC; iC++)
			result.values[mat11.nR + iR][iC] = mat21.values[iR][iC];
	for (int iR = 0; iR < mat22.nR; iR++)
		for (int iC = 0; iC < mat22.nC; iC++)
			result.values[mat12.nR + iR][mat21.nC + iC] = mat22.values[iR][iC];
	return result;
}
void CMatrix::smul(CMatrix& m) {
	if (nC != m.nR)
		throw("Invalid matrix dimension");

	if (nC <= 4) {
		CMatrix r(nR, m.nC);
		for (int iR = 0; iR < r.nR; iR++)
			for (int iC = 0; iC < r.nC; iC++)
			{
				r.values[iR][iC] = 0;
				for (int k = 0; k < m.nC; k++)
					r.values[iR][iC] += values[iR][k] * m.values[k][iC];
			}

		copy(r);
		return;
	}

	CMatrix mat1 = *this;
	CMatrix mat2 = m;
	double log2Result = 1;
	complex isThereAnyFloatingReminderToLog2Operation = modf(log2(mat1.nC), &log2Result);
	if (mat1.nC != mat1.nR || mat2.nC != mat2.nR || isThereAnyFloatingReminderToLog2Operation > 0.0) {
		int padSize = log2Result;
		while (padSize < mat1.nC || padSize < mat1.nR || padSize < mat2.nC || padSize < mat2.nR) {
			padSize *= 2;
		}
		mat1 = CMatrix(padSize, padSize);
		mat2 = CMatrix(padSize, padSize);
		for (int iR = 0; iR < nR; iR++)
			for (int iC = 0; iC < nC; iC++)
				mat1.values[iR][iC] = values[iR][iC];
		for (int iR = 0; iR < m.nR; iR++)
			for (int iC = 0; iC < m.nC; iC++)
				mat2.values[iR][iC] = m.values[iR][iC];
	}

	int subMatrixN = mat1.nC / 2;
	CMatrix a11, a12, a21, a22, b11, b12, b21, b22;
	a11 = mat1.subMatrix(0, 0, subMatrixN, subMatrixN);
	a12 = mat1.subMatrix(0, subMatrixN, subMatrixN, subMatrixN);
	a21 = mat1.subMatrix(subMatrixN, 0, subMatrixN, subMatrixN);
	a22 = mat1.subMatrix(subMatrixN, subMatrixN, subMatrixN, subMatrixN);
	b11 = mat2.subMatrix(0, 0, subMatrixN, subMatrixN);
	b12 = mat2.subMatrix(0, subMatrixN, subMatrixN, subMatrixN);
	b21 = mat2.subMatrix(subMatrixN, 0, subMatrixN, subMatrixN);
	b22 = mat2.subMatrix(subMatrixN, subMatrixN, subMatrixN, subMatrixN);
	CMatrix m1, m2, m3, m4, m5, m6, m7;
	m1 = (a11 + a22) * (b11 + b22);
	m2 = (a21 + a22) * b11;
	m3 = a11 * (b12 - b22);
	m4 = a22 * (b21 - b11);
	m5 = (a11 + a12) * b22;
	m6 = (a21 - a11) * (b11 + b12);
	m7 = (a12 - a22) * (b21 + b22);
	CMatrix c11, c12, c21, c22;
	c11 = m1 + m4 - m5 + m7;
	c12 = m3 + m5;
	c21 = m2 + m4;
	c22 = m1 - m2 + m3 + m6;
	CMatrix result;
	result = concatinate(c11, c12, c21, c22);
	if (nR < c11.nR + c21.nR || m.nC < c11.nC + c12.nC) result = result.subMatrix(0, 0, nR, m.nC);
	copy(result);
}

// Diagonal matrices powers
bool isdiagonal(const CMatrix& mat) {
	bool matDiagonal = true;
	for (int iR = 1; iR < mat.nR && matDiagonal; iR++)
		for (int iC = 0; iC < iR && matDiagonal; iC++)
			if (!(iR == iC))
				if (mat.values[iR][iC] != 0 || mat.values[iC][iR] != 0) matDiagonal = false;

	return  matDiagonal;
}
CMatrix diagPow(const CMatrix& mat, const complex& d) {
	CMatrix temp;
	temp = mat;
	for (int iR = 0; iR < temp.nR; iR++) {
		temp.values[iR][iR] = pow(temp.values[iR][iR], d);
		cout << temp.values[iR][iR] << " ";
	}
	cout << endl;
	return temp;
}

// this contains how to validate the eigen values and vector.
bool issymmetric(const CMatrix& mat) {
	bool matSymmetric = true;
	for (int iR = 1; iR < mat.nR && matSymmetric; iR++)
		for (int iC = 0; iC < iR && matSymmetric; iC++)
			if (!(iR == iC))
				if (mat.values[iR][iC] != mat.values[iC][iR]) matSymmetric = false;

	return  matSymmetric;
}
void jacobiEigenAnalysis(const CMatrix matrix, const int& maxIterations, CMatrix& eigenVectors, complex eigenValues[], int &iteraNo, int &rotationsNo) {

	CMatrix mat;
	mat = matrix;
	eigenVectors = CMatrix(mat.nR, mat.nR, 2);

	complex *diagValues;
	diagValues = new complex[mat.nR];
	complex *results;
	results = new complex[mat.nR];

	// Put values of the diagonal in the eigenValues and diagValues
	for (int i = 0; i < mat.nR; i++) {
		eigenValues[i] = mat.values[i][i];
		diagValues[i] = mat.values[i][i];
		results[i] = 0.0;
	}

	iteraNo = 0;
	rotationsNo = 0;
	while (iteraNo < maxIterations) {
		iteraNo ++;

		complex threshhold = 0.0; // essentially the value of the elements around the diagonal
		for (int i = 0; i < mat.nR; i++) {
			for (int j = 0; j < i; j++) {
				threshhold += mat.values[i][j] * mat.values[i][j];
			}
		}
		threshhold = sqrt(threshhold) / (complex)(4.0 * mat.nR);

		if (threshhold == 0.0) // The break condition
			break;

		for (int p = 0; p < mat.nR; p++) {
			for (int q = p + 1; q < mat.nC; q++) { // working on the upper triangler part of the matrix
				complex elementValue = 10.0 * abs(mat.values[p][q]);
				complex termOne = elementValue + abs(eigenValues[p]);
				complex termTwo = elementValue + abs(eigenValues[q]);

				if (iteraNo > 4 && termOne == abs(eigenValues[p]) && termTwo == abs(eigenValues[q])) // if [p][q] is so small with respect to its two eigen values, we remove it
					mat.values[p][q] = 0.0;
				else if (threshhold <= abs(mat.values[p][q])) { // if [p][q] is big, We rotate the matrix
					complex eigenDiffernace = eigenValues[q] - eigenValues[p];
					complex temp;
					complex term = abs(eigenDiffernace) + elementValue;
					if (term == abs(eigenDiffernace))
						temp = mat.values[p][q] / eigenDiffernace;
					else {
						complex theta = 0.5 * eigenDiffernace / mat.values[p][q];
						temp = 1.0 / (abs(theta) + sqrt(1.0 + theta * theta));
						if (theta < 0.0) temp = -temp;
					}
					complex temp2 = 1.0 / sqrt(1.0 + temp * temp);
					complex temp3 = temp * temp2;
					complex tau = temp3 / (1.0 + temp2);
					complex temp4 = temp * mat.values[p][q];

					results[p] -= temp4;
					results[q] += temp4;
					eigenValues[p] -= temp4;
					eigenValues[q] += temp4;
					mat.values[p][q] = 0.0;

					// Rotating 
					for (int j = 0; j < p; j++) {
						complex temp5 = mat.values[j][p];
						temp4 = mat.values[j][q];
						mat.values[j][p] = temp5 - temp3 * (temp4 + temp5 * tau);
						mat.values[j][q] = temp4 + temp3 * (temp5 - temp4 * tau);
					}
					for (int j = p + 1; j < q; j++) {
						complex temp5 = mat.values[p][j];
						temp4 = mat.values[j][q];
						mat.values[p][j] = temp5 - temp3 * (temp4 + temp5 * tau);
						mat.values[j][q] = temp4 + temp3 * (temp5 - temp4 * tau);
					}
					for (int j = q + 1; j < mat.nC; j++) {
						complex temp5 = mat.values[p][j];
						temp4 = mat.values[q][j];
						mat.values[p][j] = temp5 - temp3 * (temp4 + temp5 * tau);
						mat.values[q][j] = temp4 + temp3 * (temp5 - temp4 * tau);
					}
					// Accumulate information
					for (int j = 0; j < mat.nR; j++) {
						complex temp5 = eigenVectors.values[j][p];
						temp4 = eigenVectors.values[j][q];
						eigenVectors.values[j][p] = temp5 - temp3 * (temp4 + temp5 * tau);
						eigenVectors.values[j][q] = temp4 + temp3 * (temp5 - temp4 * tau);
					}
					rotationsNo++;
				}
			}
		}

		for (int i = 0; i < mat.nR; i++) {
			diagValues[i] += results[i];
			eigenValues[i] = diagValues[i];
			results[i] = 0.0;
		}
	}

	// making the matrix symmetric again
	for (int j = 0; j < mat.nR; j++) {
		for (int i = 0; i < j; i++) {
			mat.values[i][j] = mat.values[j][i];
		}
	}

	// sorting the values of eigenvalues and eigenvectors
	int itrationsPerSorting = mat.nR - 1;
	for (int k = 0; k < itrationsPerSorting; k++) {
		int m = k;
		for (int l = k + 1; l < mat.nR; l++)
			if (eigenValues[l] < eigenValues[m])
				m = l;

		if (m != k) {
			complex temp = eigenValues[m];
			eigenValues[m] = eigenValues[k];
			eigenValues[k] = temp;
			for (int i = 0; i < mat.nR; i++) {
				temp = eigenVectors.values[i][m];
				eigenVectors.values[i][m] = eigenVectors.values[i][k];
				eigenVectors.values[i][k] = temp;
			}
		}
	}
	delete[] diagValues;
	delete[] results;

	return;
}
CMatrix symmPow(const CMatrix& mat, const complex& d) {
	complex* eigenValues;
	eigenValues = new complex[mat.nR];
	CMatrix temp;
	temp = mat;
	CMatrix eigenVectors;
	int iterations = 0;
	int rotations = 0;
	jacobiEigenAnalysis(temp, 30000, eigenVectors, eigenValues, iterations, rotations);
	cout << iterations << " " << rotations << " " << endl;
	cout << eigenVectors.getString() << endl;
	for (int i = 0; i < mat.nR; i++) cout << eigenValues[i] << " ";
	cout << endl;

	delete[] eigenValues;
	//return mat.dotPow(d);
	return CMatrix("[]");
}

# include <cstdlib>
# include <iomanip>
# include <cmath>
# include <ctime>
# include <cstring>
using namespace std;
/*
//****************************************************************************80

complex r8mat_is_eigen_right(int n, int k, complex a[], complex x[],
	complex lambda[])

	//****************************************************************************80
	//
	//  Purpose:
	//
	//    R8MAT_IS_EIGEN_RIGHT determines the error in a (right) eigensystem.
	//
	//  Discussion:
	//
	//    An R8MAT is a matrix of complexs.
	//
	//    This routine computes the Frobenius norm of
	//
	//      A * X - X * LAMBDA
	//
	//    where
	//
	//      A is an N by N matrix,
	//      X is an N by K matrix (each of K columns is an eigenvector)
	//      LAMBDA is a K by K diagonal matrix of eigenvalues.
	//
	//    This routine assumes that A, X and LAMBDA are all real.
	//
	//  Licensing:
	//
	//    This code is distributed under the GNU LGPL license. 
	//
	//  Modified:
	//
	//    07 October 2010
	//
	//  Author:
	//
	//    John Burkardt
	//
	//  Parameters:
	//
	//    Input, int N, the order of the matrix.
	//
	//    Input, int K, the number of eigenvectors.
	//    K is usually 1 or N.
	//
	//    Input, complex A[N*N], the matrix.
	//
	//    Input, complex X[N*K], the K eigenvectors.
	//
	//    Input, complex LAMBDA[K], the K eigenvalues.
	//
	//    Output, complex R8MAT_IS_EIGEN_RIGHT, the Frobenius norm
	//    of the difference matrix A * X - X * LAMBDA, which would be exactly zero
	//    if X and LAMBDA were exact eigenvectors and eigenvalues of A.
	//
{
	complex *c;
	complex error_frobenius;
	int i;
	int j;
	int l;

	c = new complex[n*k];

	for (int j = 0; j < k; j++)
	{
		for (i = 0; i < n; i++)
		{
			c[i + j*n] = 0.0;
			for (l = 0; l < n; l++)
			{
				c[i + j*n] = c[i + j*n] + a[i + l*n] * x[l + j*n];
			}
		}
	}

	for (int j = 0; j < k; j++)
	{
		for (i = 0; i < n; i++)
		{
			c[i + j*n] = c[i + j*n] - lambda[j] * x[i + j*n];
		}
	}

	error_frobenius = r8mat_norm_fro(n, k, c);

	delete[] c;

	return error_frobenius;
}
//****************************************************************************80

complex r8mat_norm_fro(int m, int n, complex a[])

//****************************************************************************80
//
//  Purpose:
//
//    R8MAT_NORM_FRO returns the Frobenius norm of an R8MAT.
//
//  Discussion:
//
//    An R8MAT is a doubly dimensioned array of R8 values, stored as a vector
//    in column-major order.
//
//    The Frobenius norm is defined as
//
//      R8MAT_NORM_FRO = sqrt (
//        sum ( 1 <= I <= M ) sum ( 1 <= j <= N ) A(I,J)^2 )
//    The matrix Frobenius norm is not derived from a vector norm, but
//    is compatible with the vector L2 norm, so that:
//
//      r8vec_norm_l2 ( A * x ) <= r8mat_norm_fro ( A ) * r8vec_norm_l2 ( x ).
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    10 October 2005
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int M, the number of rows in A.
//
//    Input, int N, the number of columns in A.
//
//    Input, complex A[M*N], the matrix whose Frobenius
//    norm is desired.
//
//    Output, complex R8MAT_NORM_FRO, the Frobenius norm of A.
//
{
	int i;
	int j;
	complex value;

	value = 0.0;
	for (int j = 0; j < n; j++)
	{
		for (i = 0; i < m; i++)
		{
			value = value + pow(a[i + j*m], 2);
		}
	}
	value = sqrt(value);

	return value;
}
//****************************************************************************80

void r8mat_print(int m, int n, complex a[], string title)

//****************************************************************************80
//
//  Purpose:
//
//    R8MAT_PRINT prints an R8MAT.
//
//  Discussion:
//
//    An R8MAT is a doubly dimensioned array of R8 values, stored as a vector
//    in column-major order.
//
//    Entry A(I,J) is stored as A[I+J*M]
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    10 September 2009
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int M, the number of rows in A.
//
//    Input, int N, the number of columns in A.
//
//    Input, complex A[M*N], the M by N matrix.
//
//    Input, string TITLE, a title.
//
{
	r8mat_print_some(m, n, a, 1, 1, m, n, title);

	return;
}
//****************************************************************************80

void r8mat_print_some(int m, int n, complex a[], int ilo, int jlo, int ihi,
	int jhi, string title)

	//    Input, int M, the number of rows of the matrix.
	//    M must be positive.
	//
	//    Input, int N, the number of columns of the matrix.
	//    N must be positive.
	//
	//    Input, complex A[M*N], the matrix.
	//
	//    Input, int ILO, JLO, IHI, JHI, designate the first row and
	//    column, and the last row and column to be printed.
	//
	//    Input, string TITLE, a title.
	//
{
# define INCX 5

	int i;
	int i2hi;
	int i2lo;
	int j;
	int j2hi;
	int j2lo;

	cout << "\n";
	cout << title << "\n";

	if (m <= 0 || n <= 0)
	{
		cout << "\n";
		cout << "  (None)\n";
		return;
	}
	//
	//  Print the columns of the matrix, in strips of 5.
	//
	for (int j2lo = jlo; j2lo <= jhi; j2lo = j2lo + INCX)
	{
		j2hi = j2lo + INCX - 1;
		if (n < j2hi)
		{
			j2hi = n;
		}
		if (int jhi < j2hi)
		{
			j2hi = jhi;
		}
		cout << "\n";
		//
		//  For each column J in the current range...
		//
		//  Write the header.
		//
		cout << "  Col:    ";
		for (int j = j2lo; j <= j2hi; j++)
		{
			cout << setw(7) << j - 1 << "       ";
		}
		cout << "\n";
		cout << "  Row\n";
		cout << "\n";
		//
		//  Determine the range of the rows in this strip.
		//
		if (1 < ilo)
		{
			i2lo = ilo;
		}
		else
		{
			i2lo = 1;
		}
		if (ihi < m)
		{
			i2hi = ihi;
		}
		else
		{
			i2hi = m;
		}

		for (i = i2lo; i <= i2hi; i++)
		{
			//
			//  Print out (up to) 5 entries in row I, that lie in the current strip.
			//
			cout << setw(5) << i - 1 << ": ";
			for (int j = j2lo; j <= j2hi; j++)
			{
				cout << setw(12) << a[i - 1 + (int j - 1)*m] << "  ";
			}
			cout << "\n";
		}
	}

	return;
# undef INCX
}*/

CMatrix subColumn(const CMatrix& mat, const int& C) {
	CMatrix column(mat.nR, 1);
	for (int iR = 0; iR < mat.nR; iR++)
		column.values[iR][0] = mat.values[iR][C];

	return column;
}
complex innerProd(const CMatrix& mat1, const CMatrix& mat2) {
	complex ans = 0.0;

	for (int iR = 0; iR < mat1.nR; iR++)
		for (int iC = 0; iC < mat1.nC; iC++)
			ans += mat1.values[iR][iC] * mat2.values[iR][iC];

	return ans;
}
complex columnLength(const CMatrix& mat, const int& column) {
	complex ans = 0.0;

	for (int iR = 0; iR < mat.nR; iR++)
		ans += mat.values[iR][column] * mat.values[iR][column];

	return sqrt(ans);
}
void qrDecomp(const CMatrix& mat, CMatrix& q, CMatrix& r) {

	// Calculating Q
	// Orthognalizing the matrix
	q = mat;
	CMatrix column;
	CMatrix columnResult;
	CMatrix tempMat;
	for (int iC = 1; iC < mat.nC; iC++) {
		column = subColumn(mat, iC);
		columnResult = column;
		for (int i = iC - 1; i >= 0; i--) {
			tempMat = subColumn(q, i);
			complex scale = innerProd(column, tempMat) / innerProd(tempMat, tempMat);
			for (int j = 0; j < tempMat.nR; j++)
				tempMat.values[j][0] *= scale;
			columnResult = columnResult - tempMat;
		}
		for (int iR = 0; iR < q.nR; iR++)
			q.values[iR][iC] = columnResult.values[iR][0];
	}
	// Orthonormalizing the matrix
	for (int iC = 0; iC < q.nC; iC++) {
		complex length = columnLength(q, iC);
		for (int iR = 0; iR < q.nR; iR++)
			q.values[iR][iC] /= length;
	}
	
	// Calculating R
	r = q;
	r = q.getInverse();
	tempMat = mat;
	r = r * tempMat;
}

CMatrix generalPower(const CMatrix& eigenVectors, const CMatrix& eigenValues, const complex& d) {

	CMatrix tempMat = diagPow(eigenValues, d);
	CMatrix tempEVec;
	tempEVec.copy(eigenVectors);
	tempMat = tempEVec * tempMat * tempEVec.getInverse();

	return tempMat;
}

void CMatrix::pow(const complex& d) {
	if (nC != nR) throw("for A^b, A must be a square matrix. Use .^ for elementwise power.");

	complex x = d;
	if (x.real() < 0.0) copy(getInverse().posPower(d));
	else if (x.real() > 0.0) copy(posPower(d));
	else copy(CMatrix(nR, nC, 2));
}
bool CMatrix::equal(CMatrix m) {
	if (nR != m.nR || nC != m.nC) return false;
	for (int iR = 0; iR < nR; iR++)
		for (int iC = 0; iC < nC; iC++)
			if (values[iR][iC] != m.values[iR][iC]) return false;
	return true;
}
#define ITERATIONS 30
CMatrix CMatrix::posPower(const complex& d) {
	/*if (d == complex(int(d))) { // Case1 => power is an int number;
		CMatrix tempMat = *this;
		for (int i = 1; i < d; i++) tempMat = tempMat * *this;
		return tempMat;
	}*/
	cout << "in\n";
	if (isdiagonal(*this)) return diagPow(*this, d); // Case2 => Diagonal matrix
	//else if (issymmetric(*this)) return symmPow(*this, d); // Case3 => Symmetric matrix
	else {
		cout << "in2\n";
		CMatrix tempMat = *this;
		CMatrix q(nR, nC);
		CMatrix r(nR, nC);
		CMatrix eigenVectors(nR, nC, 2);
		for (int i = 0; i < ITERATIONS; i++) {
			cout << "in3\n";
			qrDecomp(tempMat, q, r);
			cout << "in4\n";
			eigenVectors = eigenVectors * q;
			tempMat = r * q;
		}
		cout << "in5\n";
		CMatrix eigenValues(nR, nC);
		for (int i = 0; i < nR; i++) {
			eigenValues.values[i][i] = tempMat.values[i][i];
			cout << eigenValues.values[i][i] << endl;
		}
		cout << "lamda" << eigenValues.getString() << "V" << eigenVectors.getString();

		return generalPower(eigenVectors, eigenValues, d);
	}
}