#include "stdafx.h"
#include "decode.h"
#include "solve.h"
#include "cmatrix.h"
#include <iostream>
#include <sstream>
using namespace std;
void print(string s, string varNames[100], string varContent[100], int& variableNo) {
	for (int index = 0; index < variableNo; index++) {
		if (varNames[index] == s) {
			cout << varNames[index] << "=" << varContent[index]<<endl;
			return;
		}
	}
	cout << s << " is not defined"<< endl;
}
void decode(string info, string varNames[100], string varContent[100], int& variableNo) {
	int defMatFlag = 0;
	for (int charIndex = 0; charIndex < info.length(); charIndex++) {
		if (info[charIndex] == '[') {
			defMatFlag = 1;
			defMat(info, varNames, varContent, variableNo);
			cout << "send: " << info << "to defMat" << endl;
			break;
		}
	}
	if (defMatFlag == 0) {
		if (info.find("rand") != string::npos || info.find("eye") != string::npos || info.find("ones") != string::npos || info.find("zeros") != string::npos) {
			defSpecialMat(info, varNames, varContent, variableNo);
			cout << "send: " << info << "to defSpecialMat" << endl;
		}
		else if (info.find('=') != string::npos) {
			doOperation(info, varNames, varContent, variableNo);
			cout << "send: " << info << "to doOperation" << endl;
		}
		else {
			print(info, varNames, varContent, variableNo);
		}
	}
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


bool isFloat(string myString) {
	std::istringstream iss(myString);
	float f;
	iss >> noskipws >> f; // noskipws considers leading whitespace invalid
						  // Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}

void defMat(string s, string varNames[100], string varContent[100], int& variablesNo)
{
	string varnames[100];
	string array[100], text, token, token2, replace;
	size_t Equal_pos, found_var, found_par1, found_par2, semi_colon, semi_colon_2, semi_colon_no, colon, token2_pos, final_semi_colon;
	int flag = 0, c = 0, replaced_pos, diff, e = 0, Equal_no;

	Equal_no = count(s.begin(), s.end(), '=');
	for (int b = 0; b<Equal_no; b++)
	{
		Equal_pos = s.find_first_of('=');

		varnames[e] = s.substr(0, Equal_pos);
		s.erase(0, Equal_pos + 1);
	}
	cout << s << endl;



	for (int i = 0; i<3; i++)
	{
		found_var = s.find_first_of(varNames[i]);
		while (found_var != string::npos)
		{
			//cout << "first 'var' found at: " << found_var << '\n';
			s.replace(found_var, varNames[i].length(), varContent[i]);
			found_var = s.find_first_of(varNames[i], found_var + 1);
		}
	}

	final_semi_colon = s.find_last_of(";");
	if (final_semi_colon == string::npos)
	{
		for (int b = 0; b<Equal_no; b++)
		{
//			outToFile[b] = varnames[b];
		}
	}
	// find '[' & ']' & what is between them
	s.erase(s.find_first_of("["), 1);
	s.erase(s.find_last_of("]"), 1);
	found_par1 = s.find_first_of("[");
	found_par2 = s.find_first_of("]");


	//	cout<<s<<endl;
	while (found_par1 != string::npos&& found_par2 != string::npos)
	{

		//cout<<found_par1<<" "<<found_par2<<endl;

		semi_colon = s.find(";", found_par1);
		//cout<<semi_colon<<endl;
		if (found_par1<semi_colon&&semi_colon< found_par2)
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
			for (int i = 0; i <= semi_colon_no; i++)
			{
				getline(iss, token, ';');
				array[c] += " " + token;
				c++;

			}

			//cout<<array[0]<<";"<<array[1]<<endl;


			colon = s.find_first_of(",", found_par2);
			diff = colon - found_par2;
			//	cout<<diff<<endl;
			if (diff>4 || diff<0)
			{
				for (int i = 0; i<c; i++)
				{
					if (i != c - 1)
						replace += array[i] + ";";
					else
						replace += array[i];
				}
				//cout<<replace<<endl;
				s.replace(replaced_pos, found_par2 - replaced_pos + 1, replace);//replace array
																				//cout<<s<<endl;
				replace.clear();
				flag = 0;
				//cout<<replaced_pos<<endl;
				for (int i = 0; i<c; i++)
					array[i].clear();
				//cout<<array[0]<<endl;
				//empty arrray & replace	
			}
			c = 0;
		}
		else
		{
			s.erase(found_par1, 1);
			s.erase(found_par2 - 1, 1);
		}

		found_par1 = s.find_first_of("[", found_par1 + 1);
		found_par2 = s.find_first_of("]", found_par2 + 1);

	}

	istringstream iss(s);
	while (getline(iss, token, ';'))
	{
		istringstream iss2(token);
		while (getline(iss2, token2, ' '))
		{
			//cout<<token2<<endl;
			if (!isFloat(token2) && token2.find_first_not_of(' ') != string::npos)
			{
				token2_pos = s.find(token2);
				s.replace(token2_pos, token2.length(), "temp");
			}
		}
	}
	//cout << "[" << s << "]" << endl;
	s = "[" + s + "]";
	cout << s << endl;
	for (int b = 0; b<Equal_no; b++)
	{
		varContent[b] = s;
	}



} // Mina Mouries /* Define matrices that contain variables like b = [1; 2] a = [5] A = a = [1 3 4 5 a sin(0.4); 3 2 3 4 [9 2]; [2 3 4 2 1; 2 3 4 5 6], b] i.e: any matrix other than special matrices defined above*/
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
	string operators = "=+-*/.^'!()";
	int stack_index = 0;
	for (int string_index = 0; string_index<s.length(); string_index++)
	{
		if (s[string_index] == ' ') continue;
		//parameters[stack_index]="";  operations[stack_index]=""; //initialinzing the values of stack elements
		bool operator_exist = false;
		bool nextoperator_exist = false;
		bool nextisdigit = false;
		if (s[string_index] == '.') { if (isdigit(s[string_index + 1]) == 1) nextisdigit = true; }
		for (int checking_index = 0; checking_index<operators.length(); checking_index++)
		{
			if (s[string_index] == operators[checking_index]) operator_exist = true;
			if (s[string_index + 1] == operators[checking_index]) nextoperator_exist = true;
		}

		if (operator_exist == true)
		{
			if (s[string_index] == '.') parameters[stack_index].insert(parameters[stack_index].end(), s[string_index]);
			else operations[stack_index].insert(operations[stack_index].end(), s[string_index]);
			if (s[string_index] != '.' || s[string_index] == '!' || s[string_index] == operators[7]) stack_index++;
		}
		else
		{
			parameters[stack_index].insert(parameters[stack_index].end(), s[string_index]);
			if (nextoperator_exist == true && nextisdigit == false && s[string_index] != '.'&& s[string_index + 1] != '.') stack_index++;
		}

	}

	//solve factorial or transpose operations
	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "!" || operations[index] == "'")
		{
			tempstr = solve(parameters[index - 1] + operations[index], &varNames[100], &varContent[100], variablesNo);
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
	// if we find "(" @ index and index+2=")" then it might be sins ,cos ,.. etc 
	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "(" && operations[index + 2] == ")")
		{
			tempstr = solve(parameters[index - 1] + operations[index] + parameters[index + 1] + operations[index + 2], &varNames[100], &varContent[100], variablesNo);
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
	//solve arguments "(" do some operations")"
	for (int index = stack_index; index>0; index++) //index is the index of opening arguments
	{
		if (operations[index] == "("/*&&(operations[index]=="*"||operations[index]=="/")*/)
		{
			for (int closingArgumentIndex = index; closingArgumentIndex<stack_index; closingArgumentIndex++)
			{
				if (operations[closingArgumentIndex] == ")")
				{
					//do power operation
					for (int solveArgumentindex = 0; index<stack_index; index++)
					{
						if (operations[solveArgumentindex] == "^")
						{
							tempstr = solve(parameters[solveArgumentindex - 1] + operations[solveArgumentindex] + parameters[solveArgumentindex + 1], &varNames[100], &varContent[100], variablesNo);
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
					//do mul and div operation
					for (int solveArgumentindex = 0; solveArgumentindex<stack_index; solveArgumentindex++)
					{
						if (operations[solveArgumentindex] == "*" || operations[solveArgumentindex] == "/" || operations[solveArgumentindex] == ".*" || operations[solveArgumentindex] == "./")
						{
							tempstr = solve(parameters[solveArgumentindex - 1] + operations[solveArgumentindex] + parameters[solveArgumentindex + 1], &varNames[100], &varContent[100], variablesNo);
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
					for (int solveArgumentindex = 0; solveArgumentindex<stack_index; solveArgumentindex++)
					{
						if (operations[solveArgumentindex] == "+" || operations[solveArgumentindex] == "-" || operations[solveArgumentindex] == ".+" || operations[solveArgumentindex] == ".-")
						{
							tempstr = solve(parameters[solveArgumentindex - 1] + operations[solveArgumentindex] + parameters[solveArgumentindex + 1], &varNames[100], &varContent[100], variablesNo);
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
					// testing for loop
					/*tempstr="";
					for (int testindex=1 ; testindex < closingArgumentIndex-index ; testindex++)
					{
					if(testindex%2==0) tempstr.insert(tempstr.length() , operations[index+testindex]);//BracesDoOpearation[0].insert(BracesDoOpearation[0].end() , parameters[index+testindex]);
					else tempstr.insert(tempstr.length() , parameters[index+testindex]);
					}
					cout<<"parsing is"<<tempstr<<endl;*/

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
					stack_index -= (closingArgumentIndex - index);
					index -= closingArgumentIndex - index;
					break;
				}
			}
		}
	}



	//slove simple opeartions like * , / , ... etc
	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "^")
		{
			tempstr = solve(parameters[index - 1] + operations[index] + parameters[index + 1], &varNames[100], &varContent[100], variablesNo);
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
		if (operations[index] == "*" || operations[index] == "/" || operations[index] == ".*" || operations[index] == "./")
		{
			tempstr = solve(parameters[index - 1] + operations[index] + parameters[index + 1], &varNames[100], &varContent[100], variablesNo);
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
			tempstr = solve(parameters[index - 1] + operations[index] + parameters[index + 1], &varNames[100], &varContent[100], variablesNo);
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

	if (stack_index == 3 && operations[1] == "="&&parameters[0] == "temp")
	{
		s = parameters[0] + operations[1] + parameters[2];
	}
	else if (stack_index == 3 && operations[1] == "="&&parameters[0] != "temp")
	{
		varNames[variablesNo] = parameters[0];
		varContent[variablesNo] = parameters[2];
		variablesNo++;
	}
	else  s = parameters[0];
}