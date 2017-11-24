#ifndef HELPERS_H
#define HELPERS_H
#include<string>

using namespace std;

int getDataFromFile(string file, string  matrix_names[100], string matrix[100], string first_parameter[100], string second_parmeter[100], string m_operation[100], string result[100]);

int passDataToOperators(int NoOfMatrices, string  matrix_names[100], string matrix[100], string first_parameter[100], string second_parmeter[100], string m_operation[100], string result[100]);

void PrintToScreen(int NoOfMatrices, string  matrix_names[100], string matrix[100], string result[100]);

void PrintToFile(string file, int NoOfMatrices, string  matrix_names[100], string matrix[100], string result[100]);

int processInput(string input, string matrices_names[100], CMatrix matrices[100], int matricesNo);
#endif