#include "pcomplexlib.h"
#include <iostream>
#include <string>

using namespace std;

static const complex j = complex(0.0, 1.0);

int main(int argc, char* argv[]) {

	complex a(1.2, 1.2), b(-1.2, -1.2);
	try {
		cout << "Please, enter a:\n\t";
		getValue(a);
		cout << "Also, enter b:\n\t";
		getValue(b);

		cout << "a = " << a.to_string() << " and b = " << to_string(b) << endl;
		cout << "a rounded to 2 floating points = " << round(a) << endl;
		cout << "a rounded to 1 floating points = " << round(a, 1) << endl;
		cout << "b rounded to 2 floating points = " << b.round() << endl;
		cout << "b rounded to 1 floating points = " << b.round(1) << endl;
		cout << "a + b = " << a + b << endl;
		cout << "a - b = " << a - b << endl;
		cout << "a * b = " << a * b << endl;
		cout << "a / b = " << a / b << endl;
		a += b;
		cout << "a+=b -> " << a << endl;
		a -= b;
		cout << "a-=b -> " << a << endl;
		a *= b;
		cout << "a*=b -> " << a << endl;
		a /= b;
		cout << "a/=b -> " << a << endl;
		cout << "a = " << abs(a) << "<" << (0 < a) << endl;
		cout << "|a| = " << abs(a) << " " << a.abs() << endl;
		cout << "<a = " << arg(a) << " " << a.arg() << endl;
		cout << "a' = " << ~a << " " << conj(a) << " " << a.conj() << endl;
		cout << "|a|^2 = " << norm(a) << " " << a.norm() << endl;
		cout << "-a = " << -a << endl;
		cout << "log(a) = " << log(a) << endl;
		cout << "log2(a) = " << log2(a) << endl;
		cout << "log10(a) = " << log10(a) << endl;
		cout << "exp(a) = " << exp(a) << endl;
		cout << "a^2.7 = " << pow(a, 2.7) << " " << a.pow(2.7) << endl;
		cout << "1.3^a = " << pow(1.3, a) << endl;
		cout << "sin(a) = " << sin(a) << endl;
		cout << "cos(a) = " << cos(a) << endl;
		cout << "tan(a) = " << tan(a) << endl;
		cout << "csc(a) = " << csc(a) << endl;
		cout << "sec(a) = " << sec(a) << endl;
		cout << "cot(a) = " << cot(a) << endl;
		cout << "asin(a) = " << asin(a) << endl;
		cout << "acos(a) = " << acos(a) << endl;
		cout << "atan(a) = " << atan(a) << endl;
		cout << "acsc(a) = " << acsc(a) << endl;
		cout << "asec(a) = " << asec(a) << endl;
		cout << "acot(a) = " << acot(a) << endl;
		cout << "sinh(a) = " << sinh(a) << endl;
		cout << "cosh(a) = " << cosh(a) << endl;
		cout << "tanh(a) = " << tanh(a) << endl;
		cout << "csch(a) = " << csch(a) << endl;
		cout << "sech(a) = " << sech(a) << endl;
		cout << "coth(a) = " << coth(a) << endl;
		cout << "asinh(a) = " << asinh(a) << endl;
		cout << "acosh(a) = " << acosh(a) << endl;
		cout << "atanh(a) = " << atanh(a) << endl;
		cout << "acsch(a) = " << acsch(a) << endl;
		cout << "asech(a) = " << asech(a) << endl;
		cout << "acoth(a) = " << acoth(a) << endl;
		//cout << "a:bool = " << static_cast<bool>(a) << endl;
		//cout << "a:int = " << static_cast<int>(a) << endl;
		//cout << "a:float = " << static_cast<float>(a) << endl; // no support in c++98
	}
	catch (const char* error) { cout << error << endl; }

	return 0;
}

/*	a = 1 + 0j
	b = 0j
	a + b
	a - b
	a * b
	a / b
	a += b
	a -= b
	a *= b
	a /= b
	polar(a)
	abs(a)
	arg(a)
	conj(a)
	norm(a) <= Doesn't give right values, different definition?
	-a
	log(a)
	log2(a)
	log10(a)
	exp(a)
	a^2.7
	1.3^a
	sin(a)
	cos(a)
	tan(a)
	csc(a)
	sec(a)
	cot(a)
	asin(a)
	acos(a)
	atan(a)
	acsc(a)
	asec(a)
	acot(a)
	sinh(a)
	cosh(a)
	tanh(a)
	csch(a)
	sech(a)
	coth(a)
	asinh(a)
	acosh(a)
	atanh(a)
	acsch(a)
	asech(a)
	acoth(a)	*/
