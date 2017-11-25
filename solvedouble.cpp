#include "cmatrix.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include <string> 
#include <stdlib.h>
using namespace std;

double solveDouble(string s, string varNames[100], string varContent[100] , int& variablesNo) //  Marina /* Takes a string as input and returns a double output, Input may contain previous predefined variables and/or normal numbers */
{
	
int placeofspecial = s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") ;
	
	if (s.at(placeofspecial)=='(')
	{//sin
		string only1operandfromvarnames = s.substr(placeofspecial+1,s.find(')')-placeofspecial-1);

		int only1operandindex =-1;
		for(int i=0;i<variablesNo;i++)
		{
			if(only1operandfromvarnames==varNames[i])
			{
				only1operandindex =i;
			}
		}
		string TRIG = s.substr(0,placeofspecial);
		if(only1operandindex!=-1)
		{
		string only1operandcontent=varContent[only1operandindex] ;
	    double only1operandtodouble = atof(only1operandcontent.c_str());
		

		  //only one operand

	           if (TRIG == "sin")
        	 { return sin(only1operandtodouble);}
			   else if (TRIG == "cos")
          	 {return cos(only1operandtodouble);}
			   else  if (TRIG == "tan")
	         {return tan(only1operandtodouble);}
			   else if (TRIG == "asin") 
	         {return asin(only1operandtodouble);}
			   else if (TRIG == "acos")  
	         {return acos(only1operandtodouble);}
               else if (TRIG == "atan")  
	         {return atan(only1operandtodouble);}
			   else if (TRIG == "sinh")
			 {return sinh(only1operandtodouble);}
			   else if (TRIG == "cosh")
			 {return cosh(only1operandtodouble);}
			   else if (TRIG == "tanh")
			 {return tanh(only1operandtodouble);}
	           else if (TRIG == "exp")
	         {return exp(only1operandtodouble);}
	           else if (TRIG == "log") 
	         {return log(only1operandtodouble);}
	           else if (TRIG == "log10") 
	         {return log10(only1operandtodouble);}
	           else if (TRIG == "sqrt")  
	         {return sqrt(only1operandtodouble);}
	           else if (TRIG == "abs")
	         {return abs(only1operandtodouble);} 

			}

			else 
				
			{
				//only one as number 
			
		         double  only1operandasnumbertodouble = atof(only1operandfromvarnames.c_str());
				 
			   if (TRIG == "sin")
	         {return sin(only1operandasnumbertodouble);}
	           else if (TRIG == "cos")
	         {return cos(only1operandasnumbertodouble);}
	           else if (TRIG == "tan")
	         {return tan(only1operandasnumbertodouble);}
	           else if (TRIG == "asin")
	         {return asin(only1operandasnumbertodouble);}
               else if (TRIG == "acos")
	         {return acos(only1operandasnumbertodouble);}
               else if (TRIG == "atan") 
	         {return atan(only1operandasnumbertodouble);}
			   else if (TRIG == "sinh")
			 {return sinh(only1operandasnumbertodouble);}
			   else if (TRIG == "cosh")
			 {return cosh(only1operandasnumbertodouble);}
			   else if (TRIG == "tanh")
			 {return tanh(only1operandasnumbertodouble);}
	           else if (TRIG == "exp")
	         {return exp(only1operandasnumbertodouble);}
	           else if (TRIG == "log") 
	         {return log(only1operandasnumbertodouble);}
	           else if (TRIG == "log10") 
	         {return log10(only1operandasnumbertodouble);}
	           else if (TRIG == "sqrt")  
	         {return sqrt(only1operandasnumbertodouble);}
	           else if (TRIG == "abs")
	         {return abs(only1operandasnumbertodouble);}
			}
			}
	
	
	else{
	//plus
		//if the operation between two variables 
				string checkvariable1invariablenames = s.substr(0,placeofspecial);
		        string checkvariable2invariablenames = s.substr(placeofspecial+1,s.length());

				int operand1index =-1;
			    int operand2index =-1;
		for(int i=0;i<variablesNo;i++)
		{
			if(checkvariable1invariablenames==varNames[i])
			{
				operand1index =i;
			}
		    if(checkvariable2invariablenames==varNames[i])
			{
				operand2index =i;
			}
		}

		

		if( operand1index !=-1 && operand2index!=-1)
		{
				string operand1content=varContent[operand1index] ;
	            double contentofoperand1inDouble = atof(operand1content.c_str());
	            string operand2content=varContent[operand2index] ;
	            double contentofoperand2inDouble = atof(operand2content.c_str());
	
	         if (s.at(placeofspecial)=='+')
	      {return contentofoperand1inDouble + contentofoperand2inDouble;}
	         else if(s.at(placeofspecial)=='-')
	      {return contentofoperand1inDouble - contentofoperand2inDouble;}
	         else if(s.at(placeofspecial)=='*')
	      {return contentofoperand1inDouble * contentofoperand2inDouble;}
	         else if(s.at(placeofspecial)=='/')
	      {return contentofoperand1inDouble / contentofoperand2inDouble;}
	         else if(s.at(placeofspecial)=='^')
	      {return pow(contentofoperand1inDouble,contentofoperand2inDouble);}

		}



		else if( operand1index ==-1 && operand2index==-1) 
		{
			//if the two inputs are numbers

				string operand1asnumber= s.substr(0,placeofspecial) ;
	            double operand1asnumbertodouble = atof(operand1asnumber.c_str());
	            string operand2asnumber= s.substr(placeofspecial+1,s.length()) ;
	            double operand2asnumbertodouble = atof(operand2asnumber.c_str());

	        if (s.at(placeofspecial)=='+')
	     {return operand1asnumbertodouble + operand2asnumbertodouble;}
	        else if(s.at(placeofspecial)=='-')
	     {return operand1asnumbertodouble - operand2asnumbertodouble;}
	        else if(s.at(placeofspecial)=='*')
	     {return operand1asnumbertodouble * operand2asnumbertodouble;}
	        else if(s.at(placeofspecial)=='/')
	     {return operand1asnumbertodouble / operand2asnumbertodouble;}
	        else if(s.at(placeofspecial)=='^')
	     {return pow(operand1asnumbertodouble,operand2asnumbertodouble);}
				}
		else if (operand1index ==-1  &&  operand2index !=-1)
				{
				string operand1asnumber= s.substr(0,placeofspecial) ;
	            double operand1asnumbertodouble = atof(operand1asnumber.c_str());
				string operand2content=varContent[operand2index] ;
	            double contentofoperand2inDouble = atof(operand2content.c_str());
			if (s.at(placeofspecial)=='+')
	     {return operand1asnumbertodouble + contentofoperand2inDouble;}
			if (s.at(placeofspecial)=='-')
	     {return operand1asnumbertodouble - contentofoperand2inDouble;}
			if (s.at(placeofspecial)=='*')
	     {return operand1asnumbertodouble * contentofoperand2inDouble;}
			if (s.at(placeofspecial)=='/')
	     {return operand1asnumbertodouble / contentofoperand2inDouble;}
			if (s.at(placeofspecial)=='^')
	     {return pow(operand1asnumbertodouble,contentofoperand2inDouble);}
				}
	   else if(operand1index !=-1  &&  operand2index ==-1)
		{
			    string operand1content=varContent[operand1index] ;
	            double contentofoperand1inDouble = atof(operand1content.c_str());
				string operand2asnumber= s.substr(placeofspecial+1,s.length()) ;
	            double operand2asnumbertodouble = atof(operand2asnumber.c_str());

		    if (s.at(placeofspecial)=='+')
	     {return contentofoperand1inDouble + operand2asnumbertodouble;}
			if (s.at(placeofspecial)=='-')
	     {return contentofoperand1inDouble - operand2asnumbertodouble;}
			if (s.at(placeofspecial)=='*')
	     {return contentofoperand1inDouble * operand2asnumbertodouble;}
			if (s.at(placeofspecial)=='/')
	     {return contentofoperand1inDouble / operand2asnumbertodouble;}
			if (s.at(placeofspecial)=='^')
	     {return pow(contentofoperand1inDouble,operand2asnumbertodouble);}
		
		}


	}

}

