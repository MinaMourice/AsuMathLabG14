#include "cmatrix.h"
#include "solve.h"
#include "decode.h"


void defSpecialMat(string s, string varNames[100], string varContent[100], int& variablesNo) {
	int NR; int NC; int x=0; int h=0; int initialization; string str;
	
	int i=s.find('='); 
	if (i-1==s.find(' ')) 
		 str= s.substr(0,i-1);
	else
		 str=s.substr(0,i);
	int j=s.find('(');
	string initial =s.substr(i+1,j-2);
	NR=atoi(s.substr(j+1,s.find(',')-1).c_str());
	NC=atoi (s.substr(s.find(',')+1,s.find(')')-1).c_str());

	if (initial[0]=='Z'||initial[0]=='z') initialization=0;
	else if (initial[0]=='O'||initial[0]=='o') initialization=1;
	else if (initial[0]=='E'||initial[0]=='e') 
		{
			if(NR != NC)
			{
			variablesNo=variablesNo-1;
			throw ("Invalid Matrix Dimension");
			}
			else initialization=2;
		}
	else if (initial[0]=='R'||initial[0]=='r') initialization=3;
	else initialization=4;
	
		for (int k=0;k<variablesNo;k++)
	{
		if(str==varNames[k])
		{   
			 variablesNo=k;
			 CMatrix content (NR,NC,initialization,0.0);
			 varContent[variablesNo]=varContent[k]=content.getOriginalString();
			 //variablesNo--;
			 //varNames[k].clear();varContent[k].clear(); 
			 h=1;
			 break;
		}
		
	}
	if(h==0){
    varNames[variablesNo]= str;
	 CMatrix content (NR,NC,initialization,0.0);
	 varContent[variablesNo]=content.getOriginalString();}

     std::size_t found1 = s.find(';');
	  if (found1!=std::string::npos)
	  {
		  x=1;
	  }
	  if(x==0)
	  {
		  //cout<<varNames[variablesNo]<<"="<<varContent[variablesNo]<<"\n";
		  string var= varNames[variablesNo]+"="+varContent[variablesNo];
		  print(var,varNames,varContent,variablesNo);
	  }
	
	variablesNo++;
	
}
