void print(string s, string varNames[100], string varContent[100], int variableNo) {
	for (int index = 0; index < variableNo; index++) {
		if (varNames[index] == s) {
			cout << varNames << "=" << varContent[index].getString();
			return;
		}
	}

}
void decode(string info, string varNames[100], string varContent[100],int& variableNo) {
	int defMatFlag = 0;
	for (int charIndex = 0; charIndex < info.length(); charIndex++) {
		if (info[charIndex] == '[') {
			defMatFlag = 1;
			//defMat(info, varNames, varContent, variableNo);
			cout << "send: " << info << "to defMat" << endl;
			break;
		}
	}
	if (defMatFlag == 0) {
		if (info.find("rand") != string::npos || info.find("eye") != string::npos || info.find("ones") != string::npos || info.find("zeros") != string::npos) {
			//defSpecialMat(info, varNames, varContent, variableNo);
			cout << "send: " << info << "to defSpecialMat" << endl;
		}
		else if(info.find('=') != string::npos){
			//doOperation(info, varNames, varContent, variableNo);
			cout << "send: " << info << "to doOperation" << endl;
		}
		else {
			print(info, varNames, varContent, variableNo);
		}
	}
}
