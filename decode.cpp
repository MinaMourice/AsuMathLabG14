#include "cmatrix.h"
#include "solve.h"

void defSpecialMat(string s, string varNames[100], string varContent[100], string outToFile[100] , int& variablesNo, int& outFileSize) {}
// Hanaa /* Define special matrices like B = rand(2, 3), C = eye(2, 4), d = F = ones(2, 3) and g = zeros(5, 4) */

void defMat(string s, string varNames[100], string varContent[100], string outToFile[100] , int& variablesNo, int& outFileSize) {} 
// Mina Mouries /* Define matrices that contain variables like b = [1; 2] a = [5] A = a = [1 3 4 5 a sin(0.4); 3 2 3 4 [9 2]; [2 3 4 2 1; 2 3 4 5 6], b] i.e: any matrix other than special matrices defined above*/

void doOperatrion(string s, string varNames[100], string varContent[100], string outToFile[100] , int& variablesNo, int& outFileSize)
{
	//define our differnt operations types
	string FirstLevelOperators[2]={"'","!"};
	string SecondLevelOperators[1]={"^"};
	string ThirdLevelOperators[4] = {"*",".*","/","./"};
	string FourthLevelOperators[4]={"+","-",".+",".-"};
	//trigonometric and exponential functions
	string functions[13]={"sin(","cos(","tan(","atan(","asin(","acos(","sinh(","cosh(","tanh","exp(","log(","log10(","sqrt("};
	string tempstr;
	int cursor=0;
	//int trigonometricIndex =0 ;
	do
	{
		int functionExist = 0;
		for(int i=0 ; i<13 ; i++)
		{
			if(s.find(functions[i]) != string::npos) 
			{
				cursor=s.find(functions[i]);
				tempstr=solve((s.substr(s.find(functions[i]),s.find_first_of(")" ,cursor)-s.find(functions[i])+1)),&varNames[100], &varContent[100], variablesNo);
				s.replace(s.find(functions[i]),s.find_first_of(")" ,cursor)-s.find(functions[i])+1,tempstr);
				functionExist=1;
			}
		}
		if(functionExist==0) break;
	} while(1);
	//do opertions between braces (.....)
	do
	{
		if(s.find("(") != string::npos)    // this line might can be removed 
		{
			cursor=s.find("(");
			tempstr=s.substr(s.find("(")+1 , s.find_first_of(")" , cursor) - s.find("(")-1);   // take a string like --> a+b*6-c^9 
			doOperatrion(tempstr,&varNames[100],&varContent[100], &outToFile[100] ,variablesNo,outFileSize);
			s.replace(s.find("("),s.find_first_of(")" ,cursor)-s.find("(")+1,tempstr);
		}
	} while (s.find("(") != string::npos); //we replaced all braces from s by its value
	
	//do level 1 operations "'","!"
	
	do
	{
		int spacecursor ;
		int level1flag=0;
		for(int i=0 ; i<2 ; i++)
		{
			if(s.find(FirstLevelOperators[i]) != string::npos) 
			{
				cursor=s.find(FirstLevelOperators[i]);
				spacecursor=s.find_last_of(" ",cursor);
				if(spacecursor==cursor-1) spacecursor=s.find_last_of(" ",spacecursor-1);
				tempstr=solve((s.substr(spacecursor+1,cursor-spacecursor)),&varNames[100], &varContent[100], variablesNo);
				s.replace(spacecursor+1,cursor-spacecursor,tempstr);
				level1flag=1;
			}
		}
		if(level1flag==0) break;
	} while(1);

	//do level 2 opeations
	do
	{
		int spacecursorBefore , spacecursorAfter;
		int level2flag=0;
		for(int i=0 ; i<1 ; i++)
		{
			if(s.find(SecondLevelOperators[i]) != string::npos) 
			{
				cursor=s.find(SecondLevelOperators[i]);
				spacecursorBefore=s.find_last_of(" ",cursor);
				if(spacecursorBefore==cursor-1) spacecursorBefore=s.find_last_of(" ",spacecursorBefore-1);
				spacecursorAfter=s.find_first_of(" ",cursor);
				if(spacecursorAfter==cursor-1) spacecursorAfter=s.find_first_of(" ",spacecursorAfter-1);
				tempstr=solve((s.substr(spacecursorBefore+1,spacecursorAfter-spacecursorBefore)),&varNames[100], &varContent[100], variablesNo);
				s.replace(spacecursorBefore+1,spacecursorAfter-spacecursorBefore,tempstr);
				level2flag=1;
			}
		}
		if(level2flag==0) break;
	} while(1);

	

} // Peter /* Will take a string input like A = 3 * sin(0.2) + d (9 + b * exp(3)) where d and b might be matrices*/

void printToFile(string file, string outToFile[100] , int& outFileSize) {} 
// Beshoy /* Takes the file name as input and prints all the data in it */

void decode(string s, string varNames[100], string varContent[100], string outToFile[100] , int& variablesNo, int& outFileSize) {} 
// Beshoy /* Takes line by line from main function and determine how to work on each line */