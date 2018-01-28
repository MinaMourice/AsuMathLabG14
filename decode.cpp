#include "stdafx.h"
#include "decode.h"
#include "solve.h"
#include "cmatrix.h"
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

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
void replaceFromStackIntoString(string &s, const string varNames[100], const string varContent[100], const int& variablesNo) {
	int npos = -1;

	// Copying stack
	string var_names[100];
	string var_content[100];
	for (int i = 0; i < variablesNo; i++) {
		var_names[i] = varNames[i];
		var_content[i] = varContent[i];
	}

	// Sorting stack
	string tempName, tempContent;
	for (int i = 0; i < variablesNo; i++)
		for (int j = i; j < variablesNo; j++) {
			if (var_names[i].length() < var_names[j].length()) {
				tempName = var_names[i]; var_names[i] = var_names[j]; var_names[j] = tempName;
				tempContent = var_content[i]; var_content[i] = var_content[j]; var_content[j] = tempContent;
			}
		}

	for (int i = 0; i < variablesNo; i++) while (s.find(var_names[i]) != npos) s.replace(s.find(var_names[i]), var_names[i].length(), var_content[i]);
}
bool operator != (const char &c, const string &s) {
	int sLength = s.length();
	for (int i = 0; i < sLength; i++) if (s[i] == c) return false;
	return true;
}
void removeSpaces(string &s, string operation, const bool afterOnly = false) {
	int iterationsNumber = countInString(s, operation);
	int npos = -1;

	for (int i = 0, referanceCharIndex = npos, currentCharIndex; i < iterationsNumber; i++) {
		referanceCharIndex = s.find(operation, referanceCharIndex + 1);

		// Forward Path
		while (s[referanceCharIndex + operation.length()] == ' ') {
			s.replace(referanceCharIndex + operation.length(), 1, "");
		}

		// Backward Path
		if (!afterOnly)
			while (s[referanceCharIndex - 1] == ' ') {
				s.replace(referanceCharIndex - 1, 1, "");
			}

		/*string x = "0123456789";
		if (s[referanceCharIndex + operation.length() + 1] != x && s[referanceCharIndex - 1] != x) {
		throw("error parsing 1");
		}*/
	}
}
void removeSpacesWithRespectToNegative(string &s) { //Used when we don't need to remove the spaces before the negative if the number after it is in contact with it ..ex: [5 -3 - 4] will output [5 -3-4]
	string operation = "-";
	int iterationsNumber = countInString(s, operation);
	int npos = -1;
	bool afterOnly;

	for (int i = 0, referanceCharIndex = npos, currentCharIndex; i < iterationsNumber; i++) {
		referanceCharIndex = s.find("-", referanceCharIndex + 1);
		afterOnly = true;

		// Forward Path
		while (s[referanceCharIndex + operation.length()] == ' ') {
			afterOnly = false;
			s.replace(referanceCharIndex + operation.length(), 1, "");
		}

		// Backward Path
		if (!afterOnly)
			while (s[referanceCharIndex - 1] == ' ') {
				s.replace(referanceCharIndex - 1, 1, "");
			}
	}
}
void removeSpacesBetweenBrackets(string &s) {
	int iterationsNumber = countInString(s, "(");
	if (countInString(s, ")") != iterationsNumber) cout << "not valid defination." << endl;

	int npos = -1; string sTemp;
	for (int i = 0, referanceOfOpening, referanceOfClosing, currentCharIndex; i < iterationsNumber; i++) {
		for (int j = 0; j < s.length(); j++)
			if (s[j] == '(') referanceOfOpening = j;
			else if (s[j] == ')') {
				referanceOfClosing = j;
				break;
			}

			sTemp = s.substr(referanceOfOpening, referanceOfClosing - referanceOfOpening + 1);
			for (int j = 0; j < sTemp.length(); j++)
				if (sTemp[j] == ' ') {
					sTemp.replace(j, 1, "");
					j--;
				}
				else if (sTemp[j] == '(') sTemp.replace(j, 1, "<");
				else if (sTemp[j] == ')') sTemp.replace(j, 1, ">");
				s.replace(referanceOfOpening, referanceOfClosing - referanceOfOpening + 1, sTemp);
	}

	while (s.find('<') != npos) s.replace(s.find('<'), 1, "(");
	while (s.find('>') != npos) s.replace(s.find('>'), 1, ")");
}
void validateString(string s) {

	{ // checking for parentheses
		if (countInString(s, "(") != countInString(s, ")") || countInString(s, "[") != countInString(s, "]")) {
			if (countInString(s, "(") > countInString(s, ")") || countInString(s, "[") > countInString(s, "]")) throw("Did you forget to close some parentheses?");
			else throw("Did you forget to open some parentheses?");
		}
	}

	{ // checking for unknown variables
		int npos = -1;
		string operations[54] = { "asinh", "acosh", "atanh", "asin", "acos", "atan"
			, "sinh", "cosh", "tanh", "sin", "cos", "tan"
			, "acsch", "asech", "acoth", "acsc", "asec", "acot"
			, "csch", "sech", "coth", "csc", "sec", "cot"
			, "pow", "sqrt", "exp", "log", "log2", "log10"
			, "pai", "det", "transpose", "eig", "qr", "diag"
			, "isinf", "isfinite", "isfloat", "isnan", "ismatrix", "isempty"
			, "isequal", "ismember", "isinteger", "isreal", "length", "rot90"
			, "fliplr", "flipud", "horzcat", "vertcat", "repmat", "xor" };
		for (int i = 0; i < 54; i++)
			while (s.find(operations[i]) != npos) s.replace(s.find(operations[i]), operations[i].length(), "");
		if (s.find_first_of("abcdefghijklmnopqrstuvwxyz") != npos) throw ("Please define your variables before using.");
	}

	{ // checking for repeated operations
		int sLength = s.length(); bool prevIsOperation = false;
		for (int currentChar = 0; currentChar < sLength; currentChar++)
			if ((s[currentChar] == '+' || s[currentChar] == '-' || s[currentChar] == '*' || s[currentChar] == '/' || s[currentChar] == '\\' || s[currentChar] == '^' || s[currentChar] == '&' || s[currentChar] == '|') && prevIsOperation) throw("Error parsing operations");
			else if (s[currentChar] == '+' || s[currentChar] == '-' || s[currentChar] == '*' || s[currentChar] == '/' || s[currentChar] == '\\' || s[currentChar] == '^' || s[currentChar] == '&' || s[currentChar] == '|') prevIsOperation = true;
			else prevIsOperation = false;
	}

	{ // checking for operations without parameters
		char prevChar = '~'; int sLength = s.length(); bool prevIsOperation = false;
		string numbers = "0123456789";
		for (int currentChar = 0; currentChar < sLength; currentChar++)
			if ((currentChar == 0 && (s[currentChar] == '+' || s[currentChar] == '*' || s[currentChar] == '/' || s[currentChar] == '\\' || s[currentChar] == '^' || s[currentChar] == '&' || s[currentChar] == '|' || s[currentChar] == ')')) ||
				(currentChar == sLength - 1 && (s[currentChar] == '+' || s[currentChar] == '*' || s[currentChar] == '/' || s[currentChar] == '\\' || s[currentChar] == '^' || s[currentChar] == '&' || s[currentChar] == '|' || s[currentChar] == '(' || s[currentChar] == '-')) ||
				((s[currentChar] == '+' || s[currentChar] == '*' || s[currentChar] == '/' || s[currentChar] == '\\' || s[currentChar] == '^' || s[currentChar] == '&' || s[currentChar] == '|') && (s[currentChar + 1] != (numbers + "(") || s[currentChar - 1] != (numbers + ")"))) ||
				(s[currentChar] == '-' && s[currentChar + 1] != (numbers + "("))) throw("Error parsing operations, did you forget to complete the parameters?");
	}

}
string handleMatrix(string &s, const string varNames[100], const string varContent[100], const int& variablesNo) {
	replaceFromStackIntoString(s, varNames, varContent, variablesNo);
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	removeSpaces(s, "+");
	removeSpacesWithRespectToNegative(s);
	//removeSpaces(s, "-");
	removeSpaces(s, "*");
	removeSpaces(s, "/");
	removeSpaces(s, "\\");
	removeSpaces(s, "^");
	removeSpaces(s, "&");
	removeSpaces(s, "|");
	removeSpaces(s, "pow", true);
	removeSpaces(s, "sqrt", true);
	removeSpaces(s, "exp", true);
	removeSpaces(s, "log", true);
	removeSpaces(s, "log2", true);
	removeSpaces(s, "log10", true);
	removeSpaces(s, "sin", true);
	removeSpaces(s, "csc", true);
	removeSpaces(s, "cos", true);
	removeSpaces(s, "sec", true);
	removeSpaces(s, "tan", true);
	removeSpaces(s, "cot", true);
	removeSpaces(s, "sinh", true);
	removeSpaces(s, "csch", true);
	removeSpaces(s, "cosh", true);
	removeSpaces(s, "sech", true);
	removeSpaces(s, "tanh", true);
	removeSpaces(s, "coth", true);
	removeSpaces(s, "det", true);
	removeSpaces(s, "transpose", true);
	removeSpaces(s, "eig", true);
	removeSpaces(s, "qr", true);
	removeSpaces(s, "diag", true);
	removeSpaces(s, "isinf", true);
	removeSpaces(s, "isfinite", true);
	removeSpaces(s, "isfloat", true);
	removeSpaces(s, "isnan", true);
	removeSpaces(s, "ismatrix", true);
	removeSpaces(s, "isempty", true);
	removeSpaces(s, "isequal", true);
	removeSpaces(s, "ismember", true);
	removeSpaces(s, "isinteger", true);
	removeSpaces(s, "isreal", true);
	removeSpaces(s, "length", true);
	removeSpaces(s, "rot90", true);
	removeSpaces(s, "fliplr", true);
	removeSpaces(s, "flipud", true);
	removeSpaces(s, "horzcat", true);
	removeSpaces(s, "vertcat", true);
	removeSpaces(s, "repmat", true);
	removeSpaces(s, "xor", true);
	validateString(s);
	removeSpacesBetweenBrackets(s);

	return s;
}
string handleOperation(string s, const string varNames[100], const string varContent[100], const int& variablesNo) {
	replaceFromStackIntoString(s, varNames, varContent, variablesNo);
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	for (int i = 0; i < s.length(); i++)
		if (s[i] == ' ') {
			s.replace(i, 1, ""); i--;
		}
	validateString(s);

	return s;
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

	/*{ // Replacing all instances of variable names in the input with their respective values
	// cout << s << endl;
	for (int i = 0, x = -1; i < variablesNo; i++) {
	x = countInString(s, varNames[i]);
	while (0 < x--) s.replace(s.find_first_of(varNames[i]), varNames[i].length(), varContent[i]);
	}
	// cout << s << endl;
	}*/
	handleMatrix(s, varNames, varContent, variablesNo);

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
	CMatrix tempMat(NR, NC);
	for (int ir = 0; ir < NR; ir++)
		for (int ic = 0; ic < NC; ic++) {
			if (sTemp[ir][ic].length() == 0) throw ("Cannot construct such a matrix. Did you forget to enter some element? are you sure you tried to concatinate appropriate matrices?");
			sTemp[ir][ic] =sTemp[ir][ic]+';';
			//cout << sTemp[ir][ic]<<endl;
			doOperation(sTemp[ir][ic], varNames, varContent, variablesNo);
			tempMat.values[ir][ic] = atof(sTemp[ir][ic].c_str());
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
		//string n = handleOperation(info, varNames, varContent, variableNo);
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
					(s[string_index] == '-' &&s[string_index - 1] != '=' && (prevoperator_exist == false /*|| s[string_index - 1] == '=' */ || s[string_index - 1] == ')')) ||
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
	//cout << stack_index << endl;

	/*for (int i = 0; i < stack_index; i++)
	{
		cout << parameters[i] << "----->" << operations[i] << endl;
	}*/
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
	s = parameters[2];
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
		//cout << "done";
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
	else { s = parameters[0]; cout << parameters[0] << endl; }
}