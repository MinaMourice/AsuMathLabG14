#include "stdafx.h"
#include "cmatrix.h"
# include <iostream>

// Diagonal matrices powers
bool isdiagonal(const CMatrix& mat) {
	bool matDiagonal = true;
	for (int iR = 1; iR < mat.nR && matDiagonal; iR++)
		for (int iC = 0; iC < iR && matDiagonal; iC++)
			if (!(iR == iC))
				if (mat.values[iR][iC] != 0 || mat.values[iC][iR] != 0) matDiagonal = false;

	return  matDiagonal;
}
CMatrix diagPow(const CMatrix& mat, const double& d) {
	CMatrix temp;
	temp = mat;
	//return temp.dotPow(d);
	return CMatrix("[]");
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
void jacobiEigenAnalysis(const CMatrix matrix, const int& maxIterations, CMatrix& eigenVectors, double eigenValues[], int &iteraNo, int &rotationsNo) {

	CMatrix mat;
	mat = matrix;
	eigenVectors = CMatrix(mat.nR, mat.nR, 2);

	double *diagValues;
	diagValues = new double[mat.nR];
	double *results;
	results = new double[mat.nR];

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

		double threshhold = 0.0; // essentially the value of the elements around the diagonal
		for (int i = 0; i < mat.nR; i++) {
			for (int j = 0; j < i; j++) {
				threshhold += mat.values[i][j] * mat.values[i][j];
			}
		}
		threshhold = sqrt(threshhold) / (double)(4.0 * mat.nR);

		if (threshhold == 0.0) // The break condition
			break;

		for (int p = 0; p < mat.nR; p++) {
			for (int q = p + 1; q < mat.nC; q++) { // working on the upper triangler part of the matrix
				double elementValue = 10.0 * abs(mat.values[p][q]);
				double termOne = elementValue + abs(eigenValues[p]);
				double termTwo = elementValue + abs(eigenValues[q]);

				if (iteraNo > 4 && termOne == abs(eigenValues[p]) && termTwo == abs(eigenValues[q])) // if [p][q] is so small with respect to its two eigen values, we remove it
					mat.values[p][q] = 0.0;
				else if (threshhold <= abs(mat.values[p][q])) { // if [p][q] is big, We rotate the matrix
					double eigenDiffernace = eigenValues[q] - eigenValues[p];
					double temp;
					double term = abs(eigenDiffernace) + elementValue;
					if (term == abs(eigenDiffernace))
						temp = mat.values[p][q] / eigenDiffernace;
					else {
						double theta = 0.5 * eigenDiffernace / mat.values[p][q];
						temp = 1.0 / (abs(theta) + sqrt(1.0 + theta * theta));
						if (theta < 0.0) temp = -temp;
					}
					double temp2 = 1.0 / sqrt(1.0 + temp * temp);
					double temp3 = temp * temp2;
					double tau = temp3 / (1.0 + temp2);
					double temp4 = temp * mat.values[p][q];

					results[p] -= temp4;
					results[q] += temp4;
					eigenValues[p] -= temp4;
					eigenValues[q] += temp4;
					mat.values[p][q] = 0.0;

					// Rotating 
					for (int j = 0; j < p; j++) {
						double temp5 = mat.values[j][p];
						temp4 = mat.values[j][q];
						mat.values[j][p] = temp5 - temp3 * (temp4 + temp5 * tau);
						mat.values[j][q] = temp4 + temp3 * (temp5 - temp4 * tau);
					}
					for (int j = p + 1; j < q; j++) {
						double temp5 = mat.values[p][j];
						temp4 = mat.values[j][q];
						mat.values[p][j] = temp5 - temp3 * (temp4 + temp5 * tau);
						mat.values[j][q] = temp4 + temp3 * (temp5 - temp4 * tau);
					}
					for (int j = q + 1; j < mat.nC; j++) {
						double temp5 = mat.values[p][j];
						temp4 = mat.values[q][j];
						mat.values[p][j] = temp5 - temp3 * (temp4 + temp5 * tau);
						mat.values[q][j] = temp4 + temp3 * (temp5 - temp4 * tau);
					}
					// Accumulate information
					for (int j = 0; j < mat.nR; j++) {
						double temp5 = eigenVectors.values[j][p];
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
			double temp = eigenValues[m];
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
CMatrix symmPow(const CMatrix& mat, const double& d) {
	double* eigenValues;
	eigenValues = new double[mat.nR];
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

double r8mat_is_eigen_right(int n, int k, double a[], double x[],
	double lambda[])

	//****************************************************************************80
	//
	//  Purpose:
	//
	//    R8MAT_IS_EIGEN_RIGHT determines the error in a (right) eigensystem.
	//
	//  Discussion:
	//
	//    An R8MAT is a matrix of doubles.
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
	//    Input, double A[N*N], the matrix.
	//
	//    Input, double X[N*K], the K eigenvectors.
	//
	//    Input, double LAMBDA[K], the K eigenvalues.
	//
	//    Output, double R8MAT_IS_EIGEN_RIGHT, the Frobenius norm
	//    of the difference matrix A * X - X * LAMBDA, which would be exactly zero
	//    if X and LAMBDA were exact eigenvectors and eigenvalues of A.
	//
{
	double *c;
	double error_frobenius;
	int i;
	int j;
	int l;

	c = new double[n*k];

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

double r8mat_norm_fro(int m, int n, double a[])

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
//    Input, double A[M*N], the matrix whose Frobenius
//    norm is desired.
//
//    Output, double R8MAT_NORM_FRO, the Frobenius norm of A.
//
{
	int i;
	int j;
	double value;

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

void r8mat_print(int m, int n, double a[], string title)

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
//    Input, double A[M*N], the M by N matrix.
//
//    Input, string TITLE, a title.
//
{
	r8mat_print_some(m, n, a, 1, 1, m, n, title);

	return;
}
//****************************************************************************80

void r8mat_print_some(int m, int n, double a[], int ilo, int jlo, int ihi,
	int jhi, string title)

	//    Input, int M, the number of rows of the matrix.
	//    M must be positive.
	//
	//    Input, int N, the number of columns of the matrix.
	//    N must be positive.
	//
	//    Input, double A[M*N], the matrix.
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