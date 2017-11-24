#include "stdafx.h"
#include "cmatrix.h"
#include "helpers.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int getDataFromFile(string file, string  matrix_names2[100], string matrix2[100], string first_parameter[100], string second_parmeter[100], string m_operation[100], string result[100])
{
	string line; 												// Every Single Line in the file
	ifstream infile(file.c_str()); 								// Read the file by ifstream and named it infile
	int  flag1 = 0, flag2 = 0, flag3 = 0; 						// counter for the number of lines
	size_t Equal_pos, first_parases_pos, second_prases_pos;		// position of '[' & ']'
	string matrix[100], operation[100], operation2[100];// matrix contents , & Operations line
	string matrix_names[100];				// matrix names
	int  m = 0, o = 0, c = 0, Equal_no = 0, Equal_pos2, matrixes_num, e = 0;

	while (getline(infile, line))  //the condition is true while there is still a line 
	{
		for (int j = 0; j <= line.length(); j++)
		{
			if (line[j] == '[')								// Find '[' : begin of a matrix
			{
				first_parases_pos = line.find('[');			// pos of the '['
				flag1 = 1;									// flag for finding the [
				break;										// stop searching for [
			}
			else if (line[j] == ']' || line[j] == ';')		//find the end of the matrix  or there is still ';' of a matrix
			{
				flag2 = 1;									// flag2
				second_prases_pos = line.find(']');			// save pos of ']'
				break;
			}
		}

		if (flag1 == 1)  // if it is a begin of a matrix
		{
			Equal_pos = line.find_last_of('='); //pos of'='
			second_prases_pos = line.find(']'); //pos of']'
			if (second_prases_pos != string::npos) matrix[m] = line.substr(first_parases_pos, line.length()); //if there is no ']'
			else  matrix[m] = line.substr(first_parases_pos, second_prases_pos);
			matrix_names[m] = line.substr(0, Equal_pos + 1);
			//cout << matrix_names[m] << endl;
			m++;
			flag1 = 0;
		}
		else if (flag2 == 1)
		{
			matrix[m - 1] += line;
			flag2 = 0;
		}

		else
		{
			Equal_pos = line.find('=');
			if (Equal_pos == string::npos)matrix[m - 1] += line;
			else
			{
				operation[o] = line;
				o++;
			}
		}
	}
	infile.close();
	matrixes_num = m;
	int matrixNo = 0;
	//remove spaces from matrix names
	for (int v = 0; v<m; v++) {
		matrix_names[v].erase(std::remove(matrix_names[v].begin(), matrix_names[v].end(), ' '), matrix_names[v].end());
	}
	for (int a = 0; a < matrixes_num; a++)
	{
		Equal_no = count(matrix_names[a].begin(), matrix_names[a].end(), '=');
		Equal_pos = matrix_names[a].find_first_of('=');
		if (Equal_no>1)
		{
			for (int b = 0; b<Equal_no; b++)
			{
				Equal_pos2 = matrix_names[a].find_first_of('=');
				matrix_names[m] = matrix_names[a].substr(0, Equal_pos2);
				matrix[m] = matrix[a];
				matrix_names[a].erase(0, Equal_pos2 + 1);
				m++;
			}
			matrix[a].erase(matrix[a].begin(), matrix[a].end());
		}
		else
		{
			matrix_names[a] = matrix_names[a].substr(0, Equal_pos);
		}
		matrixNo += Equal_no;
	}


	//cout << matrixNo << endl;
	for (int x = 0; x<o; x++)
	{
		if (!operation[x].empty())
		{
			operation2[c] = operation[x];
			//cout << operation2[c]<<endl;
			c++;
		}
	}

	/**************************************************
	***************************************************
	***************************************************
	**************************************************/
	//edit as we need the counter c as no of operations
	int operationNo = c;
	c = 0;
	for (int x = 0; x<m; x++)
	{
		if (!matrix_names[x].empty())
		{
			matrix_names2[c] = matrix_names[x];
			c++;
		}
	}
	c = 0;
	for (int x = 0; x<m; x++)
	{
		if (!matrix[x].empty())
		{
			matrix2[c] = matrix[x];
			c++;
		}
	}

	/*
	for (int x = 0; x< m; x++)
	cout << matrix_names2[x] << "" << matrix2[x] << endl;*/

	/////////////////////////////////////////////////////////////
	//  Operation Part //


	int result_pos, equal_pos, first_parameter_pos, operation_pos, second_parameter_pos;
	for (int z = 0; z< operationNo; z++)
	{
		//cout<<operation2[0]<<endl;
		for (int i = 0; i<operation2[z].length(); i++)
		{
			if (operation2[z][i] != ' ')
			{
				result[z] = operation2[z][i];
				//cout << result[z] << endl;
				result_pos = i;
				break;
			}
		}
		//cout<<result[0]<<endl;

		for (int i = 0; i<operation2[z].length(); i++)
		{
			if (operation2[z][i] == '=')
			{
				equal_pos = i;
			}
		}
		//cout<<"equal_pos = "<<equal_pos<<endl;
		operation2[z].erase(0, equal_pos + 1);
		//cout<<operation2[0]<<endl;
		for (int i = 0; i<operation2[z].length(); i++)
		{
			if (operation2[z][i] != ' ')
			{
				first_parameter[z] = operation2[z][i];
				first_parameter_pos = i;
				break;
			}
		}
		operation2[z].erase(0, first_parameter_pos + 1);
		///cout<<first_parameter[0]<<endl<<operation2[0]<<endl;

		for (int i = 0; i<operation2[z].length(); i++)
		{
			if (operation2[z][i] != ' ')
			{
				m_operation[z] = operation2[z][i];
				operation_pos = i;
				if (m_operation[z] == ".")
				{
					m_operation[z] += operation2[z][i + 1];
					operation_pos = i + 1;

				}
				break;
			}
		}
		operation2[z].erase(0, operation_pos + 1);
		//cout<<m_operation[0]<<endl<<operation2[0]<<endl;

		for (int i = 0; i<operation2[z].length(); i++)
		{
			if (operation2[z][i] != ' ')
			{
				second_parmeter[z] = operation2[z][i];
				second_parameter_pos = i;
				break;
			}
		}
		operation2[z].erase(0, second_parameter_pos + 1);
		//cout<<second_parmeter[0]<<endl;
		//cout<<result<<endl<<first_parameter<<endl<<operation<<endl<<second_parmeter<<endl<<x;

	}

	/*for (int x = 0; x< operationNo; x++)
	cout << result[x] << " " << first_parameter[x] << " " << m_operation[x] << " "  << second_parmeter[x] << endl;*/

	return matrixNo;
}
int passDataToOperators(int NoOfMatrices, string  matrix_names[100], string matrix[100], string first_parameter[100], string second_parmeter[100], string m_operation[100], string result[100])
{
	for (int Index = 0; Index < 100; Index++) {
		string firstParameterName = first_parameter[Index];
		string secondParameterName = second_parmeter[Index];
		string resultName = result[Index];
		int firstParameterIndex = 0, secondParameterIndex = 0, resultIndex = 0;
		int getFirstParameterIndexFlag = 0, getSecondParameterIndexFlag = 0, getResultIndexFlag = 0;
		for (int matrix_namesIndex = 0; matrix_namesIndex < NoOfMatrices; matrix_namesIndex++) {
			if (firstParameterName == matrix_names[matrix_namesIndex]) {
				firstParameterIndex = matrix_namesIndex;
				getFirstParameterIndexFlag = 1;
			}
			else if (secondParameterName == matrix_names[matrix_namesIndex]) {
				secondParameterIndex = matrix_namesIndex;
				getSecondParameterIndexFlag = 1;
			}
			if (resultName == matrix_names[matrix_namesIndex]) {
				resultIndex = matrix_namesIndex;
				getResultIndexFlag = 1;
			}
			else if (getFirstParameterIndexFlag == 1 && getSecondParameterIndexFlag == 1 && getResultIndexFlag == 1)
				break;
		}
		string firstParameterContent = matrix[firstParameterIndex];
		string secondParameterContent = matrix[secondParameterIndex];
		CMatrix matrix1(firstParameterContent);
		CMatrix matrix2(secondParameterContent);
		string Operator = m_operation[Index];

		string resultContent;
		if (Operator == "+") {
			resultContent = (matrix1 + matrix2).getOriginalString();
			//cout << resultContent << endl;
		}
		else if (Operator == "-") {
			resultContent = (matrix1 - matrix2).getOriginalString();

		}
		else if (Operator == "*") {
			resultContent = (matrix1 * matrix2).getOriginalString();

		}

		else if (Operator == "/")
		{
			resultContent = (matrix1 / matrix2).getOriginalString();
		}

		else if (Operator == "./") {
			//CMatrix x = matrix1.getInverse();
			resultContent = (matrix2.denominatorOfDiv(atof(firstParameterName.c_str()))).getOriginalString();

		}
		else if (Operator == "'") {
			resultContent = (matrix1.getTranspose()).getOriginalString();

		}
		else
			return NoOfMatrices;
		if (getResultIndexFlag == 1)
			matrix[resultIndex] = resultContent;
		else {
			NoOfMatrices++;
			matrix_names[NoOfMatrices - 1] = resultName;
			matrix[NoOfMatrices - 1] = resultContent;
		}


	}

	return NoOfMatrices;
}
void PrintToScreen(int NoOfMatrices, string  matrix_names[100], string matrix[100], string result[100]) {
	for (int Index = 0; Index < 100; Index++) {
		for (int MatrixIndex = 0; MatrixIndex < NoOfMatrices; MatrixIndex++) {
			if (result[Index] == matrix_names[MatrixIndex]) {
				cout << matrix_names[MatrixIndex] << " = " << matrix[MatrixIndex] << endl;
			}

		}
	}
}
void PrintToFile(string file, int NoOfMatrices, string  matrix_names[100], string matrix[100], string result[100]) {

	for (int Index = 0; Index < 100; Index++) {
		for (int MatrixIndex = 0; MatrixIndex < NoOfMatrices; MatrixIndex++) {
			if (result[Index] == matrix_names[MatrixIndex]) {
				CMatrix temp(matrix[MatrixIndex]);
				cout << matrix_names[MatrixIndex] << " = " << temp.getString(5) << endl;
			}

		}
	}
	/*ofstream outfile(file.c_str());
	if (outfile.fail()) {
	throw("Cannot open the outfile");
	}
	for (int Index = 0; Index < 100; Index++) {
	for (int MatrixIndex = 0; MatrixIndex < NoOfMatrices; MatrixIndex++) {
	if (result[Index] == matrix_names[MatrixIndex]) {
	CMatrix temp(matrix[MatrixIndex]);
	outfile << matrix_names[MatrixIndex] << " = " << temp.getString(6) << endl;
	}

	}
	}
	outfile.close();*/
}

