#include "pcomplexlib.h"
#include <sstream>
#include <cmath>

using std::string;
using std::ostream;
using std::ostringstream;

#define PI 3.141592653589793

static complex j = complex(0.0, 1.0); // j or i (imaginary one)
static double SENSITIVITY = 0.0000000000001; // Used only in returning the values of re/im in external containers. Because when you do operations on doubles, if the return value is zero its not actually saved as 0.00000 but instead as a very low value 0.0000001;

complex::complex(void) {
	reset();
}
complex::complex(const double& r) {
	re = r;
	im = 0.0;
	isComplex = false;
}
complex::complex(const double& r, const double& i) {
	re = r;
	im = i;
	iscomplex();
}
complex::complex(const complex& z) {
	re = z.re;
	im = z.im;
	isComplex = z.isComplex;
}
complex::complex(const string& str) {
	reset();
	int sLength = str.length();
	float realSign = 1.0, imagSign = 1.0;
	float realFloatValue = 0.0, imagFloatValue = 0.0;
	int realFloatNo = 0, imagFloatNo = 0;
	bool areWeReadingRealSign = true;
	bool areWeReadingReal = true;
	bool areWeReadingFloat = false;
	bool didWeReadRealAndImag = false; // Only if the string contains a second sign in the number
	bool didWeEncounterImagChar = false; // Only if the string contains "j" or "i"
										 // ===== Decoding the entered string
	for (int count = 0; count < sLength; count++) {
		char c = str[count];
		if (c == ' ');
		else if (c == '.') areWeReadingFloat = true;
		else if (c == '-' && areWeReadingReal && areWeReadingRealSign) { realSign = -1.0; }
		else if (isdigit(c) && areWeReadingReal && !areWeReadingFloat) { re = re * 10 + c - '0'; areWeReadingRealSign = false; } // "c + '0'" turns each char to its digit value
		else if (isdigit(c) && areWeReadingReal && areWeReadingFloat) { realFloatValue = realFloatValue * 10 + c - '0'; realFloatNo--; areWeReadingRealSign = false; } // "c + '0'" turns each char to its digit value
		else if (c == '-') { imagSign = -1.0; areWeReadingReal = false; areWeReadingFloat = false; didWeReadRealAndImag = true; }
		else if (c == '+') { imagSign = 1.0; areWeReadingReal = false; areWeReadingFloat = false; didWeReadRealAndImag = true; }
		else if (c == 'j' || c == 'i') { areWeReadingReal = false; didWeEncounterImagChar = true; }
		else if (isdigit(c) && !areWeReadingFloat) { im = im * 10 + c - '0'; didWeReadRealAndImag = true; }
		else if (isdigit(c) && areWeReadingFloat) { imagFloatValue = imagFloatValue * 10 + c - '0'; imagFloatNo--; }
		else throw ("Couldn't parse the complex number");
	}
	// ===== Generating the value of Z
	re = realSign * (re + realFloatValue * std::pow(10, realFloatNo));
	if (!didWeReadRealAndImag && didWeEncounterImagChar) { // Means there were no real value entered and so we swap the real and imag values and make the real value = 0
		im = re;
		re = 0.0;
		imagSign = realSign;
	}
	else if (didWeEncounterImagChar) im += imagFloatValue * std::pow(10, imagFloatNo);
	if (didWeEncounterImagChar && std::abs(im) < SENSITIVITY) im++; // Means the value entered "somedouble + j" which means the imag value is in fact 1
	im *= imagSign;

	iscomplex();
}
complex::~complex(void) {
	reset();
}

void complex::reset(void) {
	re = 0.0;
	im = 0.0;
	isComplex = false;
}
void reset(complex& z) {
	z.re = 0.0;
	z.im = 0.0;
	z.isComplex = false;
}

double complex::real(void) {
	if (std::abs(re) > SENSITIVITY) return re;
	else return 0.0;
}
double real(const complex& z) {
	if (std::abs(z.re) > SENSITIVITY) return z.re;
	else return 0.0;
}
double complex::imag(void) {
	if (isComplex) return im;
	return 0.0;
}
double imag(const complex& z) {
	if (z.isComplex) return z.im;
	return 0.0;
}
void complex::iscomplex(void) {
	if (std::abs(im) > SENSITIVITY) {
		isComplex = true;
	}
	else {
		isComplex = false;
	}
}
bool iscomplex(const complex& z) {
	return z.isComplex;
}

