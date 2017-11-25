#include "cmatrix.h"
#include "solve.h"
#include "decode.h"


void defSpecialMat(string s, string varNames[100], string varContent[100], int& variablesNo) {
	string Names[100];int NR;int NC;int x=0;int h=0;
	int i=s.find('='); int initialization;
	if (i-1==s.find(' ')) throw("Error");
	Names[variablesNo]=s.substr(0,i);
	varNames[variablesNo]= s.substr(0,i);
	for (int k=0;k<variablesNo;k++)
	{
		if(Names[k]==varNames[variablesNo])
		{   
			variablesNo=k;
			CMatrix content (NR,NC,initialization,0.0);
			 varContent[variablesNo]=varContent[k]=content.getOriginalString();
			 variablesNo--;varNames[k].clear();varContent[k].clear(); break;
			 h=1;
		}
	}
	int j=s.find('(');
	string initial =s.substr(i+1,j-2);
	 NR=atoi(s.substr(j+1,s.find(',')-1).c_str());
	 NC=atoi (s.substr(s.find(',')+1,s.find(')')-1).c_str());

	if (initial[0]=='Z'||initial[0]=='z') initialization=0;
	else if (initial[0]=='O'||initial[0]=='o') initialization=1;
	else if (initial[0]=='E'||initial[0]=='e') 
		{
			if(NR != NC)
			{throw ("Invalid Matrix Dimension");
			variablesNo=variablesNo-1;
			}
			else initialization=2;
		}
	else if (initial[0]=='R'||initial[0]=='r') initialization=3;
	else initialization=4;
	
	
	if(h==0){
	 CMatrix content (NR,NC,initialization,0.0);
	 varContent[variablesNo]=content.getOriginalString();}

     std::size_t found1 = s.find(';');
	  if (found1!=std::string::npos)
	  {
		  x=1;
	  }
	  if(x==0)
	  {
		  cout<<varNames[variablesNo]<<"="<<varContent[variablesNo]<<"\n";
		 // print(s,varNames,varContent,variablesNo);
	  }
	
	variablesNo++;
	


}
