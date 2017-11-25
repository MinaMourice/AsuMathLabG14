#include "cmatrix.h"
#include "solve.h"


void defSpecialMat(string s, string varNames[100], string varContent[100], string outToFile[100] , int& variablesNo, int& outFileSize) {} // Hanaa /* Define special matrices like B = rand(2, 3), C = eye(2, 4), d = F = ones(2, 3) and g = zeros(5, 4) */
#include "cmatrix.h"
#include "solve.h"


bool isFloat( string myString ) {
    istringstream iss(myString);
    float f;
    iss >> noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail(); 
}
	
void defMat(string s, string varNames[100], string varContent[100], string outToFile[100] , int& variablesNo, int& outFileSize)
{
	string varnames[100];
	string array[100],text,token ,token2, replace;
	size_t Equal_pos,found_var,found_par1,found_par2,semi_colon,semi_colon_2,semi_colon_no,colon,token2_pos,final_semi_colon;
	int flag =0 ,c=0,replaced_pos,diff,Equal_no;

	Equal_no =count(s.begin(), s.end(), '=');
	for(int b = 0 ; b<Equal_no ; b++)
	{
		Equal_pos=s.find_first_of('=');
		varnames[variablesNo]=s.substr(0,Equal_pos);
		s.erase(0,Equal_pos+1);
		variablesNo++;
	}
//	cout<<s<<endl;
	
	for(int i=0;i<variablesNo;i++)
	{
		for(int count=0;count<variablesNo;count++)
		{
			found_var = varContent[i].find_first_of(varNames[count]);
    		while(found_var!=string::npos)
   			{
    			varContent[i].replace(found_var,varNames[count].length(),varContent[count]);
    			cout<<varContent[i]<<endl;
    			found_var=varContent[i].find_first_of(varNames[i],found_var+1);
			}
		}
	}
	
	for(int i=0;i<variablesNo;i++)
	{
		found_var = s.find(varNames[i]);
    	while(found_var!=string::npos)
    	{
			//cout << "first 'var' found at: " << found_var << '\n';
    		s.replace(found_var,varNames[i].length(),varContent[i]);
    		found_var=s.find_first_of(varNames[i],found_var+1);
		}
	}


	// find '[' & ']' & what is between them
	
	if(s.find_first_of("[")!=string::npos&&s.find_last_of("]")!=string::npos){
	
	s.erase(s.find_first_of("["),1);
	s.erase(s.find_last_of("]"),1);
	found_par1 = s.find_first_of("[");
	found_par2 = s.find_first_of("]");


//	cout<<s<<endl;
	 while(found_par1!=string::npos&& found_par2!=string::npos)
	 {
	 	
	 	//cout<<found_par1<<" "<<found_par2<<endl;
	 	
	 	semi_colon=s.find(";",found_par1);
	 	colon=s.find_first_of(",",found_par1);
	 	//cout<<semi_colon<<endl;
	 	if( found_par1<semi_colon&&semi_colon< found_par2)
	 	{
	 	//	cout<<count_1<<endl;
	 	//	if(count_1==0)
	 	if(flag==0){
			 replaced_pos=found_par1;flag=1;}
	 		text = s.substr(found_par1+1,found_par2-found_par1-1);
	 		istringstream iss(text);
	 		//cout<<text<<endl;
	 		semi_colon_no =count(s.begin()+found_par1, s.begin()+found_par2, ';');
	 	//	cout<<semi_colon_no<<endl;
	 		for(int i=0;i<=semi_colon_no;i++)
	 		{
	 			getline(iss, token, ';');
	 			array[c]+=" "+ token;
        		c++;
        		
		 	}
		 	
		 	//cout<<array[0]<<";"<<array[1]<<endl;
		 	
		 		
		 	colon=s.find_first_of(",",found_par2);
		 	diff=colon-found_par2;
		 //	cout<<diff<<endl;
		 	if(diff>4||diff<0)
			{	
		 		for(int i =0 ;i<c;i++)
		 		{
		 			if(i!=c-1)
		 			replace+=array[i]+";";
		 			else
		 			replace+=array[i];
				}
				//cout<<replace<<endl;
		 		s.replace(replaced_pos,found_par2-replaced_pos+1,replace);//replace array
		 		//cout<<s<<endl;
		 		replace.clear();
		 		flag=0;
		 		//cout<<replaced_pos<<endl;
		 		for(int i=0;i<c;i++)
		 		array[i].clear();
		 		//cout<<array[0]<<endl;
				 //empty arrray & replace	
			}
		 	c=0;
		}
		else if( found_par1<colon&&colon< found_par2)
		s.erase(colon,1);
		else 
		{
			s.erase(found_par1,1);
			s.erase(found_par2-1,1);
		}

		found_par1=s.find_first_of("[",found_par1+1);
		found_par2=s.find_first_of("]",found_par2+1);
		
	 }

istringstream iss(s);
 while (getline(iss, token, ';'))
    {
        istringstream iss2(token);
        while(getline(iss2,token2,' '))
        {
        	//cout<<token2<<endl;
        	if (  !isFloat(token2)  &&token2.find_first_not_of(' ') != string::npos)
        	{
        		token2_pos=s.find(token2);
        		s.replace(token2_pos, token2.length(), "temp");
			}
		}
    }
cout<<"["<<s<<"]"<<endl;
s="["+s+"]";}
	final_semi_colon=s.find_first_of(";",s.find_last_of("]"));
	if(final_semi_colon==string::npos)	
	{
		cout<<s<<endl;
	}
	for(int b = 0 ; b<Equal_no ; b++)
	{
		varContent[variablesNo]=s;
	}
	
	

}
 // Mina Mouries /* Define matrices that contain variables like b = [1; 2] a = [5] A = a = [1 3 4 5 a sin(0.4); 3 2 3 4 [9 2]; [2 3 4 2 1; 2 3 4 5 6], b] i.e: any matrix other than special matrices defined above*/
void doOperatrion(string s, string varNames[100], string varContent[100], string outToFile[100] , int& variablesNo, int& outFileSize) {} // Peter /* Will take a string input like A = 3 * sin(0.2) + d (9 + b * exp(3)) where d and b might be matrices*/

void printToFile(string file, string outToFile[100] , int& outFileSize) {} // Beshoy /* Takes the file name as input and prints all the data in it */

void decode(string s, string varNames[100], string varContent[100], string outToFile[100] , int& variablesNo, int& outFileSize) {} // Beshoy /* Takes line by line from main function and determine how to work on each line */