complex complex::conj(void) { // We will return a complex anyway, no need to check whether to return -im or zero.
	return complex(re, -im);
}
complex conj(const complex& z) { // We will return a complex anyway, no need to check whether to return -z.im or zero.
	return complex(z.re, -z.im);
}
double complex::abs(void) {
	if (isComplex) return sqrt(re*re + im*im);
	return std::abs(re);
}
double abs(const complex& z) {
	if (z.isComplex) return sqrt(z.re*z.re + z.im*z.im);
	return std::abs(z.re);
}
double complex::arg(void) {
	if (isComplex) return atan2(im, re);
	return atan2(0.0, re);
}
double arg(const complex& z) {
	if (z.isComplex) return atan2(z.im, z.re);
	return atan2(0.0, z.re);
}
double complex::norm(void) {
	if (isComplex) return re*re + im*im;
	return re*re;
}
double norm(const complex& z) {
	if (z.isComplex) return z.re*z.re + z.im*z.im;
	return z.re*z.re;
}

complex complex::round(const int& precision) {
	double realValue, imagValue = 0.0;
	int tempI;

	realValue = re * std::pow(10.0, static_cast<double>(precision));
	tempI = (int)(realValue < 0 ? realValue - 0.5 : realValue + 0.5);
	realValue = tempI / std::pow(10.0, static_cast<double>(precision));

	if (isComplex) {
		imagValue = im * std::pow(10.0, static_cast<double>(precision));
		tempI = (int)(imagValue < 0 ? imagValue - 0.5 : imagValue + 0.5);
		imagValue = tempI / std::pow(10.0, static_cast<double>(precision));
	}

	return complex(realValue, imagValue);
}
complex round(const complex& z, const int& precision) {
	double realValue, imagValue = 0.0;
	int tempI;

	realValue = z.re * std::pow(10.0, static_cast<double>(precision));
	tempI = (int)(realValue < 0 ? realValue - 0.5 : realValue + 0.5);
	realValue = tempI / std::pow(10.0, static_cast<double>(precision));

	if (z.isComplex) {
		imagValue = z.im * std::pow(10.0, static_cast<double>(precision));
		tempI = (int)(imagValue < 0 ? imagValue - 0.5 : imagValue + 0.5);
		imagValue = tempI / std::pow(10.0, static_cast<double>(precision));
	}

	return complex(realValue, imagValue);
}

complex::operator const complex() { return complex(re, im); }
complex::operator const string() { return to_string(); }
/*complex::operator const bool() {
if (abs() > SENSITIVITY) return true;
else return false;
}
complex::operator const int() { return static_cast<int>(re); }
complex::operator const float() { return static_cast<float>(re); }*/  // no support in c++98

void complex::operator=(const complex& z) {
	re = z.re;
	im = z.im;
	isComplex = z.isComplex;
}
void complex::operator=(const double& d) {
	re = d;
	im = 0.0;
	isComplex = false;
}
complex operator-(const complex& z) { return complex(-z.re, -z.im); }  // We will return a complex anyway, no need to check whether to return -z.im or zero.

complex complex::operator+(const complex& z) {
	if (isComplex || z.isComplex) return complex(re + z.re, im + z.im);
	return re + z.re;
}
complex complex::operator+(const double& d) {
	if (isComplex) return complex(re + d, im);
	return re + d;
}
complex operator+(const double& d, const complex& z) {
	if (z.isComplex) return complex(d + z.re, z.im);
	return d + z.re;
}
void complex::operator+=(const complex& z) {
	re += z.re;
	if (z.isComplex) {
		im += z.im;
		iscomplex();
	}
}
void complex::operator+=(const double& d) { re += d; }

complex complex::operator-(const complex& z) {
	if (isComplex || z.isComplex) return complex(re - z.re, im - z.im);
	return complex(re - z.re);
}
complex complex::operator-(const double& d) {
	if (isComplex) return complex(re - d, im);
	return re - d;
}
complex operator-(const double& d, const complex& z) {
	if (z.isComplex) return complex(d - z.re, -z.im);
	return d - z.re;
}
void complex::operator-=(const complex& z) {
	re -= z.re;
	im -= z.im;
	iscomplex();
}
void complex::operator-=(const double& d) { re -= d; }

