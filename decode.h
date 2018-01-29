#pragma once
#include <string>
using namespace std;
void decode(string s, string varNames[100], string varContent[100], int& variableNo);

int countInString(const string& s, const string& something, const int& firstPos = 0, int lastPos = -1);
void replaceFromStackIntoString(string &s, string varNames[100], string varContent[100], int& variablesNo);
string handleMatrix(string &s, const string varNames[100], const string varContent[100], const int& variablesNo);
string handleOperation(string s, const string varNames[100], const string varContent[100], const int& variablesNo);
void defMat(string s, string varNames[100], string varContent[100], int& variablesNo);

void print(string s, string varNames[100], string varContent[100], int& variableNo);
inline bool isInteger(const std::string & s);
void defSpecialMat(string s, string varNames[100], string varContent[100], int& variablesNo);
void doOperation(string& s, string varNames[100], string varContent[100], int& variablesNo);