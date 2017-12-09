// swphase2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cmatrix.h"
#include "solve.h"
#include <string>
#include <fstream>
#include <iostream>
#include "decode.h"
using namespace std;



int main(int argc,char* argv[])
{
	string varNames[100], varContent[100];
	int variableNo = 2;
	varNames[0] = "A"; varContent[0] = "-3.9";
	varNames[1] = "B"; varContent[1] = "3.66";
	string s = "asec(A)";
	cout<<s<<"="<<solveDouble(s,  varNames, varContent, variableNo)<<endl;
	cout << "sin(A)" << "=" << solveDouble("sin(A)", varNames, varContent, variableNo) << endl;
	cout << "acot(B)" << "=" << solveDouble("acot(B)", varNames, varContent, variableNo) << endl;
	cout << "asin(A)" << "=" << solveDouble("asin(A)", varNames, varContent, variableNo) << endl;
	cout << "asech(B)" << "=" << solveDouble("asech(B)", varNames, varContent, variableNo) << endl;
	cout << "acsch(B)" << "=" << solveDouble("acsch(B)", varNames, varContent, variableNo) << endl;
	cout << "atanh(A)" << "=" << solveDouble("atanh(A)", varNames, varContent, variableNo) << endl;
	cout << "coth(A)" << "=" << solveDouble("coth(A)", varNames, varContent, variableNo) << endl;
	/*CMatrix x = CMatrix(5, 5, 3);
	CMatrix y = CMatrix(5, 5, 3);
	cout << "x="<<x.getOriginalString();
	cout << x.getString(5);
	cout << "y=" << y.getOriginalString();
	cout << y.getString(5);
	CMatrix z=exp(y);
	CMatrix a=log(x);
	CMatrix b=log10(y);
	CMatrix c=exp(x);
	CMatrix d=log10(x);
	CMatrix e=log(y);
	cout << "z=" << z.getString(5);
	cout << "a=" << a.getString(5);
	cout << "b=" << b.getString(5);
	cout << "c=" << c.getString(5);
	cout << "d=" << d.getString(5);
	cout << "e=" << e.getString(5);*/
	/*try {
		
		cout << "no=" << variableNo<<endl;
		for (int i = 0; i < variableNo; i++)
			cout<<varNames[i] << "=" <<varContent[i]<<endl;
	}
	catch (const char* error) { cout << error<<endl; }*/

	if (argc == 2)
	{
		string file = argv[1];
		ifstream infile(file);
		string line,info="";
		int bracketCounter = 0;
		while (getline(infile, line)) {
			for (int charIndex = 0; charIndex < line.length(); charIndex++) {
				if (line[charIndex] == '[') {
					bracketCounter++;
				}
				else if (line[charIndex] == ']') {
					bracketCounter--;
				}
			}
			info += line;
			if (bracketCounter == 0 && info!="") {
				decode(info, varNames, varContent, variableNo);
				info = "";
				
			}
		}
	}
	else
	{
		string line, info = "";
		int bracketCounter = 0;
		cout << ">>";
		while (getline(cin, line)) {
			
			for (int charIndex = 0; charIndex < line.length(); charIndex++) {
				if (line[charIndex] == '[') {
					bracketCounter++;
				}
				else if (line[charIndex] == ']') {
					bracketCounter--;
				}
			}
			info += line;
			if (bracketCounter == 0 && info != "") {
				decode(info, varNames, varContent, variableNo);
				info = "";

			}
			cout << ">>";
		}
	}


	



    return 0;
}

