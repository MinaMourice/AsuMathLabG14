#include <bits/stdc++.h>
using namespace std;


void errors_handler(string input);
map<string, pair<string, pair<int,int> > > matrix_data;

int main(){
	try{
		string line;
		cout << ">>"; 
		while(getline(cin, line)){
			errors_handler(line);
			cout << ">>"; 
		}
	}catch(const char* param){
		cout << "Error: " << param << "\n";
	}
}
void errors_handler(string input){
	// guarantee every semicolon have spaces before and after
	int index = 0;
	while (true){
	     index = input.find(";", index);
	     if (index == string::npos) break;
	     input.replace(index, 1, " ; "); index += 3;
	}
	
	char str[1023]; strcpy(str , input.c_str());
	char *parser = strtok(str , " =");
	matrix_data[parser].first = input;
	char *matrix_var = parser;
	int rows = 1 , cols = -1;
	set<int> checker;
	while (true) {
	    parser = strtok(NULL, " =[]");
	    if(parser == NULL) break;
	    cols += 1;
	    if(!strcmp(parser, ";")){
	      checker.insert(cols);
	      rows += 1;
	      cols = 0;
	    }
	}
	checker.insert(cols);
	if(checker.size() != 1) throw("Invalid matrix dimension");
	matrix_data[matrix_var].second.first = rows;
	matrix_data[matrix_var].second.second = cols;
	// //show all matrix_data 
	map<string, pair<string, pair<int,int> > > :: iterator mapit;
	for(mapit = matrix_data.begin() ; mapit != matrix_data.end() ; mapit++){
		cout << "matrix(" << mapit->first << ")rows:  " << mapit->second.second.first << ",cols: " << mapit->second.second.second << "\n";
	}
}