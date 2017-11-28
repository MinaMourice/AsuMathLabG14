#include "cmatrix.h"
#include "solve.h"

void defSpecialMat(string s, string varNames[100], string varContent[100], string outToFile[100] , int& variablesNo, int& outFileSize) {}
// Hanaa /* Define special matrices like B = rand(2, 3), C = eye(2, 4), d = F = ones(2, 3) and g = zeros(5, 4) */

void defMat(string s, string varNames[100], string varContent[100], string outToFile[100] , int& variablesNo, int& outFileSize) {} 
// Mina Mouries /* Define matrices that contain variables like b = [1; 2] a = [5] A = a = [1 3 4 5 a sin(0.4); 3 2 3 4 [9 2]; [2 3 4 2 1; 2 3 4 5 6], b] i.e: any matrix other than special matrices defined above*/

void doOperatrion(string s, string varNames[100], string varContent[100], string outToFile[100] , int& variablesNo, int& outFileSize)
{
	string tempstr;
	//removing spaces
	for(int string_index=0 ; string_index < s.length() ; string_index++)
	{
		if(s[string_index]== ' ') s.replace(string_index , s.length()-string_index ,s.substr(string_index+1,s.length()-string_index-1));
	}
	// sperating it to 2 arrays , Parameters array and operators array
	string parameters[100] , operations[100] ;
	string operators = "=+-*/.^'!()";
	int stack_index=0;
	for(int string_index =0 ; string_index<s.length() ; string_index++)
	{
		if(s[string_index] == ' ') continue;
		//parameters[stack_index]="";  operations[stack_index]=""; //initialinzing the values of stack elements
		bool operator_exist=false;
		bool nextoperator_exist= false;
		bool nextisdigit = false ;
		if(s[string_index] == '.') {if(isdigit(s[string_index+1])==1) nextisdigit= true ; }
		for(int checking_index=0 ; checking_index<operators.length();checking_index++)
		{
			if(s[string_index]==operators[checking_index]) operator_exist=true;
			if(s[string_index+1]==operators[checking_index]) nextoperator_exist=true;
		}

		if(operator_exist==true)
		{ 
			if(s[string_index] == '.') parameters[stack_index].insert(parameters[stack_index].end() , s[string_index]);
			else operations[stack_index].insert(operations[stack_index].end() , s[string_index]);
			if(s[string_index]!='.'||s[string_index]=='!'||s[string_index]==operators[7]) stack_index++; 
		}
		else
		{
			parameters[stack_index].insert(parameters[stack_index].end() , s[string_index]);
			if(nextoperator_exist==true && nextisdigit==false && s[string_index] != '.'&& s[string_index+1] != '.' ) stack_index++;
		}
	}
	//solve factorial or transpose operations
	for (int index=0 ; index<stack_index ; index++)
	{
		if(operations[index]=="!"||operations[index]=="'") 
		{
			tempstr=solve(parameters[index-1]+operations[index],&varNames[100], &varContent[100], variablesNo);
			//tempstr= parameters[index-1]+operations[index];
			//cout<<tempstr<<endl;
			parameters[index-1]=tempstr;
			operations[index]="";
			//cout<<"----->"<<operations[index]<<endl;
			//remove the empty elements in the stack
			for(int WBindex=index ; WBindex<stack_index;WBindex++)
			{
				operations[WBindex]=operations[WBindex+1];
				parameters[WBindex]=parameters[WBindex+1];
			}
			stack_index--;
		}
	}

	//slove braces
	// if we find "(" @ index and index+2=")" then this might be sins ,cos ,.. etc 
	for (int index=0 ; index<stack_index ; index++)
	{
		if(operations[index]=="(" && operations[index+2]==")") 
		{
			tempstr=solve(parameters[index-1]+operations[index]+parameters[index+1]+operations[index+2],&varNames[100], &varContent[100], variablesNo);
			//tempstr=parameters[index-1]+operations[index]+parameters[index+1]+operations[index+2];
			//cout<<tempstr<<endl;
			parameters[index-1]=tempstr;
			operations[index]="";
			parameters[index+1]="";
			operations[index+2]="";
			for(int WBindex=index ; WBindex<stack_index;WBindex++)
			{
				operations[WBindex]=operations[WBindex+3];
				parameters[WBindex]=parameters[WBindex+3];
			}
			stack_index--;
		}
		else if (operations[index]=="("&&(operations[index]=="*"||operations[index]=="/"))
		{
			for(int closingBraceIndex=index ; closingBraceIndex<stack_index ; closingBraceIndex++)
			{
				if(operations[closingBraceIndex]==")")
				{
				
					

				}
			}
		}
	}
	

} // Peter /* Will take a string input like A = 3 * sin(0.2) + d (9 + b * exp(3)) where d and b might be matrices*/

void printToFile(string file, string outToFile[100] , int& outFileSize) {} 
// Beshoy /* Takes the file name as input and prints all the data in it */

void decode(string s, string varNames[100], string varContent[100], string outToFile[100] , int& variablesNo, int& outFileSize) {} 
// Beshoy /* Takes line by line from main function and determine how to work on each line */
