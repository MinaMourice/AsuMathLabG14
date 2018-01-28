#ifndef SOLVE_H
#define SOLVE_H

#include <string>
#include"cmatrix.h"
#include <iostream>
using namespace std;
string solve(string s, string varNames[100], string varContent[100], int& variablesNo); // Hanaa /* Takes a string as input and returns a string output, Input may contain previous predefined variables and/or normal numbers */
CMatrix solveCMatrix(string s, string varNames[100], string varContent[100] , int& variablesNo); // Verina /* Takes a string as input and returns a matrix output, Input may contain previous predefined variables and/or normal numbers */
double solveDouble(string s, string varNames[100], string varContent[100] , int& variablesNo); //  Marina /* Takes a string as input and returns a double output, Input may contain previous predefined variables and/or normal numbers */

#endif
