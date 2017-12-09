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
	int variableNo =0;
	/*CMatrix x = CMatrix(5, 5, 3);
	CMatrix y = CMatrix(5, 5, 3);
	cout << "x="<<x.getOriginalString();
	cout << x.getString(5);
	cout << "y=" << y.getOriginalString();
	cout << y.getString(5);
	CMatrix z=x.dotMul(y);
	CMatrix a=x.dotDiv(y);
	CMatrix b=x.dotPow(5);
	CMatrix c =y.dotPow(6);
	CMatrix d=x.lDiv(y);
	CMatrix e=x.dotLDiv(y);
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

