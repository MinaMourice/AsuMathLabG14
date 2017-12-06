#include "cmatrix.h"
# include <iostream>

void CMatrix::pow(double& d) {
    if (nC != nR) throw("for A^b, A must be a square matrix. Use .^ for elementwise power.");

    if (d < 0.0) this.copy((this.getInverse()).posPower(d)));
    else if (d > 0.0) this.copy(this.posPower(d));
    else this.copy(CMatrix(nR, nC, 2));
}
bool equal(CMatrix m) {
    if (nR != m.nR || nC != m.nC) return false;
    for (int iR = 0;  iR < nR; iR++)
        for (int iC = 0;  iC < nC; iC++)
            if (values[iR][iC] != m.values[iR][iC]) return false;
    return true;
}
#define ITERATIONS 10000
CMatrix CMatrix::posPower(double& d) {
    if (d == double(int(d))) { // Case1 => power is an int number;
        CMatrix tempMat = this;
        for (int i = 1; i < d; i++) tempMat = tempMat * this;
        return tempMat;
    }
    if (isdiagonal(this)) return diagPow(this, d); // Case2 => Diagonal matrix
    else if (issymmetric(this)) return symmPow(this, d); // Case3 => Symmetric matrix
    else {
        CMatrix tempMat = this;
        CMatrix q(nR, nC);
        CMatrix r(nR, nC);
        for (int i = 0; i < ITERATIONS; i++) {
            qrDecomp(tempMat, q, r)
            tempMat = r * q;
        }

        double eigenValues[nR];
        for (int i = 0, i < nR; i++)
            eigenValues[i] = tempMat[i][i];

        CMatrix eigenVectors = getEigenVectors(this, eigenValues);

        return generalPower(eigenVectors, eigenValues[], d);
    }
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
CMatrix diagPow(const CMatrix& mat, const double& d) {
	CMatrix temp;
	temp = mat;
	//return temp.dotPow(d);
	return CMatrix("[]");
}

//Jacobi
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

// QR-decomposition
CMatrix CMatrix::subColumn(const int& C) {
    CMatrix column(nR, 1);
    for (int iR = 0; iR < nR; iR++)
        column.values[iR][0] = values[iR][C];
    
    return column;
}
double innerProd(const CMatrix& mat1, const CMatrix& mat2) {
    double ans = 0.0;

    for (int iR = 0; iR < nR; iR++)
        for (int iC = 0; iC < nC; iC++)
            ans += column.values[iR][iC] * values[iR][iC];
    
    return ans;
}
double columnLength(const CMatrix& mat) {
    double ans = 0.0;
    
    for (int iR = 0; iR < nR; iR++)
        ans += mat.values[iR][0] * mat.values[iR][0];
    
    return sqrt(ans);
}

void qrDecomp(const CMatrix& mat, CMatrix& q, CMatrix r) {

    // Calculating q
    for (int iC = 0, iC < nC, iC++) {
        CMatrix column = subColumn(iC);
        if (iC > 0) {
            for (int i = iC - 1; i >= 0; i--) {
                CMatrix tempMat = q.subColumn(i);
                column = column - (innerProd(column, tempMat)/innerProd(tempMat, tempMat)) * tempMat;
            }
        }
        double length = columnLength(column);
        for (int iR = 0; iR < nR; iR++)
            q.values[iR][iC] = column.values[iR][iC] / length;
    }

    r = mat.getInverse() * q;
}

CMatrix generalPower(const CMatrix& eigenVectors, const double eigenValues[], const double d) {

    CMatrix eigenDiagMat(eigenVectors.nR, eigenVectors.nC);
    for (int i = 0; i < eigenVectors.nR; i++)
        eigenDiagMat[i][i] = eigenValues[i];

    CMatrix tempMat = diagPow(eigenDiagMat, d);
    tempMat = eigenVectors * tempMat * eigenVectors.getInverse();

    return tempMat;
}

CMatrix getEigenVectors(const CMatrix& mat, const double eigenValues[]) {
    
}
