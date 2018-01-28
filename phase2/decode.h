#pragma once
#include <string>
using namespace std;
void print(string s, string varNames[100], string varContent[100], int& variableNo);
void decode(string s, string varNames[100], string varContent[100], int& variableNo);
inline bool isInteger(const std::string & s);
void defMat(string s, string varNames[100], string varContent[100], int& variablesNo);
void defSpecialMat(string s, string varNames[100], string varContent[100], int& variablesNo);
void doOperation(string& s, string varNames[100], string varContent[100], int& variablesNo); // Peter /* Will take a string input like A = 3 * sin(0.2) + d (9 + b * exp(3)) where d and b might be matrices*/