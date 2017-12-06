#include <math.h>
#include "cmatrix.h"
#include "solve.h"

using namespace std;

// Hanaa 
/* Takes a string as input and returns a string output, Input may contain previous predefined variables and/or normal numbers */
string solve(string s, string varNames[100], string varContent[100], int& variablesNo) {
	int  counter1 = 0;
	string operation[21] = { "+","-","*","/","+=","-=","*=","/=","\\","\\=","&","|","~",".*","./",".\\",".^",".*=","./=",".^=",".\\=" };
	string operand; string operand2;
	std::size_t found = s.find('(');
	if (found != std::string::npos)
	{
		operand = s.substr(s.find('(') + 1, s.find(')') - s.find('(') - 1);;

	}


	else
	{

		for (int j = 0; j<21; j++)
		{
			std::size_t found1 = s.find(operation[j]);
			if (found1 != std::string::npos)
			{
				operand = s.substr(0, s.find(operation[j]));

				operand2 = s.substr(s.find(operation[j]) + operation[j].length(), s.length());
				int r = operation[j].length();
				// cout<<operand2<<"\n"<<r<<"\n";

			}
		}
	}

	for (int counter = 0; counter<variablesNo; counter++)
	{
		counter1 = 0;
		for (int k = 0; k<variablesNo; k++)
		{
			if (operand == varNames[counter])
			{
				string op = varContent[counter];
				if (op[0] == ('['))
				{
					counter1 = 1; break;
				}
			}
			if (operand2 == varNames[k])
			{
				string op1 = varContent[k];
				if (op1[0] == ('['))
				{
					counter1 = 1; break;
				}
			}
		}if (counter1 == 1) break;
	}

	if (counter1 == 1)
	{
		CMatrix x=solveCMatrix(s, varNames, varContent, variablesNo);
		return x.getOriginalString();
		//goto solveCMatrix();
		//cout<<"pass "<<s<<"to solve cmatrix"<<"\n";
		
	}
	else if (counter1 == 0) {
		double y = solveDouble(s, varNames, varContent, variablesNo);
		cout << "result from solveDouble" << y << endl;
		return to_string(y);
		//	goto solveDouble();
		//cout<<"pass"<<s<<"to solve double"<<"\n";
	}
	




}
  //  Marina
  /* Takes a string as input and returns a double output, Input may contain previous predefined variables and/or normal numbers */
double solveDouble(string s, string varNames[100], string varContent[100], int& variablesNo) 
{

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
			string operand1asnumber1 = s.substr(0, placeofspecial2);
			double operand1asnumbertodouble1 = atof(operand1asnumber1.c_str());
			string operand2asnumber2 = s.substr(placeofspecial2 + 1, s.length());
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
				//  cout << operand2asnumbertodouble2 << endl <<operand1asnumbertodouble1 << endl ;
				//-2+3
			{
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
				if (s.at(placeofspecial2) == '^')
				{
					return pow(operand1asnumbertodouble1, operand2asnumbertodouble2);
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
				if (s.at(placeofspecial2) == '^')
				{
					return pow(operand1asnumbertodouble1, contentofoperand2inDouble);
				}
			}
		}
		else
		{
			string checkvariable1invariablenames = s.substr(0, placeofspecial);
			string checkvariable2invariablenames = s.substr(placeofspecial + 1, s.length());

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
				else if (s.at(placeofspecial) == '^')
				{
					return pow(contentofoperand1inDouble, contentofoperand2inDouble);
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
				if (s.at(placeofspecial) == '^')
				{
					return pow(contentofoperand1inDouble, operand2asnumbertodouble);
				}
			}

			else if (operand1index == -1 && operand2index == -1)
			{
				//if the two inputs are numbers
				string operand1asnumber = s.substr(0, placeofspecial);
				double operand1asnumbertodouble = atof(operand1asnumber.c_str());
				string operand2asnumber = s.substr(placeofspecial + 1, s.length());
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
				else if (s.at(placeofspecial) == '^')
				{
					return pow(operand1asnumbertodouble, operand2asnumbertodouble);
				}
			}
			//2+B
			else if (operand1index == -1 && operand2index != -1)
			{
				string operand1asnumber = s.substr(0, placeofspecial);
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
				if (s.at(placeofspecial) == '^')
				{
					return pow(operand1asnumbertodouble, contentofoperand2inDouble);
				}
			}
		}
	}

}
