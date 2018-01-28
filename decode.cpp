//#include "stdafx.h"
#include "decode.h"
#include "solve.h"
#include "cmatrix.h"
#include <iostream>
#include <sstream>
#include <algorithm>
//#include <bits/stdc++.h>
using namespace std;

//map<string, pair<string, pair<int, int> > > matrix_data;
void errors_handler(string input) {
	// guarantee every semicolon have spaces before and after
	int index = 0;
	while (true) {
		index = input.find(";", index);
		if (index == string::npos) break;
		input.replace(index, 1, " ; "); index += 3;
	}
/*
	char str[1023]; strcpy(str, input.c_str());
	char *parser = strtok(str, " =");
	matrix_data[parser].first = input;
	char *matrix_var = parser;
	int rows = 1, cols = -1;
	set<int> checker;
	while (true) {
		parser = strtok(NULL, " =[]");
		if (parser == NULL) break;
		cols += 1;
		if (!strcmp(parser, ";")) {
			checker.insert(cols);
			rows += 1;
			cols = 0;
		}
	}
	checker.insert(cols);
	if (checker.size() != 1) throw("Invalid matrix dimension");
	matrix_data[matrix_var].second.first = rows;
	matrix_data[matrix_var].second.second = cols;
	// //show all matrix_data 
	map<string, pair<string, pair<int, int> > > ::iterator mapit;
	for (mapit = matrix_data.begin(); mapit != matrix_data.end(); mapit++) {
		cout << "matrix(" << mapit->first << ")rows:  " << mapit->second.second.first << ",cols: " << mapit->second.second.second << "\n";
	}*/
}
void print(string s, string varNames[100], string varContent[100], int& variableNo) {
	for (int index = 0; index < variableNo; index++) {
		if (s == varNames[index]) {
			if(varContent[index][0]!='[')
			cout << varNames[index] << "=" << varContent[index] << endl;
			else {
				CMatrix m = CMatrix(varContent[index]);
				cout << varNames[index] << "=" << m.getString() << endl;
			}
			return;
		}
	}
	 cout<<s<< " is not defined"<<endl;
	
}
void decode(string info, string varNames[100], string varContent[100], int& variableNo) {
	
	//errors_handler(info);
	if (info.find("rand") != string::npos || info.find("eye") != string::npos || info.find("ones") != string::npos || info.find("zeros") != string::npos) {
		//cout << "send: " << info << "to defSpecialMat" << endl;
		defSpecialMat(info, varNames, varContent, variableNo);
		return;
	}

	for (int charIndex = 0; charIndex < info.length(); charIndex++) {
		if (info[charIndex] == '[') {
			//cout << "send: " << info << "to defMat" << endl;
			defMat(info, varNames, varContent, variableNo);
			return;
		}
	}
	string operators = "+-*/.^'!()\\&|";
	int equalFlag = info.find('=');
	if (equalFlag != string::npos) {
		//cout << "send: " << info << "to doOperation" << endl;
		doOperation(info, varNames, varContent, variableNo);
		return;
	}
	for (int charIndex = 0; charIndex < info.length(); charIndex++) {
		for (int opIndex = 0; opIndex < operators.length(); opIndex++) {
			if (info[charIndex] == operators[opIndex]) {
					//cout << "send: " << info << "to doOperation" << endl;
					doOperation(info, varNames, varContent, variableNo);
					return;
			}
		}
	}
	//cout << "send: " << info << "to print" << endl;
	print(info, varNames, varContent, variableNo);
}
void defSpecialMat(string s, string varNames[100], string varContent[100], int& variablesNo) {
	int NR; int NC; int x = 0; int h = 0; int initialization; string str;
	int len = s.length();
	// for removing any spaces in string s
	for (int i = 0; i<len; i++)
	{
		if (s[i] == ' ')
		{
			for (int j = i; j<len; j++)
			{
				s[j] = s[j + 1];
			}
			len--;
		}
	}
	int i = s.find('=');
	str = s.substr(0, i);
	int j = s.find('(');
	string initial = s.substr(i + 1, j - 2);
	NR = atoi(s.substr(j + 1, s.find(',') - 1).c_str());
	NC = atoi(s.substr(s.find(',') + 1, s.find(')') - 1).c_str());

	if (initial[0] == 'Z' || initial[0] == 'z') initialization = 0;
	else if (initial[0] == 'O' || initial[0] == 'o') initialization = 1;
	else if (initial[0] == 'E' || initial[0] == 'e')
	{
		if (NR != NC)
		{
			throw ("Invalid Matrix Dimension");
		}
		else initialization = 2;
	}
	else if (initial[0] == 'R' || initial[0] == 'r') initialization = 3;
	else initialization = 4;

	for (int k = 0; k<variablesNo; k++)
	{
		if (str == varNames[k])
		{
			CMatrix content(NR, NC, initialization, 0.0);
			varContent[k] = content.getOriginalString();
			h = 1;
			break;
		}

	}
	if (h == 0) {
		varNames[variablesNo] = str;
		CMatrix content(NR, NC, initialization, 0.0);
		varContent[variablesNo] = content.getOriginalString();
		variablesNo++;
	}

	std::size_t found1 = s.find(';');
	if (found1 != std::string::npos)
	{
		x = 1;
	}
	if (x == 0)
	{
		print(str, varNames, varContent, variablesNo);
	}



}

