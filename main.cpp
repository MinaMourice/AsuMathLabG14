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
	int variableNo = 0;
	
	if (argc == 2)
	{
		string file = argv[1];
		ifstream infile(file);
		string line,info="";
		int bracketCounter = 0;
		try {
			if (!(infile.is_open()))
				throw("Cann't open the file");
		}
		catch (const char* error) {
			cout << error << endl;
		}
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
				try {

					decode(info, varNames, varContent, variableNo);

					info = "";
				}
				catch (char* message) {
					cout << message << endl;
					info = "";
				}
				
			}
			else if (bracketCounter != 0 && info != "") {
				info += ";";
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
				try {
					
					decode(info, varNames, varContent, variableNo);
					
					info = "";
				}
				catch ( char* message) {
					cout << message << endl;
					info = "";
				}
			}
			else if (bracketCounter != 0 && info != "") {
				info += ";";
			}
			cout << ">>";
		}
	}


	



    return 0;
}

