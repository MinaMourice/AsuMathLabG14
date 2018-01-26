#include <bits/stdc++.h>
using namespace std;


void errors_handler(string input);
void go_space(string &input , char ch);
bool validate_brackets(string input);
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
	// guarantee every special char have spaces before and after
	string special_chars = ";][=+-)(/^'";
	if(validate_brackets(input) == false) throw("invalid input");
	for(int i = 0 ; i < special_chars.size() ; i++){
		go_space(input , special_chars[i]);
	}
	cout << input << "\n";
	char str[1023]; strcpy(str , input.c_str());
	char *parser = strtok(str , " =");
	matrix_data[parser].first = input;
	char *matrix_var = parser;
	int rows = 1 , cols = 0;
	set<int> checker;
	while (true) {
	    parser = strtok(NULL, " =[]");
	    if(parser == NULL) break;
	    cols += 1;
	    if(!strcmp(parser, ";")){
	      cols -= 1;
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

void go_space(string &input , char ch){
	int index = 0;
	while (true){
	     index = input.find(ch, index);
	     if (index == string::npos) break;
	     string out = " ";
	     out += ch;
	     out += " ";
	     input.replace(index, 1, out); index += 3;
	}
}

bool validate_brackets(string input){
	// validate [ ]
	string to_check = "";
	int b_left = 0 , b_right = 0 , b_ans = 0;
	for(int i = 0 ;  i < input.size() ; i++){
		if(b_ans < 0) return false;
		if(input[i] == '[') {to_check += '[', b_right += 1; b_ans += 1;}
		if(input[i] == ']') {to_check += ']', b_left += 1; b_ans -= 1;}
	}
	if(to_check != ""){
		if(b_right != b_left) return false;
	}
	// validate ( )
	to_check = "";
	b_left = 0 ; b_right = 0;
	for(int i = 0 ;  i < input.size() ; i++){
		if(b_ans < 0) return false;
		if(input[i] == '(') {to_check += '(', b_right += 1; b_ans += 1;}
		if(input[i] == ')') {to_check += ')', b_left += 1; b_ans -= 1;}
	}
	if(to_check != ""){
		if(b_right != b_left) return false;
	}

	return true;
}