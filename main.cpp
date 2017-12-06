#include "cmatrix.h"
#include "solve.h"
#include "decode.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc,char* argv[])
{
	string varNames[100], varContent[100];
	int variableNo =0;
	try {
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
		/*cout << "no =" << variableNo<<endl;
		for (int i = 0; i < variableNo; i++)
			cout<<varNames[i] << "=" <<varContent[i]<<endl;*/
		
	}
	catch (const char* error) { cout << error<<endl; }
    return 0;
}

