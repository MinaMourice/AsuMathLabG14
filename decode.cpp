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
	
	errors_handler(info);
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


void defMat(string s, string varNames[100], string varContent[100], int& variablesNo)
{

	string array[100], text, token, replace, value;
	size_t Equal_pos, found_var, found_par1, diff, found_par2, semi_colon, semi_colon_2, semi_colon_no, colon, token2_pos, final_semi_colon;
	int flag = 0, c = 0, replaced_pos, Equal_no;
	string name;

	//sort(varNames, varNames + variablesNo - 1);
	Equal_no = count(s.begin(), s.end(), '=');


	//cout << "variablesNo :" << variablesNo << endl;
	final_semi_colon = s.find_first_of(";", s.find_last_of("]"));
	if (final_semi_colon != string::npos)s.erase(final_semi_colon, 1);
	//cout << s << endl;

	// Replace The Variable in all matrix By it's Value

	for (int i = variablesNo; i >= 0; i--)
	{
		for (int count = variablesNo; count >= 0; count--)
		{
			found_var = varContent[i].find(varNames[count]);
			//cout << found_var << endl;
			while (found_var != string::npos)
			{
				//cout << "first 'var' found at: " << found_var << '\n';
				varContent[i].replace(found_var, varNames[count].length(), varContent[count]);
				//cout << varContent[i] << endl;
				found_var = varContent[i].find(varNames[i], found_var + 1);
			}
		}
	}
	/*
	for (int i = 0; i < variablesNo; i++)
	{
	istringstream iss4(varContent[i]);
	cout << "start" << endl;
	while (getline(iss4, token, ' '))
	{
	cout << token << endl;
	if (!isFloat(token))
	{
	token2_pos = varContent[i].find(token);
	for (int i = variablesNo; i >= 0; i--)
	{
	if (token.compare(varnames[i]) != 0)
	{
	value = varContent[i];
	cout << value << endl;
	}
	}
	varContent[i].replace(token2_pos, token.length(), value);
	}
	}
	cout << "end" << endl;

	}*/
	Equal_pos = s.find_first_of('=');
	// Replace The Variable in s By it's Value
	for (int i = variablesNo; i >= 0; i--)
	{
		found_var = s.find(varNames[i], Equal_pos);
		while (found_var != string::npos)
		{
			//cout << "first 'var' found at: " << found_var << '\n';
			s.replace(found_var, varNames[i].length(), varContent[i]);
			found_var = s.find(varNames[i], found_var + 1);
		}
	}
	//	cout << "first: " << s << endl;
	//more than one variable have the same content a=b=...
	for (int b = 0; b < Equal_no; b++)
	{
		Equal_pos = s.find_first_of('=');
		varNames[variablesNo] = s.substr(0, Equal_pos);
		//remove_if(varNames[variablesNo].begin(), varNames[variablesNo].end(), isspace);
		varNames[variablesNo].erase(remove_if(varNames[variablesNo].begin(), varNames[variablesNo].end(), isspace), varNames[variablesNo].end());
		name = varNames[variablesNo];

		s.erase(0, Equal_pos + 1);
		variablesNo++;
		//string::iterator end_pos = remove(varNames[variablesNo].begin(), varNames[variablesNo].end(), ' ');
		//varNames[variablesNo].erase(end_pos, varNames[variablesNo].end());
		//cout <<varNames[variablesNo];
	}
	//cout << "variablesNo :" << variablesNo << endl;
	//cout << s << endl;

	// parsing '[' to ']'
	if (s.find_first_of("[") != string::npos&&s.find_last_of("]") != string::npos)
	{
		s.erase(s.find_first_of("["), 1);
		s.erase(s.find_last_of("]"), 1);
		//cout << "erase :" << s << endl;
		/*istringstream iss3(s);
		//cout << "start" << endl;
		while (getline(iss3, token, ' '))
		{
		cout << token << endl;
		if (!isFloat(token))
		{
		token2_pos = s.find(token);
		for (int i = variablesNo; i >= 0; i--)
		{
		if (token.compare(varnames[i]) != 0)
		{
		value = varContent[i];
		cout << value << endl;
		}
		}
		s.replace(token2_pos, token.length(), value);
		}
		}
		cout << "end" << endl;*/
		//cout << s << endl;


		found_par1 = s.find_first_of("[");
		found_par2 = s.find_first_of("]");

		//cout << s << endl;
		while (found_par1 != string::npos&& found_par2 != string::npos)
		{

			//cout<<found_par1<<" "<<found_par2<<endl;

			semi_colon = s.find(";", found_par1);
			colon = s.find_first_of(",", found_par1);
			//cout<<semi_colon<<endl;
			//if there is semi-colon between the two braces []
			if (found_par1 < semi_colon&&semi_colon < found_par2)
			{
				//	cout<<count_1<<endl;
				//	if(count_1==0)
				if (flag == 0) {
					replaced_pos = found_par1; flag = 1;
				}
				text = s.substr(found_par1 + 1, found_par2 - found_par1 - 1);
				istringstream iss(text);
				//cout<<text<<endl;
				semi_colon_no = count(s.begin() + found_par1, s.begin() + found_par2, ';');
				//	cout<<semi_colon_no<<endl;
				//save value inside [] in an array
				for (size_t i = 0; i <= semi_colon_no; i++)
				{
					getline(iss, token, ';');
					array[c] += " " + token;
					c++;

				}

				//cout<<array[0]<<";"<<array[1]<<endl;


				colon = s.find_first_of(",", found_par2, 2);
				semi_colon_2 = s.find_first_of(";", found_par2);
				//	cout << "semi_colon_2 : " << semi_colon_2 << endl;
				diff = colon - found_par2;
				//	cout << "found_par2 : " << found_par2 << endl;
				//	diff2 = semi_colon_2 - found_par2;
				//	cout << "diff2 : " << diff2<< endl;

				//	cout<<diff<<endl;
				//if  (diff>4 || diff<0) 
				if (semi_colon_2 > 100)
				{
					for (int i = 0; i < c; i++)
					{
						if (i != c - 1)
							replace += array[i] + ";";
						else
							replace += array[i];
					}
					//cout<<"replace : "<<replace<<endl;
					s.replace(replaced_pos, found_par2 - replaced_pos + 1, replace);//replace array
																					//cout<<s<<endl;
					replace.clear();
					flag = 0;
					//cout<<replaced_pos<<endl;
					for (int i = 0; i < c; i++)
						array[i].clear();
					//cout<<array[0]<<endl;
					//empty arrray & replace	
				}
				c = 0;
			}
			else if (found_par1 < colon&&colon < found_par2)
				s.erase(colon, 1);
			else
			{
				//s.erase(found_par1, 1);
				//s.erase(found_par2 - 1, 1);
				s.erase(remove(s.begin(), s.end(), '['), s.end());
				s.erase(remove(s.begin(), s.end(), ']'), s.end());
				//	cout << "Second erase :" << s<<endl;
			}

			found_par1 = s.find_first_of("[", found_par1 + 1);
			found_par2 = s.find_first_of("]", found_par2 + 1);

		}

		istringstream iss(s);
		while (getline(iss, token, ';'))
		{
			istringstream iss2(token);
			while (getline(iss2, token, ' '))
			{
				//cout << token << endl;
				if ((!isFloat(token) && token.find_first_not_of(' ') != string::npos) && (!isComplex(token)))
				{
					//cout << token << endl;
					token2_pos = s.find(token);
					//					doOperation(token, varNames, varContent, variablesNo);
					//s.replace(token2_pos, token.length(),token);
					s.replace(token2_pos, token.length(), "temp");
				}
			}
		}
		//cout << s << endl;
		//	s.erase(remove(s.begin(), s.end(), '['), s.end());
		//	s.erase(remove(s.begin(), s.end(), ']'), s.end());
		s = "[" + s + "]";
	}
	//else
	//{
	//s = "[" + s + "]";
	//}



	//int real = variablesNo - Equal_no;
	for (int b = 1; b <= Equal_no; b++)
	{
		varContent[variablesNo - b] = s;
		//cout<<varContent[variablesNo]<<variablesNo<<endl;
	}


	//find similar variables

	for (int i = 0; i<variablesNo; i++)
	{
		for (int j = i + 1; j<variablesNo; j++)
		{
			if (varNames[i] == varNames[j])
			{

				varContent[i] = varContent[j];
				for (int x = j; x <= variablesNo; x++)
				{
					varContent[x] = varContent[x + 1];
					varNames[x] = varNames[x + 1];
				}
				variablesNo--;
			}
		}
	}
	if (final_semi_colon == string::npos) {
		//cout << "//" << name << "//";
		print(name, varNames, varContent, variablesNo);
	}
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
			if(string_index!=0){if (s[string_index - 1] == operators[checking_index]) prevoperator_exist = true;}
		}

		if (operator_exist == true)
		{
			if ((s[string_index] == '.'&&nextisdigit==true) ||(s[string_index] == '-'&& s[string_index-1]!='.' &&(prevoperator_exist==true&&s[string_index-1]!='='&&s[string_index-1]!=')')) ) parameters[stack_index].insert(parameters[stack_index].end(), s[string_index]);
			else 
			{ if (s[string_index] == '.'&&nextisdigit==false)stack_index++;
					operations[stack_index].insert(operations[stack_index].end(), s[string_index]);
			}
			if(s[string_index-1]== '.' /*&& operator_exist == true */) stack_index++;
			else if (s[string_index] != '.' &&
				(( s[string_index] == '!' || s[string_index] == ';'|| s[string_index] == '\'')||
				(s[string_index]!='-'&&(prevoperator_exist==false||s[string_index-1]=='='||s[string_index-1]==')')&&s[string_index+1] != '.')||
				(s[string_index]=='-'&&(prevoperator_exist==false||s[string_index-1]=='='||s[string_index-1]==')'))||
				(s[string_index]=='(')
				)) stack_index++;
		}
		else
		{
			parameters[stack_index].insert(parameters[stack_index].end(), s[string_index]);
			if (nextoperator_exist == true && nextisdigit == false && s[string_index] != '.'&& s[string_index + 1] != '.') stack_index++;
			if (string_index==s.length()-1) stack_index++;
		}

	}


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
	for (int index = stack_index-1; index>0; index--) //index is the index of opening arguments
	{
		bool simpletrignometricfn_exist=false;
		if (operations[index] == "("/*&&(operations[index]=="*"||operations[index]=="/")*/)
		{
			for (int closingArgumentIndex = index; closingArgumentIndex<stack_index; closingArgumentIndex++)
			{
				if (operations[closingArgumentIndex] == ")")
				{
					bool argument_exist=false;
					do
					{
					//do power operation
					for (int solveArgumentindex = index; solveArgumentindex<closingArgumentIndex; solveArgumentindex++)
					{
						if (operations[solveArgumentindex] == "^"||operations[solveArgumentindex] == ".^")
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
							
							if(solveArgumentindex==index&&closingArgumentIndex==index+2) {simpletrignometricfn_exist=true; break;}
							index -= 4;
						}
					}	
					if(simpletrignometricfn_exist) break;
					//do mul and div operation
					for (int solveArgumentindex = index; solveArgumentindex<closingArgumentIndex; solveArgumentindex++)
					{
						
						if (operations[solveArgumentindex] == "*" || operations[solveArgumentindex] == "/" || operations[solveArgumentindex] == ".*" || operations[solveArgumentindex] == "./"||operations[index] == "\\"||operations[index] == ".\\")
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
					for(int argumentindex=index; argumentindex<closingArgumentIndex; argumentindex++) 
					{
						if (operations[argumentindex] != ""&&operations[argumentindex]!="("&&operations[argumentindex]!=")")  argument_exist=true;
						else argument_exist=false;
					}
					}
					while(argument_exist);

	/*///////////////////
	cout<<stack_index<<endl;
	for(int i=0 ; i < stack_index ; i++)
	{
		cout << parameters[i] << "----->" << operations[i]<<endl;
	}

	///////////////////*/
					// testing for loop
					/*tempstr="";
					for (int testindex=1 ; testindex < closingArgumentIndex-index ; testindex++)
					{
					if(testindex%2==0) tempstr.insert(tempstr.length() , operations[index+testindex]);//BracesDoOpearation[0].insert(BracesDoOpearation[0].end() , parameters[index+testindex]);
					else tempstr.insert(tempstr.length() , parameters[index+testindex]);
					}
					cout<<"parsing is"<<tempstr<<endl;*/

					
					if(parameters[index-1]=="") //if not sin or cos remove arguments "(   )"
					{
						//replacing old by new data and remove unused elements from stack
						parameters[index] = parameters[index + 1];
						for (int removeindex = 0; removeindex < closingArgumentIndex - index; removeindex++)
						{
							if (removeindex % 2 == 0) operations[index + removeindex] = "";
							else parameters[index + removeindex] = "";
						}

			

			
						//remove the empty elements in the stack


						for (int WBindex = index+1 ; WBindex<stack_index; WBindex++)
						{
							operations[WBindex] = operations[WBindex + (closingArgumentIndex - index)];
							parameters[WBindex] = parameters[WBindex + (closingArgumentIndex - index)];
						}
						//stack_index -= (closingArgumentIndex - index);
						stack_index -= 2;
						index -= closingArgumentIndex - index;

						break;
					}
					if(simpletrignometricfn_exist) break;
				}
			}
		}
		if(simpletrignometricfn_exist) break;
	}

	for(int argumentindex=0; argumentindex<stack_index; argumentindex++) 
		{
			if (/*operations[argumentindex] != ""&&*/operations[argumentindex]=="("||operations[argumentindex]==")") { more_arguments=true; break;}
						else more_arguments=false;
		}
	}
	while(more_arguments);
				


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
			index -= 4;
		}
	}	



	//slove simple opeartions like * , / , ... etc
	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "^"||operations[index] == ".^")
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
			index -= 3;
		}
	}
	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "*" || operations[index] == "/" || operations[index] == ".*" || operations[index] == "./"||operations[index] == "\\"||operations[index] == ".\\")
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
			index -= 3;
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
			index -= 3;
		}
	}

	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "&" || operations[index] == "|" )
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
			index -= 3;
		}
	}

	/*if (stack_index == 4 && operations[1] == "="&&parameters[0] == "temp" && parameters[3]==";")
	{
		s = parameters[0] + operations[1] + parameters[2];
	}*/
	if (stack_index == 4 && operations[1] == "="&&parameters[0] != "temp"&& operations[3]==";")
	{
		bool variablexsist=false;
		for(int checkingindex=0 ; checkingindex<variablesNo;checkingindex++)
		{
			if(varNames[checkingindex]==parameters[0])
			{
				variablexsist=true;
				varNames[checkingindex] = parameters[0];
				varContent[checkingindex] = parameters[2];
				break;
			}
		}
		if(variablexsist==false)
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
	else if (stack_index == 3  && operations[1] == "=" &&parameters[0] != "temp" )
	{
		bool variablexsist=false;
		for(int checkingindex=0 ; checkingindex<variablesNo;checkingindex++)
		{
			if(varNames[checkingindex]==parameters[0])
			{
				variablexsist=true;
				varNames[checkingindex] = parameters[0];
				varContent[checkingindex] = parameters[2];
				break;
			}
		}
		if(variablexsist==false)
		{
		varNames[variablesNo] = parameters[0];
		varContent[variablesNo] = parameters[2];
		variablesNo++;
		}
		print(parameters[0], varNames, varContent,variablesNo);
	}
	else if (stack_index == 2  && operations[1] == ";")
	{
		s=parameters[0];
	}
	else  { s = parameters[0]; cout<<parameters[0];}
}
