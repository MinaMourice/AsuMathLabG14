#include <math.h>
#include "cmatrix.h"
#include "solve.h"
#include <sstream>
using namespace std;

// Addition for linux
/*#include <sstream>
template <typename T> string to_string(const T& t) {
	ostringstream os;
	os << t;
	return os.str();
}
double stod(const string& s) {
	stringstream ss;
	ss << s;
	double x;
	ss >> x;
	return x;
}
template<class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& val) {
	while (first != last) {
		if (*first == val) return first;
		++first;
	}
	return last;
}*/
// <<
bool isDouble(string myString)
{
	istringstream iss(myString);
	double f;
	iss >> noskipws >> f; // noskipws considers leading whitespace invalid
						  // Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}
// Hanaa 
/* Takes a string as input and returns a string output, Input may contain previous predefined variables and/or normal numbers */
string solve(string s, string varNames[100], string varContent[100], int& variablesNo) {
	int  matFlag = 0; bool validOperand1 = 0, validOperand2 = 0; 
	string operation[14] = {".^",".+",".-",".*","./",".\\","^","*","/","\\","&","|","+","-" };
	int opIndex;
	string operand; string operand2;
	int found1 = s.find('(');
	if (found1 != std::string::npos)
	{
		operand = s.substr(s.find('(') + 1, s.find(')') - s.find('(') - 1);
		validOperand2 = 1;//as no having operand2 here
	}
	else if ((found1 = s.find('\'')) != std::string::npos)
	{
		operand = s.substr(0, found1);
		validOperand2 = 1;//as no having operand2 here
	}
	else
	{
		int indexbracket1 = s.find('[');
		int indexbracket2 = s.find(']');
		//cout << indexbracket2;
		
		for (int j = 0; j<14; j++)
		{
			if(indexbracket2 != std::string::npos&&indexbracket2!=s.length()-1)
				found1 = s.find(operation[j], indexbracket2+1);
			else if(indexbracket2 != std::string::npos&&indexbracket2 == s.length() - 1)
				found1 = s.rfind(operation[j], indexbracket1 );
			else
				found1 = s.find(operation[j],1);//to avoid first negative that may be available
			
			if (found1 != std::string::npos)
			{
				opIndex = j;
				break;
			}
		}
		if (found1 == 0) {
			operand = s.substr(1, s.length());
			validOperand2 = 1;//as no having operand2 here
		}
		else if (found1 != std::string::npos) {
			//cout << found1;
			//cout << operation[j] << endl;
			operand = s.substr(0, found1);
			operand2 = s.substr(found1 + operation[opIndex].length(), s.length());
			int r = operation[opIndex].length();
			// cout<<operand2<<"\n"<<r<<"\n";

		}
		else if (found1 == std::string::npos&&s[0] == '-') {
			found1 = 0;
			operand = s.substr(1, s.length());
			validOperand2 = 1;//as no having operand2 here
		}
	}
	
	 
	
	//cout << "s="<<s<< endl<<operand << endl << operand2 << endl;
	matFlag = 0; 
		if (operand[0] == '[') { 
			matFlag = 1; 
			validOperand1 = 1;
		}
		if (operand2[0] == '[') {
			matFlag = 1;
			validOperand2 = 1;
		}
			for (int k = 0; k < variablesNo; k++)
			{
				//cout << varNames[k]<<endl;
				if (operand == varNames[k])
				{
					validOperand1 = 1;
					string op = varContent[k];
					if (op[0] == ('['))
					{
						matFlag = 1;
					}
				}
				if (operand2 == varNames[k])
				{
					validOperand2 = 1;
					string op1 = varContent[k];
					if (op1[0] == ('['))
					{
						matFlag = 1;
					}
				}
			}
		if (!validOperand1)validOperand1 = isDouble(operand);
		if(!validOperand2)validOperand2 = isDouble(operand2);
		//cout << validOperand1 << "   " << validOperand2 << endl;
		/*if (!validOperand1 || !validOperand2)
			throw "unvalid operand";*/
	//cout << s<<endl;
	if (matFlag == 1)
	{
		//cout << "pass " << s << "to solve cmatrix" << "\n";
		CMatrix x = solveCMatrix(s, found1, varNames, varContent, variablesNo);
		//cout <<s<< "result from solveCMatrix" << x.getString() << endl;
		return x.getOriginalString();
		//goto solveCMatrix();
		

	}
	else if (matFlag == 0) {
		//cout << "pass" << s << "to solve double" << "\n";
		double y = solveDouble(s, varNames, varContent, variablesNo);
		//cout  << "result from solveDouble" << y << endl;
		return to_string(y);
		//	goto solveDouble();
		
	}





}
//  Marina
/* Takes a string as input and returns a double output, Input may contain previous predefined variables and/or normal numbers */
double solveDouble(string s, string varNames[100], string varContent[100], int& variablesNo)
{
	//cout << s;
	int placeofspecial = s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_.");

	if (s.at(placeofspecial) == '(')
	{

		//sin
		string only1operandfromvarnames = s.substr(placeofspecial + 1, s.find(')') - placeofspecial - 1);

		int only1operandindex = -1;
		for (int i = 0; i<variablesNo; i++)
		{
			if (only1operandfromvarnames == varNames[i])
			{
				only1operandindex = i;
			}
		}
		string TRIG = s.substr(0, placeofspecial);
		if (only1operandindex != -1)
		{
			string only1operandcontent = varContent[only1operandindex];
			double only1operandtodouble = atof(only1operandcontent.c_str());


			//only one operand

			if (TRIG == "sin")
			{
				return sin(only1operandtodouble);
			}
			else if (TRIG == "cos")
			{
				return cos(only1operandtodouble);
			}
			else  if (TRIG == "tan")
			{
				return tan(only1operandtodouble);
			}
			else if (TRIG == "sec")
			{
				return 1 / cos(only1operandtodouble);
			}
			else if (TRIG == "csc")
			{
				return 1 / sin(only1operandtodouble);
			}
			else if (TRIG == "cot")
			{
				return 1 / tan(only1operandtodouble);
			}
			else if (TRIG == "asin")
			{
				return asin(only1operandtodouble);
			}
			else if (TRIG == "acos")
			{
				return acos(only1operandtodouble);
			}
			else if (TRIG == "atan")
			{
				return atan(only1operandtodouble);
			}
			else if (TRIG == "acsc")
			{
				return asin(1.0 / only1operandtodouble);
			}
			else if (TRIG == "asec")
			{
				return acos(1.0 / only1operandtodouble);
			}
			else if (TRIG == "acot")
			{
				return atan(1.0 / only1operandtodouble);
			}
			else if (TRIG == "sinh")
			{
				return sinh(only1operandtodouble);
			}
			else if (TRIG == "cosh")
			{
				return cosh(only1operandtodouble);
			}
			else if (TRIG == "tanh")
			{
				return tanh(only1operandtodouble);
			}
			else if (TRIG == "sech")
			{
				return 2 / (exp(only1operandtodouble) + exp(-only1operandtodouble));
			}
			else if (TRIG == "csch")
			{
				return 2 / (exp(only1operandtodouble) - exp(-only1operandtodouble));
			}
			else if (TRIG == "coth")
			{
				return (exp(2 * only1operandtodouble) + 1) / (exp(2 * only1operandtodouble) - 1);
			}
			else if (TRIG == "asinh")
			{
				return asinh(only1operandtodouble);
			}
			else if (TRIG == "acosh")
			{
				return acosh(only1operandtodouble);
			}
			else if (TRIG == "atanh")
			{
				return atanh(only1operandtodouble);
			}
			else if (TRIG == "acsch")
			{
				return asinh(1.0 / only1operandtodouble);
			}
			else if (TRIG == "asech")
			{
				return acosh(1.0 / only1operandtodouble);
			}
			else if (TRIG == "acoth")
			{
				return atanh(1.0 / only1operandtodouble);
			}
			else if (TRIG == "exp")
			{
				return exp(only1operandtodouble);
			}
			else if (TRIG == "log")
			{
				return log(only1operandtodouble);
			}
			else if (TRIG == "log10")
			{
				return log10(only1operandtodouble);
			}
			else if (TRIG == "sqrt")
			{
				return sqrt(only1operandtodouble);
			}
			else if (TRIG == "abs")
			{
				return abs(only1operandtodouble);
			}
		}

		else

		{
			//only one as number 

			double  only1operandasnumbertodouble = atof(only1operandfromvarnames.c_str());


			if (TRIG == "sin")
			{
				return sin(only1operandasnumbertodouble);
			}
			else if (TRIG == "cos")
			{
				return cos(only1operandasnumbertodouble);
			}
			else if (TRIG == "tan")
			{
				return tan(only1operandasnumbertodouble);
			}
			else if (TRIG == "sec")
			{
				return 1 / cos(only1operandasnumbertodouble);
			}
			else if (TRIG == "csc")
			{
				return 1 / sin(only1operandasnumbertodouble);
			}
			else if (TRIG == "cot")
			{
				return 1 / tan(only1operandasnumbertodouble);
			}
			else if (TRIG == "asin")
			{
				return asin(only1operandasnumbertodouble);
			}
			else if (TRIG == "acos")
			{
				return acos(only1operandasnumbertodouble);
			}
			else if (TRIG == "atan")
			{
				return atan(only1operandasnumbertodouble);
			}
			else if (TRIG == "acsc")
			{
				return asin(1.0 / only1operandasnumbertodouble);
			}
			else if (TRIG == "asec")
			{
				return acos(1.0 / only1operandasnumbertodouble);
			}
			else if (TRIG == "acot")
			{
				return atan(1.0 / only1operandasnumbertodouble);
			}
			else if (TRIG == "sinh")
			{
				return sinh(only1operandasnumbertodouble);
			}
			else if (TRIG == "cosh")
			{
				return cosh(only1operandasnumbertodouble);
			}
			else if (TRIG == "tanh")
			{
				return tanh(only1operandasnumbertodouble);
			}
			else if (TRIG == "sech")
			{
				return 2 / (exp(only1operandasnumbertodouble) + exp(-only1operandasnumbertodouble));
			}
			else if (TRIG == "csch")
			{
				return 2 / (exp(only1operandasnumbertodouble) - exp(-only1operandasnumbertodouble));
			}
			else if (TRIG == "coth")
			{
				return (exp(2 * only1operandasnumbertodouble) + 1) / (exp(2 * only1operandasnumbertodouble) - 1);
			}
			else if (TRIG == "asinh")
			{
				return asinh(only1operandasnumbertodouble);
			}
			else if (TRIG == "acosh")
			{
				return acosh(only1operandasnumbertodouble);
			}
			else if (TRIG == "atanh")
			{
				return atanh(only1operandasnumbertodouble);
			}
			else if (TRIG == "acsch")
			{
				return asinh(1.0 / only1operandasnumbertodouble);
			}
			else if (TRIG == "asech")
			{
				return acosh(1.0 / only1operandasnumbertodouble);
			}
			else if (TRIG == "acoth")
			{
				return atanh(1.0 / only1operandasnumbertodouble);
			}
			else if (TRIG == "exp")
			{
				return exp(only1operandasnumbertodouble);
			}
			else if (TRIG == "log")
			{
				return log(only1operandasnumbertodouble);
			}
			else if (TRIG == "log10")
			{
				return log10(only1operandasnumbertodouble);
			}
			else if (TRIG == "sqrt")
			{
				return sqrt(only1operandasnumbertodouble);
			}
			else if (TRIG == "abs")
			{
				return abs(only1operandasnumbertodouble);
			}
		}
	}
	else
	{
		//plus
		if (placeofspecial == 0)
		{
			//-2+3
			int placeofspecial2 = s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_.", 1);
			if (placeofspecial2 == string::npos){ //case -2 or -a
				string operand = s.substr(placeofspecial+1,s.length());
				int operandindex = -1;
				for (int i = 0; i<variablesNo; i++)
				{
					if (operand == varNames[i])
					{
						operandindex = i; break;
					}
				}
				if (operandindex == -1) { //-2
					return -atof(operand.c_str());
				}
				else if (operandindex != -1) { //-a
					return -atof(varContent[operandindex].c_str());
				}
			}
			string operand1asnumber1 = s.substr(0, placeofspecial2);
			string operand2asnumber2 = s.substr(placeofspecial2 + 1, s.length());
			if (s[placeofspecial2 - 1] == '.') {
				operand1asnumber1 = s.substr(0, placeofspecial2-1);
				operand2asnumber2 = s.substr(placeofspecial2 + 1, s.length());
			}
			double operand1asnumbertodouble1 = atof(operand1asnumber1.c_str());
			double operand2asnumbertodouble2 = atof(operand2asnumber2.c_str());
			string checkvariable2invariablenames = operand2asnumber2;

			int operand2index = -1;
			for (int i = 0; i<variablesNo; i++)
			{
				if (checkvariable2invariablenames == varNames[i])
				{
					operand2index = i;
				}
			}

			if (operand2index == -1)
				
				//-2+3
			{
				//cout << operand2asnumbertodouble2 << endl << operand1asnumbertodouble1 << endl;
				if (s.at(placeofspecial2) == '+')
				{
					return operand1asnumbertodouble1 + operand2asnumbertodouble2;
				}
				if (s.at(placeofspecial2) == '-')
				{
					return operand1asnumbertodouble1 - operand2asnumbertodouble2;
				}
				if (s.at(placeofspecial2) == '*')
				{
					return operand1asnumbertodouble1 * operand2asnumbertodouble2;
				}
				if (s.at(placeofspecial2) == '/')
				{
					return operand1asnumbertodouble1 / operand2asnumbertodouble2;
				}
				if (s.at(placeofspecial2) == '\\')
				{
					return  operand2asnumbertodouble2 / operand1asnumbertodouble1;
				}
				if (s.at(placeofspecial2) == '^')
				{
					return pow(operand1asnumbertodouble1, operand2asnumbertodouble2);
				}
				if (s.at(placeofspecial2) == '&')
				{
					return int(operand1asnumbertodouble1)&int(operand2asnumbertodouble2);
				}
				if (s.at(placeofspecial2) == '|')
				{
					return int(operand1asnumbertodouble1)|int(operand2asnumbertodouble2);
				}
			}
			else if (operand2index != -1)
			{
				//-2+B
				string operand2content = varContent[operand2index];
				double contentofoperand2inDouble = atof(operand2content.c_str());

				if (s.at(placeofspecial2) == '+')
				{
					return operand1asnumbertodouble1 + contentofoperand2inDouble;
				}
				if (s.at(placeofspecial2) == '-')
				{
					return operand1asnumbertodouble1 - contentofoperand2inDouble;
				}
				if (s.at(placeofspecial2) == '*')
				{
					return operand1asnumbertodouble1 * contentofoperand2inDouble;
				}
				if (s.at(placeofspecial2) == '/')
				{
					return operand1asnumbertodouble1 / contentofoperand2inDouble;
				}
				if (s.at(placeofspecial2) == '\\')
				{
					return contentofoperand2inDouble / operand1asnumbertodouble1;
				}
				if (s.at(placeofspecial2) == '^')
				{
					return pow(operand1asnumbertodouble1, contentofoperand2inDouble);
				}
				if (s.at(placeofspecial2) == '&')
				{
					return int(operand1asnumbertodouble1)&int(contentofoperand2inDouble);
				}
				if (s.at(placeofspecial2) == '|')
				{
					return int(operand1asnumbertodouble1)|int(contentofoperand2inDouble);
				}
			}
		}
		else
		{
			string checkvariable1invariablenames = s.substr(0, placeofspecial);
			string checkvariable2invariablenames = s.substr(placeofspecial + 1, s.length());
			if (s[placeofspecial - 1] == '.') {
				checkvariable1invariablenames = s.substr(0, placeofspecial - 1);
				checkvariable2invariablenames = s.substr(placeofspecial + 1, s.length());
			}
			int operand1index = -1;
			int operand2index = -1;
			for (int i = 0; i<variablesNo; i++)
			{
				if (checkvariable1invariablenames == varNames[i])
				{
					operand1index = i;
				}
				if (checkvariable2invariablenames == varNames[i])
				{
					operand2index = i;
				}
			}
			//if the operation between two variables 
			if (operand1index != -1 && operand2index != -1)
			{
				string operand1content = varContent[operand1index];
				double contentofoperand1inDouble = atof(operand1content.c_str());
				string operand2content = varContent[operand2index];
				double contentofoperand2inDouble = atof(operand2content.c_str());
				if (s.at(placeofspecial) == '+')
				{
					return contentofoperand1inDouble + contentofoperand2inDouble;
				}
				else if (s.at(placeofspecial) == '-')
				{
					return contentofoperand1inDouble - contentofoperand2inDouble;
				}
				else if (s.at(placeofspecial) == '*')
				{
					return contentofoperand1inDouble * contentofoperand2inDouble;
				}
				else if (s.at(placeofspecial) == '/')
				{
					return contentofoperand1inDouble / contentofoperand2inDouble;
				}
				else if (s.at(placeofspecial) == '\\')
				{
					return contentofoperand2inDouble / contentofoperand1inDouble;
				}
				else if (s.at(placeofspecial) == '^')
				{
					return pow(contentofoperand1inDouble, contentofoperand2inDouble);
				}
				if (s.at(placeofspecial) == '&')
				{
					return int(contentofoperand1inDouble)&int(contentofoperand2inDouble);
				}
				if (s.at(placeofspecial) == '|')
				{
					return int(contentofoperand1inDouble)|int(contentofoperand2inDouble);
				}
			}
			//B+2
			else if (operand1index != -1 && operand2index == -1)
			{
				string operand1content = varContent[operand1index];
				double contentofoperand1inDouble = atof(operand1content.c_str());
				string operand2asnumber = s.substr(placeofspecial + 1, s.length());
				double operand2asnumbertodouble = atof(operand2asnumber.c_str());

				if (s.at(placeofspecial) == '+')
				{
					return contentofoperand1inDouble + operand2asnumbertodouble;
				}
				if (s.at(placeofspecial) == '-')
				{
					return contentofoperand1inDouble - operand2asnumbertodouble;
				}
				if (s.at(placeofspecial) == '*')
				{
					return contentofoperand1inDouble * operand2asnumbertodouble;
				}
				if (s.at(placeofspecial) == '/')
				{
					return contentofoperand1inDouble / operand2asnumbertodouble;
				}
				if (s.at(placeofspecial) == '\\')
				{
					return operand2asnumbertodouble / contentofoperand1inDouble;
				}
				if (s.at(placeofspecial) == '^')
				{
					return pow(contentofoperand1inDouble, operand2asnumbertodouble);
				}
				if (s.at(placeofspecial) == '&')
				{
					return int(contentofoperand1inDouble)&int(operand2asnumbertodouble);
				}
				if (s.at(placeofspecial) == '|')
				{
					return int(contentofoperand1inDouble) | int(operand2asnumbertodouble);
				}
			}

			else if (operand1index == -1 && operand2index == -1)
			{
				//if the two inputs are numbers
				string operand1asnumber = s.substr(0, placeofspecial);
				string operand2asnumber = s.substr(placeofspecial + 1, s.length());
				if (s[placeofspecial - 1] == '.') {
					operand1asnumber = s.substr(0, placeofspecial - 1);
					operand2asnumber = s.substr(placeofspecial + 1, s.length());
				}
				double operand1asnumbertodouble = atof(operand1asnumber.c_str());
				double operand2asnumbertodouble = atof(operand2asnumber.c_str());
				if (s.at(placeofspecial) == '+')
				{
					return operand1asnumbertodouble + operand2asnumbertodouble;
				}
				else if (s.at(placeofspecial) == '-')
				{
					return operand1asnumbertodouble - operand2asnumbertodouble;
				}
				else if (s.at(placeofspecial) == '*')
				{
					return operand1asnumbertodouble * operand2asnumbertodouble;
				}
				else if (s.at(placeofspecial) == '/')
				{
					return operand1asnumbertodouble / operand2asnumbertodouble;
				}
				else if (s.at(placeofspecial) == '\\')
				{
					return operand2asnumbertodouble / operand1asnumbertodouble;
				}
				else if (s.at(placeofspecial) == '^')
				{
					return pow(operand1asnumbertodouble, operand2asnumbertodouble);
				}
				if (s.at(placeofspecial) == '&')
				{
					return int(operand1asnumbertodouble)&int(operand2asnumbertodouble);
				}
				if (s.at(placeofspecial) == '|')
				{
					return int(operand1asnumbertodouble) | int(operand2asnumbertodouble);
				}
			}
			//2+B
			else if (operand1index == -1 && operand2index != -1)
			{
				string operand1asnumber = s.substr(0, placeofspecial);
				if (s[placeofspecial - 1] == '.') {
					operand1asnumber = s.substr(0, placeofspecial - 1);
				}
				double operand1asnumbertodouble = atof(operand1asnumber.c_str());
				string operand2content = varContent[operand2index];
				double contentofoperand2inDouble = atof(operand2content.c_str());
				if (s.at(placeofspecial) == '+')
				{
					return operand1asnumbertodouble + contentofoperand2inDouble;
				}
				if (s.at(placeofspecial) == '-')
				{
					return operand1asnumbertodouble - contentofoperand2inDouble;
				}
				if (s.at(placeofspecial) == '*')
				{
					return operand1asnumbertodouble * contentofoperand2inDouble;
				}
				if (s.at(placeofspecial) == '/')
				{
					return operand1asnumbertodouble / contentofoperand2inDouble;
				}
				if (s.at(placeofspecial) == '//')
				{
					return contentofoperand2inDouble / operand1asnumbertodouble;
				}
				if (s.at(placeofspecial) == '^')
				{
					return pow(operand1asnumbertodouble, contentofoperand2inDouble);
				}
				if (s.at(placeofspecial) == '&')
				{
					return int(operand1asnumbertodouble)&int(contentofoperand2inDouble);
				}
				if (s.at(placeofspecial) == '|')
				{
					return int(operand1asnumbertodouble) | int(contentofoperand2inDouble);
				}
			}
		}
	}

}
CMatrix solveCMatrix(string s,int placeOfOPerator, string varNames[100], string varContent[100], int& variablesNo)
{
	string operand1, operand2;  CMatrix valueOfOperand1, valueOfOperand2;  string numberString; int operand1index=100, operand2index=100;
	double op1const = 1, op2const = 1;
	//string operators = "+-\\*/^";
	/*int placeOfOPerator = s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_[]; ", 1);
	while (s[placeOfOPerator] == '.' && (s[placeOfOPerator + 1] != '+' || s[placeOfOPerator + 1] != '-' || s[placeOfOPerator + 1] != '*' || s[placeOfOPerator + 1] != '/' || s[placeOfOPerator + 1] != '\\' || s[placeOfOPerator + 1] != '^')) {
		placeOfOPerator = s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_[]; ", placeOfOPerator+1);
	}*/
	
	if (placeOfOPerator == 0) {
		operand1 = s.substr(1, s.length());
		operand1index = distance(varNames, find(varNames, varNames + 100, operand1));
		if (operand1index != 100) {
			valueOfOperand1 = CMatrix(varContent[operand1index]);
		}
		else {
			valueOfOperand1 = CMatrix(operand1);
		}
		return -valueOfOperand1;
	}
	//cout << s[placeOfOPerator];
	if (placeOfOPerator != std::string::npos)
	{
		
		//if (s.substr(placeOfOPerator + 1, 1) == "-"&&s.substr(placeOfOPerator, 2) != ".-") { op2const = -1; s.erase(placeOfOPerator + 1, 1); }
		//if (s.substr(placeOfOPerator + 1, 1) == "-"&&s.substr(placeOfOPerator, 2) == ".-") { op2const = 1; }
		//if (s.substr(placeOfOPerator + 2, 1) == "-") { op2const = -1; s.erase(placeOfOPerator + 2, 1); }
		if (s.substr(0, 1) == "-") { op1const = -1; s.erase(0, 1); placeOfOPerator--; }
		//placeOfOPerator = s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_[]; ", 1);
		/*while (s[placeOfOPerator] == '.' && (s[placeOfOPerator + 1] != '+' || s[placeOfOPerator + 1] != '-' || s[placeOfOPerator + 1] != '*' || s[placeOfOPerator + 1] != '/' || s[placeOfOPerator + 1] != '\\' || s[placeOfOPerator + 1] != '^')) {
			placeOfOPerator = s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_[]; ", placeOfOPerator + 1);
		}*/
		//cout << "op is"<<s[placeOfOPerator]<<endl;
		int placeOfSubscriptionOperator1 = s.find('[',0);
		int placeOfSubscriptionOperator2 = s.rfind('[',s.length()-1);
		//cout << placeOfSubscriptionOperator1 << placeOfSubscriptionOperator2;
		string matrixContent1, matrixContent2;
		if (placeOfSubscriptionOperator1 != std::string::npos)
			matrixContent1 = s.substr(placeOfSubscriptionOperator1, s.find(']',0) - placeOfSubscriptionOperator1 + 1);
		if (placeOfSubscriptionOperator2 != std::string::npos)
			matrixContent2 = s.substr(placeOfSubscriptionOperator2, s.find(']', placeOfOPerator) - placeOfSubscriptionOperator2 + 1);
		//cout << matrixContent1 <<endl<< matrixContent2<<endl;
		//cout << valueOfOperand1.getString() << valueOfOperand2.getString() << endl;
		if (s[placeOfOPerator] == 43 || s[placeOfOPerator] == 45 || s[placeOfOPerator] == 42 || s[placeOfOPerator] == 47 || s[placeOfOPerator] == 92 || s[placeOfOPerator] == 38 || s[placeOfOPerator] == 124||s[placeOfOPerator] == '^'|| s[placeOfOPerator] == '\'')
		{
			int findDouble = s.find_first_of("0123456789");
			{
				int endDouble = s.find_first_not_of("0123456789", findDouble);
				if (findDouble != std::string::npos)
				{
					if (findDouble<placeOfOPerator)
					{
						if (s[placeOfOPerator] != '\'') {// as ' has one operand
							operand2index = distance(varNames, find(varNames, varNames + 100, s.substr(placeOfOPerator + 1, s.length())));
						}
						if (operand2index != 100) {
							valueOfOperand2 = CMatrix(varContent[operand2index]);
							valueOfOperand2 = valueOfOperand2.dotMul(CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op2const));
							
						}
						numberString = s.substr(findDouble, endDouble != std::string::npos ? endDouble - findDouble : endDouble);
						valueOfOperand1 = CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op1const * stod(numberString));
					}

					else
					{
						operand1index = distance(varNames, find(varNames, varNames + 100, s.substr(0, placeOfOPerator)));
						if (operand1index != 100) {
							valueOfOperand1 = CMatrix(varContent[operand1index]);
							valueOfOperand1 = valueOfOperand1.dotMul(CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op1const));
						}
						if (s[placeOfOPerator] != '\'') {// as ' has one operand
							numberString = s.substr(findDouble, endDouble != std::string::npos ? endDouble - findDouble : endDouble);
							valueOfOperand2 = CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op2const * stod(numberString));
						}
					}

				}

				else
				{
					operand1index = distance(varNames, find(varNames, varNames + 100, s.substr(0, placeOfOPerator)));
					if (s[placeOfOPerator] != '\'') {// as ' has one operand
						operand2index = distance(varNames, find(varNames, varNames + 100, s.substr(placeOfOPerator + 1, s.length())));
					}
					//cout << operand1index << operand2index;
					int foundMatrix1=-1, foundMatrix2=-1;
					if (operand1index != 100) {
						 foundMatrix1 = varContent[operand1index].find("[");
					}
					if (operand2index != 100) {
						 foundMatrix2 = varContent[operand2index].find("[");
					}
					if (foundMatrix2 == std::string::npos)
					{
						if (operand1index != 100) {
							valueOfOperand1 = CMatrix(varContent[operand1index]);
							valueOfOperand1 = valueOfOperand1.dotMul(CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op1const));
						}
						if (operand2index != 100) {
							valueOfOperand2 = CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, stod(varContent[operand2index]));
						}
					}
					else if (foundMatrix1 == std::string::npos)
					{
						if (operand2index != 100) {
							valueOfOperand2 = CMatrix(varContent[operand2index]);
							valueOfOperand2 = valueOfOperand2.dotMul(CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op2const));
						}
						if (operand1index != 100) {
							valueOfOperand1 = CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, stod(varContent[operand1index]));
						}
					}
					else
					{
						if (operand1index != 100) {
							valueOfOperand1 = CMatrix(varContent[operand1index]);
							valueOfOperand1 = valueOfOperand1.dotMul(CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op1const));
						}
						if (operand2index != 100) {
							valueOfOperand2 = CMatrix(varContent[operand2index]);
							valueOfOperand2 = valueOfOperand2.dotMul(CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op2const));
						}
					}

				}
			}//cout << valueOfOperand1.getString() << valueOfOperand2.getString() << endl;
			if (placeOfSubscriptionOperator1 != std::string::npos&&placeOfOPerator > placeOfSubscriptionOperator1&&placeOfSubscriptionOperator2 != std::string::npos&&placeOfOPerator < placeOfSubscriptionOperator2)//first is [1 2 3 4] second is [1 2 3 4]
			{
				valueOfOperand1 = CMatrix(matrixContent1);
				if (op1const == -1) { valueOfOperand1 = -valueOfOperand1; }
				if (s[placeOfOPerator] != '\'') {// as ' has one operand
					valueOfOperand2 = CMatrix(matrixContent2);
				}
			}
			else if (placeOfSubscriptionOperator1 != std::string::npos&&placeOfOPerator > placeOfSubscriptionOperator1)//first is[1 2 3 4]
			{
	
				valueOfOperand1 = CMatrix(matrixContent1);
				if (op1const == -1) { valueOfOperand1 = -valueOfOperand1; }
				if (s[placeOfOPerator] != '\'') {// as ' has one operand
					operand2 = s.substr(placeOfOPerator + 1);
					operand2index = distance(varNames, find(varNames, varNames + 100, operand2));
					if (operand2index != 100) {//second is variable
						if (varContent[operand2index].find("[") != string::npos) {//matrix variable
							valueOfOperand2 = CMatrix(varContent[operand2index]);
						}
						else {//normal variable
							valueOfOperand2 = CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, stod(varContent[operand2index]));

						}
					}
					else {// second is a double number
						valueOfOperand2 = CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, stod(operand2));
					}
				}
			}
			else if (placeOfSubscriptionOperator2 != std::string::npos&&placeOfOPerator < placeOfSubscriptionOperator2)//second is [1 2 3 4]
			{
				if (s[placeOfOPerator] != '\'') {// as ' has one operand
					valueOfOperand2 = CMatrix(matrixContent2);
				}
				operand1 = s.substr(0,placeOfOPerator);
				operand1index = distance(varNames, find(varNames, varNames + 100, operand1));
				if (operand1index != 100) {//first is variable
					if (varContent[operand1index].find("[") != string::npos) {//matrix variable
						valueOfOperand1 = CMatrix(varContent[operand1index]);
					}
					else {//normal variable
						valueOfOperand1 = CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, stod(varContent[operand1index]));
					}
				}
				else {// first is a double number
					valueOfOperand1 = CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, stod(operand1));
				}
				if (op1const == -1) { valueOfOperand1 = -valueOfOperand1; }
			}
			//cout << valueOfOperand1.getString() << valueOfOperand2.getString() << endl;
			if (s[placeOfOPerator] == 43)        return (valueOfOperand1 + valueOfOperand2);
			else if (s[placeOfOPerator] == 45)   return valueOfOperand1 - valueOfOperand2;
			else if (s[placeOfOPerator] == 42)   return valueOfOperand1 * valueOfOperand2;
			else if (s[placeOfOPerator] == 47)   return valueOfOperand1 / valueOfOperand2;
			else if (s[placeOfOPerator] == 92)   return valueOfOperand1.lDiv(valueOfOperand2);
			else if (s[placeOfOPerator] == '^')  return pow(valueOfOperand1,stod(s.substr(placeOfOPerator+1)));
			else if(s[placeOfOPerator]==38)   return valueOfOperand1 & valueOfOperand2 ;
			else if(s[placeOfOPerator]==124)  return valueOfOperand1 | valueOfOperand2 ;
			else if (s[placeOfOPerator] =='\'')  return valueOfOperand1.getTranspose();

		}

		else if ((s[placeOfOPerator]) == 40)                        // (
		{
			int p = s.find(")");

			if (s.substr(0, placeOfOPerator) != "pow")
			{
				operand2index = distance(varNames, find(varNames, varNames + 100, s.substr(placeOfOPerator + 1, p - placeOfOPerator - 1)));
				if (operand2index != 100) {
					valueOfOperand2 = CMatrix(varContent[operand2index]);
					valueOfOperand2 = valueOfOperand2.dotMul(CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op2const));
				}
			}
			if (placeOfSubscriptionOperator2 != std::string::npos&&placeOfOPerator<placeOfSubscriptionOperator2)
				valueOfOperand2 = CMatrix(matrixContent2);
			if (s.substr(0, placeOfOPerator) == "sin")          return sin(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "cos")     return cos(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "tan")     return tan(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "csc")     return csc(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "sec")     return sec(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "cot")     return cot(valueOfOperand2);

			else if (s.substr(0, placeOfOPerator) == "sinh")	 return sinh(valueOfOperand2); 
			else if (s.substr(0, placeOfOPerator) == "cosh")     return cosh(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "tanh")     return tanh(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "csch")     return csch(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "sech")     return sech(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "coth")     return coth(valueOfOperand2);

			else if (s.substr(0, placeOfOPerator) == "asin")    return asin(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "acos")    return acos(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "atan")    return atan(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "acsc")    return acsc(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "asec")    return asec(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "acot")    return acot(valueOfOperand2);

			else if (s.substr(0, placeOfOPerator) == "asinh")    return asinh(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "acosh")    return acosh(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "atanh")    return atanh(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "acsch")    return acsch(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "asech")    return asech(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "acoth")    return acoth(valueOfOperand2);

			else if(s.substr(0,placeOfOPerator)=="sqrt")		return valueOfOperand2.dotPow(0.5);
			else if (s.substr(0, placeOfOPerator) == "exp")     return exp(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "log")     return log(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "log10")   return log10(valueOfOperand2);

			/*else if(s.substr(0,placeOfOPerator)=="pow")
			{
			int findDouble = s.find_first_of("0123456789");
			if (findDouble != std::string::npos)
			{
			int endDouble = s.find_first_not_of("0123456789", findDouble);
			valueOfOperand2 = CMatrix (s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) ) ;
			}
			operand1index = distance( varNames, find( varNames , varNames + 100 , s.substr(0,placeOfOPerator-3) ) );
			valueOfOperand1 = CMatrix (varContent[operand1index]);
			return valueOfOperand1 . pow ( valueOfOperand2 ) ;
			}*/
		}

		else if (s[placeOfOPerator] == 46)                      // .
		{
			int findDouble = s.find_first_of("0123456789");
			{
				int endDouble = s.find_first_not_of("0123456789", findDouble);
				if (findDouble != std::string::npos)
				{
					if (findDouble<placeOfOPerator)
					{
						operand2index = distance(varNames, find(varNames, varNames + 100, s.substr(placeOfOPerator + 2, s.length())));
						if (operand2index != 100) {
							valueOfOperand2 = CMatrix(varContent[operand2index]);
							valueOfOperand2 = valueOfOperand2.dotMul(CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op2const));
						}
						numberString = s.substr(findDouble, endDouble != std::string::npos ? endDouble - findDouble : endDouble);
						valueOfOperand1 = CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op1const * stod(numberString));
					}

					else
					{
						
						operand1index = distance(varNames, find(varNames, varNames + 100, s.substr(0, placeOfOPerator)));
						if (operand1index != 100) {
								valueOfOperand1 = CMatrix(varContent[operand1index]);
								valueOfOperand1 = valueOfOperand1.dotMul(CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op1const));
						}
						numberString = s.substr(findDouble, endDouble != std::string::npos ? endDouble - findDouble : endDouble);
						valueOfOperand2 = CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op2const * stod(numberString));
					}

				}

				else
				{
					operand1index = distance(varNames, find(varNames, varNames + 100, s.substr(0, placeOfOPerator)));
					operand2index = distance(varNames, find(varNames, varNames + 100, s.substr(placeOfOPerator + 2, s.length())));
					int foundMatrix1=-1, foundMatrix2=-1;
					if (operand1index != 100) {
						foundMatrix1 = varContent[operand1index].find("[");
					}
					if (operand2index != 100) {
						foundMatrix2 = varContent[operand2index].find("[");
					}
					if (foundMatrix2 == std::string::npos)
					{
						if (operand1index != 100) {
							valueOfOperand1 = CMatrix(varContent[operand1index]);
							valueOfOperand1 = valueOfOperand1.dotMul(CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op1const));
						}
						if (operand2index != 100) {
							valueOfOperand2 = CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, stod(varContent[operand2index]));
						}
					}
					else if (foundMatrix1 == std::string::npos)
					{
						if (operand2index != 100) {
							valueOfOperand2 = CMatrix(varContent[operand2index]);
							valueOfOperand2 = valueOfOperand2.dotMul(CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op2const));
						}
						if (operand1index != 100) {
							valueOfOperand1 = CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, stod(varContent[operand1index]));
						}
					}
					else
					{
						if (operand1index != 100) {
							valueOfOperand1 = CMatrix(varContent[operand1index]);
							valueOfOperand1 = valueOfOperand1.dotMul(CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op1const));
						}
						if (operand2index != 100) {
							valueOfOperand2 = CMatrix(varContent[operand2index]);
							valueOfOperand2 = valueOfOperand2.dotMul(CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op2const));
						}
					}

				}
			}
			if (placeOfSubscriptionOperator1 != std::string::npos&&placeOfOPerator > placeOfSubscriptionOperator1&&placeOfSubscriptionOperator2 != std::string::npos&&placeOfOPerator < placeOfSubscriptionOperator2)//first is [1 2 3 4] second is [1 2 3 4]
			{
				valueOfOperand1 = CMatrix(matrixContent1);
				if (op1const == -1) { valueOfOperand1 = -valueOfOperand1; }
				valueOfOperand2 = CMatrix(matrixContent2);
			}
			else if (placeOfSubscriptionOperator1 != std::string::npos&&placeOfOPerator > placeOfSubscriptionOperator1)//first is[1 2 3 4]
			{

				valueOfOperand1 = CMatrix(matrixContent1);
				if (op1const == -1) { valueOfOperand1 = -valueOfOperand1; }
				operand2 = s.substr(placeOfOPerator + 2);
				operand2index = distance(varNames, find(varNames, varNames + 100, operand2));
				if (operand2index != 100) {//second is variable
					if (varContent[operand2index].find("[") != string::npos) {//matrix variable
						valueOfOperand2 = CMatrix(varContent[operand2index]);
					}
					else {//normal variable
						valueOfOperand2 = CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, stod(varContent[operand2index]));

					}
				}
				else {// second is a double number
					valueOfOperand2 = CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, stod(operand2));
				}
			}
			else if (placeOfSubscriptionOperator2 != std::string::npos&&placeOfOPerator < placeOfSubscriptionOperator2)//second is [1 2 3 4]
			{
				valueOfOperand2 = CMatrix(matrixContent2);
				operand1 = s.substr(0,placeOfOPerator );
				operand1index = distance(varNames, find(varNames, varNames + 100, operand1));
				if (operand1index != 100) {//first is variable
					if (varContent[operand1index].find("[") != string::npos) {//matrix variable
						valueOfOperand1 = CMatrix(varContent[operand1index]);
					}
					else {//normal variable
						valueOfOperand1 = CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, stod(varContent[operand1index]));
					}
				}
				else {// first is a double number
					valueOfOperand1 = CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, stod(operand1));
				}
				if (op1const == -1) { valueOfOperand1 = -valueOfOperand1; }
			}
			//cout << valueOfOperand1.getString() << valueOfOperand1.getString();
			if (s[placeOfOPerator + 1] == 43)        return (valueOfOperand1 + valueOfOperand2);
			else if (s[placeOfOPerator + 1] == 45)   return valueOfOperand1 - valueOfOperand2;
			else if (s[placeOfOPerator + 1] == 42)        return valueOfOperand1.dotMul(valueOfOperand2);       // **
			else if (s[placeOfOPerator + 1] == 47)   return valueOfOperand1.dotDiv(valueOfOperand2);       // **
			else if (s[placeOfOPerator + 1] == 93)   return valueOfOperand1.dotLDiv(valueOfOperand2);       // **
			else if (s[placeOfOPerator + 1] == '^')   return valueOfOperand1.dotPow(stod(s.substr(placeOfOPerator + 2)));
			/*else if (s.substr(placeOfOPerator + 1, placeOfOPerator + 3) == "pow(" || s[placeOfOPerator] == 94)
			{
				int findDouble = s.find_first_of("0123456789");
				if (findDouble != std::string::npos)
				{
					int endDouble = s.find_first_not_of("0123456789", findDouble);
					return valueOfOperand1.dotPow(stod(s.substr(findDouble, endDouble != std::string::npos ? endDouble - findDouble : endDouble)));                                  //      **
				}
			}*/


		}





	}

}