complex complex::operator*(const complex& z) {
	if (isComplex && z.isComplex) return complex(re * z.re - im * z.im, re * z.im + im * z.re);
	else if (isComplex) return z.re * *this;
	else if (z.isComplex) return re * z;
	return re * z.re;
}
complex complex::operator*(const double& d) {
	if (isComplex) return complex(d*re, d*im);
	return d*re;
}
complex operator*(const double& d, const complex& z) {
	if (z.isComplex) return complex(d * z.re, d * z.im);
	return d * z.re;
}
void complex::operator*=(const complex& z) {
	if (isComplex && z.isComplex) {
		double real = re, imag = im;
		re = real * z.re - imag * z.im;
		im = real * z.im + imag * z.re;
		iscomplex();
	}
	else if (isComplex) {
		re = re * z.re;
		im = im * z.re;
		iscomplex();
	}
	else if (z.isComplex) {
		re = re * z.re;
		im = re * z.im;
		iscomplex();
	}
	else re = re * z.re;
}
void complex::operator*=(const double& d) {
	re *= d;
	if (isComplex) im *= d;
}

complex complex::operator/(const complex& z) {
	if (isComplex && z.isComplex) {
		complex temp = *this * ::conj(z);
		double denominator = ::norm(z);
		return temp / denominator;
	}
	else if (isComplex) return *this / z.re;
	else if (z.isComplex) return re / z;
	return re / z.re;
}
complex complex::operator/(const double& d) {
	if (isComplex) return complex(re / d, im / d);
	return re / d;
}
complex operator/(const double& d, const complex& z) {
	if (z.isComplex) {
		complex temp = d * conj(z);
		double denominator = norm(z);
		return temp / denominator;
	}
	return d / z.re;
}
void complex::operator/=(const complex& z) {
	if (isComplex && z.isComplex) {
		*this *= ::conj(z);
		*this /= ::norm(z);
		iscomplex();
	}
	else if (isComplex) {
		re /= z.re;
		im /= z.re;
		iscomplex();
	}
	else if (z.isComplex) {
		*this *= ::conj(z);
		*this /= ::norm(z);
		iscomplex();
	}
	else re /= z.re;
}
void complex::operator/=(const double& d) {
	re /= d;
	if (isComplex) im /= d;
}

bool complex::operator==(const complex& z) {
	if (re == z.re) {
		if (isComplex && z.isComplex) {
			if (im == z.im) return true;
		}
		else if (!isComplex && !z.isComplex) return true;
	}
	return false;
}
bool complex::operator!=(const complex& z) {
	if (re != z.re) {
		if (!isComplex && !z.isComplex) return true;
		else if (isComplex && z.isComplex) {
			if (im == z.im) return false;
		}
		else return true;
	}
	return false;
}
bool complex::operator<(const complex& z) {
	if (abs() < ::abs(z)) return true;
	else return false;
}
bool complex::operator>(const complex& z) {
	if (abs() > ::abs(z)) return true;
	else return false;
}
bool complex::operator<=(const complex& z) {
	if (abs() <= ::abs(z)) return true;
	else return false;
}
bool complex::operator>=(const complex& z) {
	if (abs() >= ::abs(z)) return true;
	else return false;
}

complex complex::operator~() { return this->conj(); }
double operator<(int, const complex& z) {
	return arg(z);
}