bool isFloat(string myString)
{
	istringstream iss(myString);
	double f;
	iss >> noskipws >> f; // noskipws considers leading whitespace invalid
						  // Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}

bool isComplex(string mystring)
{
	std::size_t found = mystring.find_first_of("ij");
	if (found == std::string::npos)
	{
		return false;
	}
	return true;
}


//#include <algorithm>
int countInString(const string& s, const string& something, const int& firstPos, int lastPos) {
	if ((firstPos > lastPos && lastPos >= 0) || firstPos < 0) return 0;

	int sLength = s.length(), count = 0, lastFountPos = firstPos - 1;
	if (lastPos < 0) lastPos = sLength;
	const int npos = -1;

	while (true) {
		lastFountPos = s.find(something, lastFountPos + 1);
		if (lastFountPos != npos) count++;
		else if (lastFountPos == npos || lastFountPos >= sLength) break;
	}

	return count;
}

void defMat(string s, string varNames[100], string varContent[100], int& variablesNo) {

	string sTemp[100][100];
	int writtenColumns[100]; // Indicates how many columns have been written per each row
	bool writable[100][100]; // Boolen matrix indicating writeable elements in the matrix
	for (int i = 0; i < 100; i++) writtenColumns[i] = 0;

	bool printMat = true;
	bool saveMat = false;
	int savePos = variablesNo;
	{ // Preparing the string for processing and cutting the name of the matrix
		string s2 = s;
		int pos1 = s.find_first_of('[');
		int pos2 = s.find_last_of(']');
		s = s.substr(pos1, pos2 - pos1 + 1);
		for (int i = s2.length() - 1; i >= 0; i--) if (s2[i] == ';') { printMat = false; break; }
		else if (s2[i] == ']') break;
		s2 = s2.replace(pos1, s.length() - pos1, "");
		pos1 = 0;
		pos2 = s2.find('=');
		if (pos2 != string::npos) s2 = s2.substr(pos1, pos2 - pos1);
		if (s2.length() >= 1 && pos2 != string::npos) {
			while (s2.length() != 0)
				if (s2[s2.length() - 1] == ' ') s2.replace(s2.length() - 1, 1, "");
				else break;
				while (s2.length() != 0)
					if (s2[0] == ' ') s2.replace(0, 1, "");
					else break;
					if (s2.length() > 0) saveMat = true;
					for (int i = 0; i < variablesNo; i++)
						if (varNames[i] == s2) {
							savePos = i; break;
						}
		}
		if (saveMat) varNames[savePos] = s2;
		// cout << s2 << " - " << s << endl;
	}

	{ // Replacing all instances of variable names in the input with their respective values
	  // cout << s << endl;
		for (int i = 0, x = -1; i < variablesNo; i++) {
			x = countInString(s, varNames[i]);
			while (0 < x--) s.replace(s.find_first_of(varNames[i]), varNames[i].length(), varContent[i]);
		}
		// cout << s << endl;
	}

	// Checking the input for possible errors
	int matricesToConcatinate = countInString(s, "[");
	if (matricesToConcatinate != countInString(s, "]")) throw("Invalid matrix string");

	// Counting the matrices needed to be concatinated and initializing all variables needed
	int sLength = s.length(), npos = -1, *iR, *iC, *nR, *nC, *baseR, *baseC, workingOnMatrix = npos, workedMatrices = npos, *parentMatrix;
	bool *weCanChangeRow, *weCanChangeColumn;
	iR = new int[matricesToConcatinate];
	nR = new int[matricesToConcatinate];
	baseR = new int[matricesToConcatinate];
	weCanChangeRow = new bool[matricesToConcatinate];
	iC = new int[matricesToConcatinate];
	nC = new int[matricesToConcatinate];
	baseC = new int[matricesToConcatinate];
	weCanChangeColumn = new bool[matricesToConcatinate];
	parentMatrix = new int[matricesToConcatinate];
	for (int i = 0; i < matricesToConcatinate; i++) iR[i] = 0, iC[i] = 0, nR[i] = 0, nC[i] = 0, weCanChangeRow[i] = false, weCanChangeColumn[i] = false;
	// Building the string array
	for (int i = 0; i < sLength; i++) {
		// cout << nR[0] << " " << nR[1] << " " << nR[2] << " " << nR[3] << " " << nR[4] << endl;
		if (s[i] == '[') {
			// if (workingOnMatrix != npos && iC[workingOnMatrix] != npos) cout << "Row " << iR[workingOnMatrix] << " Column " << iC[workingOnMatrix] << " = " << sTemp[iR[workingOnMatrix]][iC[workingOnMatrix]] << endl;
			int tempWorkingOnMatrix = workingOnMatrix;
			workedMatrices++; workingOnMatrix = workedMatrices;
			parentMatrix[workingOnMatrix] = tempWorkingOnMatrix;
			// cout << "Fount [ and changing workingOnMatrix to " << workingOnMatrix << endl;
			if (workingOnMatrix != 0) {
				baseR[workingOnMatrix] = iR[parentMatrix[workingOnMatrix]];
				if (iC[parentMatrix[workingOnMatrix]] == npos) iC[parentMatrix[workingOnMatrix]] = baseC[parentMatrix[workingOnMatrix]];
				baseC[workingOnMatrix] = iC[parentMatrix[workingOnMatrix]];
				iR[workingOnMatrix] = baseR[workingOnMatrix];
				iC[workingOnMatrix] = npos;
			}
			else baseR[workingOnMatrix] = 0, baseC[workingOnMatrix] = 0, iR[workingOnMatrix] = 0, iC[workingOnMatrix] = npos;
			// cout << "Base R = " << baseR[workingOnMatrix] << " base C = " << baseC[workingOnMatrix] << endl;
		}
		else if (s[i] == ']') {
			// cout << "Row " << iR[workingOnMatrix] << " Column " << iC[workingOnMatrix] << " = " << sTemp[iR[workingOnMatrix]][iC[workingOnMatrix]] << endl;
			if (iC[workingOnMatrix] == npos && nR[workingOnMatrix] != 0) {
				nR[workingOnMatrix]--;
				// cout << "Changing nR of " << workingOnMatrix << " to " << nR[workingOnMatrix] << endl;
			}
			if (!weCanChangeColumn[workingOnMatrix] && weCanChangeRow[workingOnMatrix]) {
				iC[workingOnMatrix]--;
				// cout << "Changing iC of " << workingOnMatrix << " to " << iC[workingOnMatrix] << endl;
			}
			if (nC[workingOnMatrix] < (iC[workingOnMatrix] - baseC[workingOnMatrix])) {
				nC[workingOnMatrix] = iC[workingOnMatrix] - baseC[workingOnMatrix];
				// cout << "Changing nC of " << workingOnMatrix << " to " << nC[workingOnMatrix] << " due to bigger iC" << endl;
			}

			if (parentMatrix[workingOnMatrix] != npos) {
				if (iC[parentMatrix[workingOnMatrix]] == npos) iC[parentMatrix[workingOnMatrix]] = baseC[parentMatrix[workingOnMatrix]];
				iC[parentMatrix[workingOnMatrix]] += nC[workingOnMatrix] + 1;
				// cout << "Changing iC of " << parentMatrix[workingOnMatrix] << " to " << iC[parentMatrix[workingOnMatrix]] << endl;
			}
			else break;

			if (iR[parentMatrix[workingOnMatrix]] < nR[workingOnMatrix] + baseR[workingOnMatrix]) {
				nR[parentMatrix[workingOnMatrix]] = nR[workingOnMatrix] + baseR[workingOnMatrix] - baseR[parentMatrix[workingOnMatrix]];
				// cout << "Changing nR of " << parentMatrix[workingOnMatrix] << " to " << nR[parentMatrix[workingOnMatrix]] << endl;
			}

			workingOnMatrix = parentMatrix[workingOnMatrix];
			// cout << "Fount ] and changing workingOnMatrix to " << workingOnMatrix << endl;
			if (nC[workingOnMatrix] < (iC[workingOnMatrix] - baseC[workingOnMatrix] - 1)) {
				nC[workingOnMatrix] = iC[workingOnMatrix] - baseC[workingOnMatrix] - 1;
				// cout << "Changing nC of " << workingOnMatrix << " to " << nC[workingOnMatrix] << " due to bigger iC" << endl;
			}

			if (nC[workingOnMatrix] == (iC[workingOnMatrix] - baseC[workingOnMatrix] - 1)) weCanChangeRow[workingOnMatrix] = true;
		}
		// might be error when [1 2 3; [1 2];[1,2],[1; 2]]
		else if (s[i] == ';' && weCanChangeRow[workingOnMatrix]) {
			// cout << "Row " << iR[workingOnMatrix] << " Column " << iC[workingOnMatrix] << " = " << sTemp[iR[workingOnMatrix]][iC[workingOnMatrix]] << endl;
			if (iC[workingOnMatrix] == npos) {
				nC[workingOnMatrix]--;
				// cout << "Fount ; and changing nC of " << workingOnMatrix << " to " << nC[workingOnMatrix] << endl;
			}
			weCanChangeColumn[workingOnMatrix] = false;
			weCanChangeRow[workingOnMatrix] = false;
			iC[workingOnMatrix] = npos;
			nR[workingOnMatrix]++;
			iR[workingOnMatrix] = baseR[workingOnMatrix] + nR[workingOnMatrix];
			// cout << "Fount ; and changing iR and nR of " << workingOnMatrix << " to " << iR[workingOnMatrix] << " and " << nR[workingOnMatrix] << endl;
		}
		else if ((s[i] == ' ' || s[i] == ',') && weCanChangeColumn[workingOnMatrix]) {
			// cout << "Row " << iR[workingOnMatrix] << " Column " << iC[workingOnMatrix] << " = " << sTemp[iR[workingOnMatrix]][iC[workingOnMatrix]] << endl;
			weCanChangeColumn[workingOnMatrix] = false;
			iC[workingOnMatrix]++;
			if (nC[workingOnMatrix] < iC[workingOnMatrix] - baseC[workingOnMatrix] - 1) {
				nC[workingOnMatrix] = iC[workingOnMatrix] - baseC[workingOnMatrix] - 1;
				// cout << "Changing nC of " << workingOnMatrix << " to " << nC[workingOnMatrix] << " due to bigger iC" << endl;
			}
			// cout << "Fount " << s[i] << " and changing iC of " << workingOnMatrix << " to " << iC[workingOnMatrix] << endl;
		}
		else if (s[i] == ' ' || s[i] == ',' || s[i] == ';');
		else {
			weCanChangeColumn[workingOnMatrix] = true;
			if (iC[parentMatrix[workingOnMatrix]] == npos) iC[parentMatrix[workingOnMatrix]] = baseC[parentMatrix[workingOnMatrix]];
			if (iC[workingOnMatrix] == npos) iC[workingOnMatrix] = baseC[workingOnMatrix];
			if (nC[workingOnMatrix] == iC[workingOnMatrix] - baseC[workingOnMatrix]) weCanChangeRow[workingOnMatrix] = true;
			sTemp[iR[workingOnMatrix]][iC[workingOnMatrix]] += s[i];
			if (writable[iR[workingOnMatrix]][iC[workingOnMatrix]]) writtenColumns[iR[workingOnMatrix]]++;
			writable[iR[workingOnMatrix]][iC[workingOnMatrix]] = false;
		}
	}

	int NR = nR[0] + 1;
	int NC = nC[0] + 1;

	// Printing all data about matrices
	/*for (int i = 0; i < matricesToConcatinate; i++)
	cout << i << "\t" << iR[i] << "\t" << nR[i] << "\t" << baseR[i] << "\t" << iC[i] << "\t" << nC[i] << "\t" << baseC[i] << endl;*/

	// Printing the string matrix before doOperation
	/*for (int ir = 0; ir < NR; ir++, cout << endl)
	for (int ic = 0; ic < NC; ic++)
	cout << "(" << ir << "," << ic << ") " << sTemp[ir][ic] << "\t";*/

	// Calculating elements of the string matrix
	CMatrix tempMat(NR, NC); string temp;
	for (int ir = 0; ir < NR; ir++)
		for (int ic = 0; ic < NC; ic++) {
			temp = sTemp[ir][ic] + ";";
			doOperation(temp, varNames, varContent, variablesNo);
			tempMat.values[ir][ic] = atof(temp.c_str());
		}

	if (saveMat) {
		varContent[savePos] = tempMat.getOriginalString();
		if (savePos == variablesNo) variablesNo++;
	}
	if (printMat) cout << (saveMat ? varNames[savePos] : "ans") << " = " << tempMat.getString();

	// Printing the string matrix after doOperation
	/*for (int ir = 0; ir < NR; ir++, cout << endl)
	for (int ic = 0; ic < NC; ic++)
	cout << "(" << ir << "," << ic << ") " << sTemp[ir][ic] << "\t";*/

	//cout << sTemp[ir][ic] << "\t";//cout << ir << "," << ic << " " << sTemp[ir][ic] << " ";


	delete[] iR, iC, nR, nC, weCanChangeColumn, weCanChangeRow, parentMatrix;
	return;
}
void doOperation(string& s, string varNames[100], string varContent[100], int& variablesNo)
{
	string tempstr;
	//int cursor=0;
	//removing all spaces from string
	for (int string_index = 0; string_index < s.length(); string_index++)
	{
		if (s[string_index] == ' ') s.replace(string_index, s.length() - string_index, s.substr(string_index + 1, s.length() - string_index - 1));
	}
	// sperating it to 2 arrays , Parameters array and operators array
	string parameters[100], operations[100];
	string operators = "=+-*/.^'!()&|;\\";
	int stack_index = 0;
	for (int string_index = 0; string_index<s.length(); string_index++)
	{
		if (s[string_index] == ' ') continue;
		//parameters[stack_index]="";  operations[stack_index]=""; //initialinzing the values of stack elements
		bool operator_exist = false;
		bool nextoperator_exist = false;
		bool prevoperator_exist = false;
		bool nextisdigit = false;
		if (s[string_index] == '.') { if (isdigit(s[string_index + 1])) nextisdigit = true; }
		for (int checking_index = 0; checking_index<operators.length(); checking_index++)
		{
			if (s[string_index] == operators[checking_index]) operator_exist = true;
			if (s[string_index + 1] == operators[checking_index]) nextoperator_exist = true;
			if (string_index != 0) { if (s[string_index - 1] == operators[checking_index]) prevoperator_exist = true; }
		}

		if (operator_exist == true)
		{
			if ((s[string_index] == '.'&&nextisdigit == true) || (s[string_index] == '-'&& s[string_index - 1] != '.' && (prevoperator_exist == true &&/* s[string_index - 1] == '='&&*/s[string_index - 1] != ')'))) parameters[stack_index].insert(parameters[stack_index].end(), s[string_index]);
			else
			{
				if (s[string_index] == '.'&&nextisdigit == false)stack_index++;
				operations[stack_index].insert(operations[stack_index].end(), s[string_index]);
			}
			if (s[string_index - 1] == '.' /*&& operator_exist == true */) stack_index++;
			else if (s[string_index] != '.' &&
				((s[string_index] == '!' || s[string_index] == ';' || s[string_index] == '\'') ||
				(s[string_index] != '-' && (prevoperator_exist == false || s[string_index - 1] == '=' || s[string_index - 1] == ')') && s[string_index + 1] != '.') ||
					(s[string_index] == '-' &&s[string_index - 1] != '='&& (prevoperator_exist == false /*|| s[string_index - 1] == '=' */|| s[string_index - 1] == ')')) ||
					(s[string_index] == '(')
					)) stack_index++;
		}
		else
		{
			parameters[stack_index].insert(parameters[stack_index].end(), s[string_index]);
			if (nextoperator_exist == true && nextisdigit == false && s[string_index] != '.'&& s[string_index + 1] != '.') stack_index++;
			if (string_index == s.length() - 1) stack_index++;
		}

	}
							///////////////////
						cout<<stack_index<<endl;
						for(int i=0 ; i < stack_index ; i++)
						{
						cout << parameters[i] << "----->" << operations[i]<<endl;
						}
						///////////////////

	//solve factorial or transpose operations
	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "!" || operations[index] == "'")
		{
			tempstr = solve(parameters[index - 1] + operations[index], varNames, varContent, variablesNo);
			parameters[index - 1] = tempstr;
			operations[index] = "";
			//remove the empty elements in the stack
			for (int WBindex = index; WBindex<stack_index; WBindex++)
			{
				operations[WBindex] = operations[WBindex + 1];
				parameters[WBindex] = parameters[WBindex + 1];
			}
			stack_index--;
		}
	}

	//slove arguments

	//solve arguments "(" do some operations")"

	bool more_arguments = false;
	do
	{
		for (int index = stack_index - 1; index>0; index--) //index is the index of opening arguments
		{
			bool simpletrignometricfn_exist = false;
			if (operations[index] == "("/*&&(operations[index]=="*"||operations[index]=="/")*/)
			{
				for (int closingArgumentIndex = index; closingArgumentIndex<stack_index; closingArgumentIndex++)
				{
					if (operations[closingArgumentIndex] == ")")
					{
						bool argument_exist = false;
						do
						{
							//do power operation
							for (int solveArgumentindex = index; solveArgumentindex<closingArgumentIndex; solveArgumentindex++)
							{
								if (operations[solveArgumentindex] == "^" || operations[solveArgumentindex] == ".^")
								{
									tempstr = solve(parameters[solveArgumentindex - 1] + operations[solveArgumentindex] + parameters[solveArgumentindex + 1], varNames, varContent, variablesNo);
									parameters[solveArgumentindex - 1] = tempstr;
									operations[solveArgumentindex] = "";
									parameters[solveArgumentindex + 1] = "";
									//remove the empty elements in the stack
									for (int WBindex = solveArgumentindex; WBindex<stack_index; WBindex++)
									{
										operations[WBindex] = operations[WBindex + 2];
										parameters[WBindex] = parameters[WBindex + 2];
									}
									stack_index -= 2;
									closingArgumentIndex -= 2;
									solveArgumentindex -= 3;
								}
							}
							// if we find "(" @ index and index+2=")" then it might be sins ,cos ,.. etc 
							simpletrignometricfn_exist = false;
							for (int solveArgumentindex = index; solveArgumentindex<closingArgumentIndex; solveArgumentindex++)
							{
								if (operations[solveArgumentindex] == "(" && operations[solveArgumentindex + 2] == ")")
								{
									tempstr = solve(parameters[solveArgumentindex - 1] + operations[solveArgumentindex] + parameters[solveArgumentindex + 1] + operations[solveArgumentindex + 2], varNames, varContent, variablesNo);
									parameters[solveArgumentindex - 1] = tempstr;
									operations[solveArgumentindex] = "";
									parameters[solveArgumentindex + 1] = "";
									operations[solveArgumentindex + 2] = "";
									//remove the empty elements in the stack
									for (int WBindex = solveArgumentindex; WBindex<stack_index; WBindex++)
									{
										operations[WBindex] = operations[WBindex + 3];
										parameters[WBindex] = parameters[WBindex + 3];
									}
									stack_index -= 3;

									if (solveArgumentindex == index&&closingArgumentIndex == index + 2) { simpletrignometricfn_exist = true; break; }
									index -= 3;
								}
							}
							if (simpletrignometricfn_exist) break;
							//do mul and div operation
							for (int solveArgumentindex = index; solveArgumentindex<closingArgumentIndex; solveArgumentindex++)
							{

								if (operations[solveArgumentindex] == "*" || operations[solveArgumentindex] == "/" || operations[solveArgumentindex] == ".*" || operations[solveArgumentindex] == "./" || operations[index] == "\\" || operations[index] == ".\\")
								{
									tempstr = solve(parameters[solveArgumentindex - 1] + operations[solveArgumentindex] + parameters[solveArgumentindex + 1], varNames, varContent, variablesNo);
									parameters[solveArgumentindex - 1] = tempstr;
									operations[solveArgumentindex] = "";
									parameters[solveArgumentindex + 1] = "";
									//remove the empty elements in the stack
									for (int WBindex = solveArgumentindex; WBindex<stack_index; WBindex++)
									{
										operations[WBindex] = operations[WBindex + 2];
										parameters[WBindex] = parameters[WBindex + 2];
									}
									stack_index -= 2;
									closingArgumentIndex -= 2;
									solveArgumentindex -= 3;



								}
							}

							//do add and sub operations
							for (int solveArgumentindex = index; solveArgumentindex<closingArgumentIndex; solveArgumentindex++)
							{
								if (operations[solveArgumentindex] == "+" || operations[solveArgumentindex] == "-" || operations[solveArgumentindex] == ".+" || operations[solveArgumentindex] == ".-")
								{
									tempstr = solve(parameters[solveArgumentindex - 1] + operations[solveArgumentindex] + parameters[solveArgumentindex + 1], varNames, varContent, variablesNo);
									parameters[solveArgumentindex - 1] = tempstr;
									operations[solveArgumentindex] = "";
									parameters[solveArgumentindex + 1] = "";
									//remove the empty elements in the stack
									for (int WBindex = solveArgumentindex; WBindex<stack_index; WBindex++)
									{
										operations[WBindex] = operations[WBindex + 2];
										parameters[WBindex] = parameters[WBindex + 2];
									}
									stack_index -= 2;
									closingArgumentIndex -= 2;
									solveArgumentindex -= 3;
								}
							}

							//do bitwise and , or operations
							for (int solveArgumentindex = index; solveArgumentindex<closingArgumentIndex; solveArgumentindex++)
							{
								if (operations[solveArgumentindex] == "&" || operations[solveArgumentindex] == "|")
								{

									tempstr = solve(parameters[solveArgumentindex - 1] + operations[solveArgumentindex] + parameters[solveArgumentindex + 1], varNames, varContent, variablesNo);
									parameters[solveArgumentindex - 1] = tempstr;
									operations[solveArgumentindex] = "";
									parameters[solveArgumentindex + 1] = "";
									//remove the empty elements in the stack
									for (int WBindex = solveArgumentindex; WBindex<stack_index; WBindex++)
									{
										operations[WBindex] = operations[WBindex + 2];
										parameters[WBindex] = parameters[WBindex + 2];
									}
									stack_index -= 2;
									closingArgumentIndex -= 2;
									solveArgumentindex -= 3;
								}
							}
							for (int argumentindex = index; argumentindex<closingArgumentIndex; argumentindex++)
							{
								if (operations[argumentindex] != ""&&operations[argumentindex] != "("&&operations[argumentindex] != ")")  argument_exist = true;
								else argument_exist = false;
							}
						} while (argument_exist);


						// testing for loop
						/*tempstr="";
						for (int testindex=1 ; testindex < closingArgumentIndex-index ; testindex++)
						{
						if(testindex%2==0) tempstr.insert(tempstr.length() , operations[index+testindex]);//BracesDoOpearation[0].insert(BracesDoOpearation[0].end() , parameters[index+testindex]);
						else tempstr.insert(tempstr.length() , parameters[index+testindex]);
						}
						cout<<"parsing is"<<tempstr<<endl;*/


						if (parameters[index - 1] == "") //if not sin or cos remove arguments "(   )"
						{
							//replacing old by new data and remove unused elements from stack
							parameters[index] = parameters[index + 1];
							for (int removeindex = 0; removeindex < closingArgumentIndex - index; removeindex++)
							{
								if (removeindex % 2 == 0) operations[index + removeindex] = "";
								else parameters[index + removeindex] = "";
							}




							//remove the empty elements in the stack


							for (int WBindex = index + 1; WBindex<stack_index; WBindex++)
							{
								operations[WBindex] = operations[WBindex + (closingArgumentIndex - index)];
								parameters[WBindex] = parameters[WBindex + (closingArgumentIndex - index)];
							}
							//stack_index -= (closingArgumentIndex - index);
							stack_index -= 2;
							index -= closingArgumentIndex - index;

							break;
						}
						if (simpletrignometricfn_exist) break;
					}
				}
			}
			if (simpletrignometricfn_exist) break;
		}

		for (int argumentindex = 0; argumentindex<stack_index; argumentindex++)
		{
			if (/*operations[argumentindex] != ""&&*/operations[argumentindex] == "(" || operations[argumentindex] == ")") { more_arguments = true; break; }
			else more_arguments = false;
		}
	} while (more_arguments);



	// if we find "(" @ index and index+2=")" then it might be sins ,cos ,.. etc 
	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "(" && operations[index + 2] == ")")
		{
			tempstr = solve(parameters[index - 1] + operations[index] + parameters[index + 1] + operations[index + 2], varNames, varContent, variablesNo);
			parameters[index - 1] = tempstr;
			operations[index] = "";
			parameters[index + 1] = "";
			operations[index + 2] = "";
			//remove the empty elements in the stack
			for (int WBindex = index; WBindex<stack_index; WBindex++)
			{
				operations[WBindex] = operations[WBindex + 3];
				parameters[WBindex] = parameters[WBindex + 3];
			}
			stack_index -= 3;
			index -= 3;
		}
	}



	//slove simple opeartions like * , / , ... etc
	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "^" || operations[index] == ".^")
		{
			tempstr = solve(parameters[index - 1] + operations[index] + parameters[index + 1], varNames, varContent, variablesNo);
			//tempstr = parameters[index-1]+operations[index]+parameters[index+1];
			parameters[index - 1] = tempstr;
			operations[index] = "";
			parameters[index + 1] = "";
			//remove the empty elements in the stack
			for (int WBindex = index; WBindex<stack_index; WBindex++)
			{
				operations[WBindex] = operations[WBindex + 2];
				parameters[WBindex] = parameters[WBindex + 2];
			}
			stack_index -= 2;
			index -= 2;
		}
	}
	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "*" || operations[index] == "/" || operations[index] == ".*" || operations[index] == "./" || operations[index] == "\\" || operations[index] == ".\\")
		{
			tempstr = solve(parameters[index - 1] + operations[index] + parameters[index + 1], varNames, varContent, variablesNo);
			//tempstr = parameters[index-1]+operations[index]+parameters[index+1];
			parameters[index - 1] = tempstr;
			operations[index] = "";
			parameters[index + 1] = "";
			//remove the empty elements in the stack
			for (int WBindex = index; WBindex<stack_index; WBindex++)
			{
				operations[WBindex] = operations[WBindex + 2];
				parameters[WBindex] = parameters[WBindex + 2];
			}
			stack_index -= 2;
			index -= 2;
		}
	}
	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "+" || operations[index] == "-" || operations[index] == ".+" || operations[index] == ".-")
		{
			//cout<<parameters[index - 1] + operations[index] + parameters[index + 1]<<endl;
			tempstr = solve(parameters[index - 1] + operations[index] + parameters[index + 1], varNames, varContent, variablesNo);
			//tempstr = parameters[index-1]+operations[index]+parameters[index+1];
			parameters[index - 1] = tempstr;
			operations[index] = "";
			parameters[index + 1] = "";
			//remove the empty elements in the stack
			for (int WBindex = index; WBindex<stack_index; WBindex++)
			{
				operations[WBindex] = operations[WBindex + 2];
				parameters[WBindex] = parameters[WBindex + 2];
			}
			stack_index -= 2;
			index -= 2;
		}
	}

	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "&" || operations[index] == "|")
		{
			//cout<<parameters[index - 1] + operations[index] + parameters[index + 1]<<endl;
			tempstr = solve(parameters[index - 1] + operations[index] + parameters[index + 1], varNames, varContent, variablesNo);
			//tempstr = parameters[index-1]+operations[index]+parameters[index+1];
			parameters[index - 1] = tempstr;
			operations[index] = "";
			parameters[index + 1] = "";
			//remove the empty elements in the stack
			for (int WBindex = index; WBindex<stack_index; WBindex++)
			{
				operations[WBindex] = operations[WBindex + 2];
				parameters[WBindex] = parameters[WBindex + 2];
			}
			stack_index -= 2;
			index -= 2;
		}
	}

	/*if (stack_index == 4 && operations[1] == "="&&parameters[0] == "temp" && parameters[3]==";")
	{
	s = parameters[0] + operations[1] + parameters[2];
	}*/
	if (stack_index == 4 && operations[1] == "="&&parameters[0] != "temp"&& operations[3] == ";")
	{
		bool variablexsist = false;
		for (int checkingindex = 0; checkingindex<variablesNo; checkingindex++)
		{
			if (varNames[checkingindex] == parameters[0])
			{
				variablexsist = true;
				varNames[checkingindex] = parameters[0];
				varContent[checkingindex] = parameters[2];
				break;
			}
		}
		if (variablexsist == false)
		{
			varNames[variablesNo] = parameters[0];
			varContent[variablesNo] = parameters[2];
			variablesNo++;
		}
	}
	/*else if (stack_index == 3 && operations[1] == "="&&parameters[0] == "temp")
	{
	s = parameters[0] + operations[1] + parameters[2];
	}*/
	else if (stack_index == 3 && operations[1] == "=" &&parameters[0] != "temp")
	{
		cout<<"done";
		bool variablexsist = false;
		for (int checkingindex = 0; checkingindex<variablesNo; checkingindex++)
		{
			if (varNames[checkingindex] == parameters[0])
			{
				variablexsist = true;
				varNames[checkingindex] = parameters[0];
				varContent[checkingindex] = parameters[2];
				break;
			}
		}
		if (variablexsist == false)
		{
			varNames[variablesNo] = parameters[0];
			varContent[variablesNo] = parameters[2];
			variablesNo++;
		}
		print(parameters[0], varNames, varContent, variablesNo);
	}
	else if (stack_index == 2 && operations[1] == ";")
	{
		s = parameters[0];
	}
	else { s = parameters[0]; cout << parameters[0]; }
}
