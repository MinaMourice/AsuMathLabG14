#include <bits/stdc++.h>
using namespace std;


void errors_handler(string input);
void go_space(string &input , char ch);
bool validate_brackets(string input);
void matrix_limit(string &input);
string get_name(string input);
void sequence_operators(string input);
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
	// check sequenced operators 
	sequence_operators(input);
	
	// guarantee every special char have spaces before and after
	string matrix_name =  get_name(input);
	matrix_limit(input);
	matrix_data[matrix_name].first = input;
	
	string special_chars = ";][=+-)(/^'";
	string mat_varNames = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
	size_t mat_found = input.find_first_of(mat_varNames);
	while (mat_found!=std::string::npos) {
		string finder = "";
		finder += input[mat_found];
		if(matrix_data[finder].second.first == 0) throw("unavailable variable input");

		mat_found=input.find_first_of(mat_varNames,mat_found+1);
	}
	cout << input << "\n";
	input = "a = " + input;
	if(validate_brackets(input) == false) throw("invalid input");
	for(int i = 0 ; i < special_chars.size() ; i++){
		go_space(input , special_chars[i]);
	}



	char str[1023]; strcpy(str , input.c_str());
	char *parser = strtok(str , " =[]");

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
	matrix_data[matrix_name].second.first = rows;
	matrix_data[matrix_name].second.second = cols;

	// //show all matrix_data 
	map<string, pair<string, pair<int,int> > > :: iterator mapit;
	for(mapit = matrix_data.begin() ; mapit != matrix_data.end() ; mapit++){
		cout << "matrix(" << mapit->first << ")rows: " << mapit->second.second.first << ",cols: " << mapit->second.second.second << " |->";
		cout << mapit->second.first << "\n";
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

void matrix_limit(string &input){
	int left = 0 , right = 0;
	string ret = "";
	for(int i = 0 ; i < input.size() ; i++){
		if(input[i] == '['){
			left = i;
			break;
		}
	}
	for(int i = 0 ; i < input.size() ; i++){
		if(input[i] == ']')
			right = i;
	}
	for(int i = left  ; i <= right ; i++)
		ret += input[i];
	input = ret;
}

string get_name(string input){
	string ret;
	int count_sign = 0;
	for(int i = 0 ; i < input.size() ; i++)
		if(input[i] == '=') count_sign += 1;
	if(count_sign != 1) throw("invalid input");
	for(int i = 0 ; i < input.size() ; i++){
		if(input[i] == '=') break;
		if(input[i] != ' ') ret += input[i];
	}
	return ret;
}

void sequence_operators(string input){
	map<char,int> mat_checker;
	mat_checker['/'] = 1 , mat_checker['-'] = 1 , mat_checker['+'] = 1 , mat_checker['*'] = 1;
	for(int i = 1 ; i < input.size() ; i++){
		char ch = input[i] , prev_ch = input[i-1];
		if(mat_checker[ch] == 1 && mat_checker[prev_ch] == 1) throw("sequenced operators");
	}
}