void getValue(complex& z) { // It will throw an error or have some undefined behavior when the input is not like -> (+/-)real(+/-)imag(j/i), (+/-)real(+/-)(j/i)imag, (+/-)real, (+/-)imag(j/i) or (+/-)(j/i)imag and it ignores any spaces in the input
	string str;
	getline(std::cin, str);
	z = complex(str);
}
ostream& operator<<(ostream& stream, const complex& z) {
	bool printedReal = false;
	bool printedImag = false;
	// ===== Printing real value
	if (isinf(z.re)) {
		if (z.re < 0) stream << "-INF";
		else stream << "INF";

		printedReal = true;
	}
	else if (isnan(z.re)) {
		if (z.re < 0) stream << "-NaN";
		else stream << "NaN";

		printedReal = true;
	}
	else if (z.re > SENSITIVITY || z.re < -SENSITIVITY) {
		stream << z.re;
		printedReal = true;
	}
	// ===== Printing imaginary value
	if (z.isComplex) {
		if (isinf(z.im)) {
			if (printedReal) {
				if (z.im < 0) stream << " - INFj";
				else stream << " + INFj";
			}
			else {
				if (z.im < 0) stream << "-INFj";
				else stream << "INFj";
			}
			printedImag = true;
		}
		else if (isnan(z.im)) {
			if (printedReal) {
				if (z.im < 0) stream << " - NaNj";
				else stream << " + NaNj";
			}
			else {
				if (z.im < 0) stream << "-NaNj";
				else stream << "NaNj";
			}
			printedImag = true;
		}
		else if (z.im > SENSITIVITY || z.im < -SENSITIVITY) {
			if (printedReal) {
				if (z.im < 0) stream << " - ";
				else stream << " + ";
			}
			else if (z.im < 0.00) stream << "-";
			else;

			if ((std::abs(z.im) < 1.0 + SENSITIVITY) && (std::abs(z.im) > 1.0 - SENSITIVITY)) stream << "j";
			else stream << std::abs(z.im) << "j";
			printedImag = true;
		}
	}
	// ===== Printing 0 if both imag and real = 0;
	if (!printedReal && !printedImag) stream << 0;
	return stream;
}
string to_string(const complex& z) {
	ostringstream os;
	os << z;
	return os.str();
}
string complex::to_string() {
	ostringstream os;
	os << *this;
	return os.str();
}

complex log(const complex& z) {
	if (z.isComplex || z.re <= SENSITIVITY) {
		return complex(log(abs(z)), arg(z));
	}
	return log(z.re);
}
complex log2(const complex& z) {
	if (z.isComplex || z.re <= SENSITIVITY) {
		return complex(log(abs(z)) / log(2.0), arg(z) / log(2.0));
	}
	return log2(z.re);
}
complex log10(const complex& z) {
	if (z.isComplex || z.re <= SENSITIVITY) {
		return complex(log(abs(z)) / log(10.0), arg(z) / log(10.0));
	}
	return log10(z.re);
}
complex exp(const complex& z) {
	if (z.isComplex) {
		return complex(exp(z.re) * cos(z.im), exp(z.re) * sin(z.im));
	}
	return std::exp(z.re);
}

complex complex::pow(const double& d) {
	if (isComplex || re <= SENSITIVITY) {
		double absTemp = std::pow(static_cast<double>(abs()), static_cast<double>(d));
		double argTemp = d * arg();
		return complex(absTemp * cos(argTemp), absTemp * sin(argTemp));
	}
	return std::pow(re, d);
}
complex pow(const complex& z, const double& d) {
	if (z.isComplex || z.re <= SENSITIVITY) {
		double absTemp = pow(abs(z), d);
		double argTemp = d * arg(z);
		return complex(absTemp * cos(argTemp), absTemp * sin(argTemp));
	}
	return std::pow(z.re, d);
}
complex pow(const double& d, const complex& c) {
	if (c.isComplex) return exp(log(d) * c);
	return std::pow(d, c.re);
}
complex complex::pow(const complex& c) {
	if ((isComplex || re <= SENSITIVITY) && c.isComplex) return exp(log(*this) * c);
	else if (isComplex || re <= SENSITIVITY) return pow(c.re);
	else if (c.isComplex) return ::pow(re, c);
	return std::pow(re, c.re);
}
complex pow(const complex& z, const complex& c) {
	if ((z.isComplex || z.re <= SENSITIVITY) && c.isComplex) return exp(log(z) * c);
	else if (z.isComplex || z.re <= SENSITIVITY) return pow(z, c.re);
	else if (c.isComplex) return pow(z.re, c);
	return std::pow(z.re, c.re);
}
complex sqrt(const complex& z) {
	if (z.isComplex || z.re <= SENSITIVITY) {
		double absTemp = pow(abs(z), 0.5);
		double argTemp = 0.5 * arg(z);
		return complex(absTemp * cos(argTemp), absTemp * sin(argTemp));
	}
	return std::sqrt(z.re);
}

