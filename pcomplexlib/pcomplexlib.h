#ifndef _PCOMPLEXLIB_H_
#define _PCOMPLEXLIB_H_

#include <iostream>

const int PRECISION = 2;  // Used for round functions

using std::ostream;
using std::string;

class complex {
private:
	double re, im;
	bool isComplex;
	void iscomplex(void);

public:
	// ===== Constructors and destructor
	complex(void);
	complex(const double& r);
	complex(const double& r, const double& i);
	complex(const complex& z);
	complex(const string& str);
	~complex(void);

	// ==== Erasing values
	void reset(void);
	friend void reset(complex& z);

	// ===== Accessing private variables
	double real(void);
	friend double real(const complex& z);
	double imag(void);
	friend double imag(const complex& z);
	friend bool iscomplex(const complex& z);

	// ===== Complex special functions
	complex conj(void);
	friend complex conj(const complex& z);
	double abs(void);
	friend double abs(const complex& z);
	double arg(void);
	friend double arg(const complex& z);
	double norm(void);
	friend double norm(const complex& z);

	// ===== Rounding complex numbers
	complex round(const int& precision = PRECISION);
	friend complex round(const complex& z, const int& precision = PRECISION);

	// ===== Casting
	operator const complex();
	operator const string();
	/*explicit operator const bool();
	explicit operator const int();
	explicit operator const float();*/ // no support in c++98
	// ===== Assignment operators
	void operator=(const complex& z);
	void operator=(const double& d);
	friend complex operator-(const complex& z); // -z
												// ===== Addition operators
	complex operator+(const complex& z);
	complex operator+(const double& d);
	friend complex operator+(const double& d, const complex& z);
	void operator+=(const complex& z);
	void operator+=(const double& d);
	// ===== Subtraction operators
	complex operator-(const complex& z);
	complex operator-(const double& d);
	friend complex operator-(const double& d, const complex& z);
	void operator-=(const complex& z);
	void operator-=(const double& d);
	// ===== Multiplication operators
	complex operator*(const complex& z);
	complex operator*(const double& d);
	friend complex operator*(const double& d, const complex& z);
	void operator*=(const complex& z);
	void operator*=(const double& d);
	// ===== Division operators
	complex operator/(const complex& z);
	complex operator/(const double& d);
	friend complex operator/(const double& d, const complex& z);
	void operator/=(const complex& z);
	void operator/=(const double& d);
	// ===== Boolen operators
	bool operator==(const complex& z);
	bool operator!=(const complex& z);
	bool operator<(const complex& z);
	bool operator>(const complex& z);
	bool operator<=(const complex& z);
	bool operator>=(const complex& z);
	// ===== Complex special operators
	complex operator~(); // conjugate
	friend double operator<(int, const complex& z); // argument

													// ===== Input and output assignments
	friend void getValue(complex& z);
	friend ostream& operator<<(ostream& stream, const complex& z);
	friend string to_string(const complex& z);
	string to_string();

	// ===== Logarithmic and exponential functions
	friend complex log(const complex& z);
	friend complex log2(const complex& z);
	friend complex log10(const complex& z);
	friend complex exp(const complex& z);

	// ===== Power functions
	complex pow(const double& d);
	friend complex pow(const complex& z, const double& d);
	friend complex pow(const double& d, const complex& c);
	complex pow(const complex& c);
	friend complex pow(const complex& z, const complex& c);
	friend complex sqrt(const complex& z);

	// ===== Trigonometric functions
	friend complex sin(const complex& z);
	friend complex cos(const complex& z);
	friend complex tan(const complex& z);
	friend complex csc(const complex& z);
	friend complex sec(const complex& z);
	friend complex cot(const complex& z);
	// ===== Inverse trigonometric functions
	friend complex asin(const complex& z);
	friend complex acos(const complex& z);
	friend complex atan(const complex& z);
	friend complex acsc(const complex& z);
	friend complex asec(const complex& z);
	friend complex acot(const complex& z);

	// ===== Hyperbolic functions
	friend complex sinh(const complex& z);
	friend complex cosh(const complex& z);
	friend complex tanh(const complex& z);
	friend complex csch(const complex& z);
	friend complex sech(const complex& z);
	friend complex coth(const complex& z);
	// ===== Inverse hyperbolic functions
	friend complex asinh(const complex& z);
	friend complex acosh(const complex& z);
	friend complex atanh(const complex& z);
	friend complex acsch(const complex& z);
	friend complex asech(const complex& z);
	friend complex acoth(const complex& z);

};

#endif