int processInput(string input, string matrices_names[100], CMatrix matrices[100], int matricesNo) {
	bool printToScreen = 1;
	if (input.substr(input.length() - 1) == ";") { //checking for ; at the end of the line, If it exists than we don't cout the result of the current operation
		printToScreen = 0;
		input = input.substr(0, input.length() - 1);
	}
	if (input.find("[") != string::npos) {
		while (input.find("]") == string::npos) {
			string s;
			getline(cin, s);
			input += s;
		}
		CMatrix tempMat(input.substr(input.find("["), input.find("]") - (input.find("[") - 1)));
		string tempS = "";
		for (int i = 0; i<input.length(); i++) {
			if (input[i] != ' ') tempS += input[i];
		}
		do {
			matrices_names[matricesNo] = tempS.substr(0, tempS.find("="));
			//cout <<"new term " << matrices_names[matricesNo] << endl;
			matrices[matricesNo] = tempMat;
			if (printToScreen) cout << matrices_names[matricesNo] << " = " << matrices[matricesNo].getString(7) << endl;
			matricesNo++;
			tempS = tempS.substr(tempS.find("=") + 1, tempS.length() - (tempS.find("=") + 1));
			//cout <<"new sub " << tempS << endl;
		} while (tempS.find("=") != string::npos);
	}
	else {
		//getting opertaion
		string operation;
		if (input.find("+") != string::npos) operation = "+";
		else if (input.find("-") != string::npos) operation = "-";
		else if (input.find("*") != string::npos) operation = "*";
		else if (input.find("./") != string::npos) operation = "./";
		else if (input.find("/") != string::npos) operation = "/";
		else if (input.find("'") != string::npos) operation = "'";
		else { return matricesNo; };

		string tempS = "";
		for (int i = 0; i<input.length(); i++) if (input[i] != ' ') tempS += input[i];
		string parameter0 = tempS.substr(0, tempS.find("="));
		string parameter1 = tempS.substr(tempS.find("=") + 1, tempS.find(operation) - (tempS.find("=") + 1));
		string parameter2;
		if (operation == "+" || operation == "-" || operation == "*" || operation == "/") parameter2 = tempS.substr(tempS.find(operation) + 1, tempS.length() - (tempS.find(operation) + 1));
		else if (operation == "./") parameter2 = tempS.substr(tempS.find(operation) + 2, tempS.length() - (tempS.find(operation) + 2));
		else if (operation == "'");
		int parameter0id = -1, parameter1id = -1, parameter2id = -1;
		for (int i = 0; i<matricesNo; i++) {
			if (parameter0 == matrices_names[i]) parameter0id = i;
			else if (parameter1 == matrices_names[i]) parameter1id = i;
			else if (parameter2 == matrices_names[i] && operation != "'") parameter2id = i;
		}
		if (parameter0id == -1) { parameter0id = matricesNo; matrices_names[matricesNo] = parameter0; matricesNo++; }
		CMatrix tempMat;
		if (operation != "./") tempMat.copy(matrices[parameter1id]);
		if (operation == "+") tempMat.add(matrices[parameter2id]);
		else if (operation == "-") tempMat.sub(matrices[parameter2id]);
		else if (operation == "*") tempMat.mul(matrices[parameter2id]);
		else if (operation == "/") tempMat.div(matrices[parameter2id]);
		else if (operation == "./") {
			tempMat.copy(matrices[parameter2id]);
			tempMat.copy(tempMat.denominatorOfDiv(atof(parameter1.c_str())));
		}
		else if (operation == "'") tempMat.copy(tempMat.getTranspose());
		matrices[parameter0id].copy(tempMat);
		if (printToScreen) cout << matrices_names[parameter0id] << " = " << matrices[parameter0id].getString(7) << endl;
	}
	return matricesNo;
}