complex sin(const complex& z) {
	return 0.5 * j * (-exp(j*z) + exp(-j*z));
	// or
	return sin(z.re) * cosh(z.im) + j * cos(z.re) * sinh(z.im);
}
complex cos(const complex& z) {
	return 0.5 * (exp(j*z) + exp(-j*z));
	// or
	return cos(z.re) * cosh(z.im) - j * sin(z.re) * sinh(z.im);
}
complex tan(const complex& z) {
	return sin(z) / cos(z);
	// or
	return j * (-exp(j*z) + exp(-j*z)) / (exp(j*z) + exp(-j*z));
	// or
	return (tan(z.re) + j * tanh(z.im)) / (1.0 - j * tan(z.re) * tanh(z.im));
}
complex csc(const complex& z) {
	return 1.0 / sin(z);
	// or
	return 2.0 * j / (exp(j*z) - exp(-j*z));
}
complex sec(const complex& z) {
	return 1.0 / cos(z);
	// or
	return 2.0 / (exp(j*z) + exp(-j*z));
}
complex cot(const complex& z) {
	return cos(z) / sin(z);
	// or
	return (j * exp(j*z) + j * exp(-j*z)) / (exp(j*z) - exp(-j*z));
	// or
	return 1.0 / tan(z);
}

complex asin(const complex& z) {
	return (1.0 / j) * log(j * z + sqrt(1.0 - pow(z, 2.0)));
}
complex acos(const complex& z) {
	return (1.0 / j) * log(j * sqrt(1.0 - pow(z, 2.0)) + z);
}
complex atan(const complex& z) {
	return 0.5 * (1.0 / j) * log((j - z) / (j + z));
}
complex acsc(const complex& z) {
	return PI / 2.0 - j * log(sqrt(1.0 / pow(z, 2.0) - 1.0) + 1.0 / z);
	// or
	return (1.0 / j) * log(sqrt(1.0 - 1.0 / pow(z, 2.0)) + j / z);
	// or
	return asin(1.0 / z);
}
complex asec(const complex& z) {
	return PI / 2.0 + j * log(sqrt(1.0 - 1.0 / pow(z, 2.0)) + j / z);
	// or
	return j * log(sqrt(1.0 / pow(z, 2.0) - 1.0) + 1.0 / z);
	// or
	return acos(1.0 / z);
}
complex acot(const complex& z) {
	return 0.5 * (1.0 / j) * log((j + z) / (-j + z));
}

complex sinh(const complex& z) {
	return 0.5 * (exp(z) - exp(-z));
	// or
	return sinh(z.re) * cos(z.im) + j * cosh(z.re) * sin(z.im);
}
complex cosh(const complex& z) {
	return 0.5 * (exp(z) + exp(-z));
	// or
	return complex(cosh(z.re) * cos(z.im), sinh(z.re) * sin(z.im));
}
complex tanh(const complex& z) {
	return (exp(z) - exp(-z)) / (exp(z) + exp(-z));
	// or
	return (tanh(z.re) + j * tan(z.im)) / (1.0 + j * tanh(z.re) * tan(z.im));
}
complex csch(const complex& z) {
	return 2.0 / (exp(z) - exp(-z));
	// or
	return 1.0 / sinh(z);
}
complex sech(const complex& z) {
	return 2.0 / (exp(z) + exp(-z));
	// or
	return 1.0 / cosh(z);
}
complex coth(const complex& z) {
	return (exp(z) + exp(-z)) / (exp(z) - exp(-z));
	// or
	return 1.0 / tanh(z);
}

complex asinh(const complex& z) {
	return log(sqrt(pow(z, 2.0) + 1.0) + z);
}
complex acosh(const complex& z) {
	return log(sqrt(pow(z, 2.0) - 1.0) + z);
}
complex atanh(const complex& z) {
	return 0.5 * log((1.0 + z) / (1.0 - z));
}
complex acsch(const complex& z) {
	return log(1.0 / z + sqrt(1.0 / pow(z, 2.0) + 1.0));
	// or
	return log(1.0 / z + sqrt(1.0 + pow(z, 2.0)) / abs(z)); // 8lt
															// or
	return asinh(1.0 / z);
}
complex asech(const complex& z) {
	return log((1.0 + sqrt(1.0 - pow(z, 2.0))) / z);
	// or
	return acosh(1.0 / z);
}
complex acoth(const complex& z) {
	return 0.5 * log((1.0 + z) / (-1.0 + z));
}