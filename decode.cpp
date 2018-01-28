void doOperation(string& s, string varNames[100], string varContent[100], int& variablesNo)
{
	string tempstr;
	//int cursor=0;
	//removing all spaces from string
	for (int string_index = 0; string_index < s.length(); string_index++)
	{
		if (s[string_index] == ' ') s.replace(string_index, s.length() - string_index, s.substr(string_index + 1, s.length() - string_index - 1));
	}
	// sperating it to 2 arrays , Parameters array and operators array
	string parameters[100], operations[100];
	string operators = "=+-*/.^'!()&|;\\";
	int stack_index = 0;
	for (int string_index = 0; string_index<s.length(); string_index++)
	{
		if (s[string_index] == ' ') continue;
		//parameters[stack_index]="";  operations[stack_index]=""; //initialinzing the values of stack elements
		bool operator_exist = false;
		bool nextoperator_exist = false;
		bool prevoperator_exist = false;
		bool nextisdigit = false;
		if (s[string_index] == '.') { if (isdigit(s[string_index + 1])) nextisdigit = true; }
		for (int checking_index = 0; checking_index<operators.length(); checking_index++)
		{
			if (s[string_index] == operators[checking_index]) operator_exist = true;
			if (s[string_index + 1] == operators[checking_index]) nextoperator_exist = true;
			if (string_index != 0) { if (s[string_index - 1] == operators[checking_index]) prevoperator_exist = true; }
		}

		if (operator_exist == true)
		{
			if ((s[string_index] == '.'&&nextisdigit == true) || (s[string_index] == '-'&& s[string_index - 1] != '.' && (prevoperator_exist == true &&/* s[string_index - 1] == '='&&*/s[string_index - 1] != ')'))) parameters[stack_index].insert(parameters[stack_index].end(), s[string_index]);
			else
			{
				if (s[string_index] == '.'&&nextisdigit == false)stack_index++;
				operations[stack_index].insert(operations[stack_index].end(), s[string_index]);
			}
			if (s[string_index - 1] == '.' /*&& operator_exist == true */) stack_index++;
			else if (s[string_index] != '.' &&
				((s[string_index] == '!' || s[string_index] == ';' || s[string_index] == '\'') ||
				(s[string_index] != '-' && (prevoperator_exist == false || s[string_index - 1] == '=' || s[string_index - 1] == ')') && s[string_index + 1] != '.') ||
					(s[string_index] == '-' &&s[string_index - 1] != '=' && (prevoperator_exist == false /*|| s[string_index - 1] == '=' */ || s[string_index - 1] == ')')) ||
					(s[string_index] == '(')
					)) stack_index++;
		}
		else
		{
			parameters[stack_index].insert(parameters[stack_index].end(), s[string_index]);
			if (nextoperator_exist == true && nextisdigit == false && s[string_index] != '.'&& s[string_index + 1] != '.') stack_index++;
			if (string_index == s.length() - 1) stack_index++;
		}

	}
	///////////////////
	//cout << stack_index << endl;

	/*for (int i = 0; i < stack_index; i++)
	{
		cout << parameters[i] << "----->" << operations[i] << endl;
	}*/
	///////////////////

	//solve factorial or transpose operations
	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "!" || operations[index] == "'")
		{
			tempstr = solve(parameters[index - 1] + operations[index], varNames, varContent, variablesNo);
			parameters[index - 1] = tempstr;
			operations[index] = "";
			//remove the empty elements in the stack
			for (int WBindex = index; WBindex<stack_index; WBindex++)
			{
				operations[WBindex] = operations[WBindex + 1];
				parameters[WBindex] = parameters[WBindex + 1];
			}
			stack_index--;
		}
	}

	//slove arguments

	//solve arguments "(" do some operations")"

	bool more_arguments = false;
	do
	{
		for (int index = stack_index - 1; index>0; index--) //index is the index of opening arguments
		{
			bool simpletrignometricfn_exist = false;
			if (operations[index] == "("/*&&(operations[index]=="*"||operations[index]=="/")*/)
			{
				for (int closingArgumentIndex = index; closingArgumentIndex<stack_index; closingArgumentIndex++)
				{
					if (operations[closingArgumentIndex] == ")")
					{
						bool argument_exist = false;
						do
						{
							//do power operation
							for (int solveArgumentindex = index; solveArgumentindex<closingArgumentIndex; solveArgumentindex++)
							{
								if (operations[solveArgumentindex] == "^" || operations[solveArgumentindex] == ".^")
								{
									tempstr = solve(parameters[solveArgumentindex - 1] + operations[solveArgumentindex] + parameters[solveArgumentindex + 1], varNames, varContent, variablesNo);
									parameters[solveArgumentindex - 1] = tempstr;
									operations[solveArgumentindex] = "";
									parameters[solveArgumentindex + 1] = "";
									//remove the empty elements in the stack
									for (int WBindex = solveArgumentindex; WBindex<stack_index; WBindex++)
									{
										operations[WBindex] = operations[WBindex + 2];
										parameters[WBindex] = parameters[WBindex + 2];
									}
									stack_index -= 2;
									closingArgumentIndex -= 2;
									solveArgumentindex -= 3;
								}
							}
							// if we find "(" @ index and index+2=")" then it might be sins ,cos ,.. etc 
							simpletrignometricfn_exist = false;
							for (int solveArgumentindex = index; solveArgumentindex<closingArgumentIndex; solveArgumentindex++)
							{
								if (operations[solveArgumentindex] == "(" && operations[solveArgumentindex + 2] == ")")
								{
									tempstr = solve(parameters[solveArgumentindex - 1] + operations[solveArgumentindex] + parameters[solveArgumentindex + 1] + operations[solveArgumentindex + 2], varNames, varContent, variablesNo);
									parameters[solveArgumentindex - 1] = tempstr;
									operations[solveArgumentindex] = "";
									parameters[solveArgumentindex + 1] = "";
									operations[solveArgumentindex + 2] = "";
									//remove the empty elements in the stack
									for (int WBindex = solveArgumentindex; WBindex<stack_index; WBindex++)
									{
										operations[WBindex] = operations[WBindex + 3];
										parameters[WBindex] = parameters[WBindex + 3];
									}
									stack_index -= 3;

									if (solveArgumentindex == index&&closingArgumentIndex == index + 2) { simpletrignometricfn_exist = true; break; }
									index -= 3;
								}
							}
							if (simpletrignometricfn_exist) break;
							//do mul and div operation
							for (int solveArgumentindex = index; solveArgumentindex<closingArgumentIndex; solveArgumentindex++)
							{

								if (operations[solveArgumentindex] == "*" || operations[solveArgumentindex] == "/" || operations[solveArgumentindex] == ".*" || operations[solveArgumentindex] == "./" || operations[index] == "\\" || operations[index] == ".\\")
								{
									tempstr = solve(parameters[solveArgumentindex - 1] + operations[solveArgumentindex] + parameters[solveArgumentindex + 1], varNames, varContent, variablesNo);
									parameters[solveArgumentindex - 1] = tempstr;
									operations[solveArgumentindex] = "";
									parameters[solveArgumentindex + 1] = "";
									//remove the empty elements in the stack
									for (int WBindex = solveArgumentindex; WBindex<stack_index; WBindex++)
									{
										operations[WBindex] = operations[WBindex + 2];
										parameters[WBindex] = parameters[WBindex + 2];
									}
									stack_index -= 2;
									closingArgumentIndex -= 2;
									solveArgumentindex -= 3;



								}
							}

							//do add and sub operations
							for (int solveArgumentindex = index; solveArgumentindex<closingArgumentIndex; solveArgumentindex++)
							{
								if (operations[solveArgumentindex] == "+" || operations[solveArgumentindex] == "-" || operations[solveArgumentindex] == ".+" || operations[solveArgumentindex] == ".-")
								{
									tempstr = solve(parameters[solveArgumentindex - 1] + operations[solveArgumentindex] + parameters[solveArgumentindex + 1], varNames, varContent, variablesNo);
									parameters[solveArgumentindex - 1] = tempstr;
									operations[solveArgumentindex] = "";
									parameters[solveArgumentindex + 1] = "";
									//remove the empty elements in the stack
									for (int WBindex = solveArgumentindex; WBindex<stack_index; WBindex++)
									{
										operations[WBindex] = operations[WBindex + 2];
										parameters[WBindex] = parameters[WBindex + 2];
									}
									stack_index -= 2;
									closingArgumentIndex -= 2;
									solveArgumentindex -= 3;
								}
							}

							//do bitwise and , or operations
							for (int solveArgumentindex = index; solveArgumentindex<closingArgumentIndex; solveArgumentindex++)
							{
								if (operations[solveArgumentindex] == "&" || operations[solveArgumentindex] == "|")
								{

									tempstr = solve(parameters[solveArgumentindex - 1] + operations[solveArgumentindex] + parameters[solveArgumentindex + 1], varNames, varContent, variablesNo);
									parameters[solveArgumentindex - 1] = tempstr;
									operations[solveArgumentindex] = "";
									parameters[solveArgumentindex + 1] = "";
									//remove the empty elements in the stack
									for (int WBindex = solveArgumentindex; WBindex<stack_index; WBindex++)
									{
										operations[WBindex] = operations[WBindex + 2];
										parameters[WBindex] = parameters[WBindex + 2];
									}
									stack_index -= 2;
									closingArgumentIndex -= 2;
									solveArgumentindex -= 3;
								}
							}
							for (int argumentindex = index; argumentindex<closingArgumentIndex; argumentindex++)
							{
								if (operations[argumentindex] != ""&&operations[argumentindex] != "("&&operations[argumentindex] != ")")  argument_exist = true;
								else argument_exist = false;
							}
						} while (argument_exist);


						// testing for loop
						/*tempstr="";
						for (int testindex=1 ; testindex < closingArgumentIndex-index ; testindex++)
						{
						if(testindex%2==0) tempstr.insert(tempstr.length() , operations[index+testindex]);//BracesDoOpearation[0].insert(BracesDoOpearation[0].end() , parameters[index+testindex]);
						else tempstr.insert(tempstr.length() , parameters[index+testindex]);
						}
						cout<<"parsing is"<<tempstr<<endl;*/


						if (parameters[index - 1] == "") //if not sin or cos remove arguments "(   )"
						{
							//replacing old by new data and remove unused elements from stack
							parameters[index] = parameters[index + 1];
							for (int removeindex = 0; removeindex < closingArgumentIndex - index; removeindex++)
							{
								if (removeindex % 2 == 0) operations[index + removeindex] = "";
								else parameters[index + removeindex] = "";
							}




							//remove the empty elements in the stack


							for (int WBindex = index + 1; WBindex<stack_index; WBindex++)
							{
								operations[WBindex] = operations[WBindex + (closingArgumentIndex - index)];
								parameters[WBindex] = parameters[WBindex + (closingArgumentIndex - index)];
							}
							//stack_index -= (closingArgumentIndex - index);
							stack_index -= 2;
							index -= closingArgumentIndex - index;

							break;
						}
						if (simpletrignometricfn_exist) break;
					}
				}
			}
			if (simpletrignometricfn_exist) break;
		}

		for (int argumentindex = 0; argumentindex<stack_index; argumentindex++)
		{
			if (/*operations[argumentindex] != ""&&*/operations[argumentindex] == "(" || operations[argumentindex] == ")") { more_arguments = true; break; }
			else more_arguments = false;
		}
	} while (more_arguments);



	// if we find "(" @ index and index+2=")" then it might be sins ,cos ,.. etc 
	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "(" && operations[index + 2] == ")")
		{
			tempstr = solve(parameters[index - 1] + operations[index] + parameters[index + 1] + operations[index + 2], varNames, varContent, variablesNo);
			parameters[index - 1] = tempstr;
			operations[index] = "";
			parameters[index + 1] = "";
			operations[index + 2] = "";
			//remove the empty elements in the stack
			for (int WBindex = index; WBindex<stack_index; WBindex++)
			{
				operations[WBindex] = operations[WBindex + 3];
				parameters[WBindex] = parameters[WBindex + 3];
			}
			stack_index -= 3;
			index -= 3;
		}
	}



	//slove simple opeartions like * , / , ... etc
	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "^" || operations[index] == ".^")
		{
			tempstr = solve(parameters[index - 1] + operations[index] + parameters[index + 1], varNames, varContent, variablesNo);
			//tempstr = parameters[index-1]+operations[index]+parameters[index+1];
			parameters[index - 1] = tempstr;
			operations[index] = "";
			parameters[index + 1] = "";
			//remove the empty elements in the stack
			for (int WBindex = index; WBindex<stack_index; WBindex++)
			{
				operations[WBindex] = operations[WBindex + 2];
				parameters[WBindex] = parameters[WBindex + 2];
			}
			stack_index -= 2;
			index -= 2;
		}
	}
	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "*" || operations[index] == "/" || operations[index] == ".*" || operations[index] == "./" || operations[index] == "\\" || operations[index] == ".\\")
		{
			tempstr = solve(parameters[index - 1] + operations[index] + parameters[index + 1], varNames, varContent, variablesNo);
			//tempstr = parameters[index-1]+operations[index]+parameters[index+1];
			parameters[index - 1] = tempstr;
			operations[index] = "";
			parameters[index + 1] = "";
			//remove the empty elements in the stack
			for (int WBindex = index; WBindex<stack_index; WBindex++)
			{
				operations[WBindex] = operations[WBindex + 2];
				parameters[WBindex] = parameters[WBindex + 2];
			}
			stack_index -= 2;
			index -= 2;
		}
	}
	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "+" || operations[index] == "-" || operations[index] == ".+" || operations[index] == ".-")
		{
			//cout<<parameters[index - 1] + operations[index] + parameters[index + 1]<<endl;
			tempstr = solve(parameters[index - 1] + operations[index] + parameters[index + 1], varNames, varContent, variablesNo);
			//tempstr = parameters[index-1]+operations[index]+parameters[index+1];
			parameters[index - 1] = tempstr;
			operations[index] = "";
			parameters[index + 1] = "";
			//remove the empty elements in the stack
			for (int WBindex = index; WBindex<stack_index; WBindex++)
			{
				operations[WBindex] = operations[WBindex + 2];
				parameters[WBindex] = parameters[WBindex + 2];
			}
			stack_index -= 2;
			index -= 2;
		}
	}

	for (int index = 0; index<stack_index; index++)
	{
		if (operations[index] == "&" || operations[index] == "|")
		{
			//cout<<parameters[index - 1] + operations[index] + parameters[index + 1]<<endl;
			tempstr = solve(parameters[index - 1] + operations[index] + parameters[index + 1], varNames, varContent, variablesNo);
			//tempstr = parameters[index-1]+operations[index]+parameters[index+1];
			parameters[index - 1] = tempstr;
			operations[index] = "";
			parameters[index + 1] = "";
			//remove the empty elements in the stack
			for (int WBindex = index; WBindex<stack_index; WBindex++)
			{
				operations[WBindex] = operations[WBindex + 2];
				parameters[WBindex] = parameters[WBindex + 2];
			}
			stack_index -= 2;
			index -= 2;
		}
	}

	if (stack_index == 4 && operations[1] == "="&&parameters[0] == "temp" && parameters[3]==";")
	{
	s = parameters[2];
	}
	if (stack_index == 4 && operations[1] == "="&&parameters[0] != "temp"&& operations[3] == ";")
	{
		bool variablexsist = false;
		for (int checkingindex = 0; checkingindex<variablesNo; checkingindex++)
		{
			if (varNames[checkingindex] == parameters[0])
			{
				variablexsist = true;
				varNames[checkingindex] = parameters[0];
				varContent[checkingindex] = parameters[2];
				break;
			}
		}
		if (variablexsist == false)
		{
			varNames[variablesNo] = parameters[0];
			varContent[variablesNo] = parameters[2];
			variablesNo++;
		}
	}
	/*else if (stack_index == 3 && operations[1] == "="&&parameters[0] == "temp")
	{
	s = parameters[0] + operations[1] + parameters[2];
	}*/
	else if (stack_index == 3 && operations[1] == "=" &&parameters[0] != "temp")
	{
		//cout << "done";
		bool variablexsist = false;
		for (int checkingindex = 0; checkingindex<variablesNo; checkingindex++)
		{
			if (varNames[checkingindex] == parameters[0])
			{
				variablexsist = true;
				varNames[checkingindex] = parameters[0];
				varContent[checkingindex] = parameters[2];
				break;
			}
		}
		if (variablexsist == false)
		{
			varNames[variablesNo] = parameters[0];
			varContent[variablesNo] = parameters[2];
			variablesNo++;
		}
		print(parameters[0], varNames, varContent, variablesNo);
	}
	else if (stack_index == 2 && operations[1] == ";")
	{
		s = parameters[0];
	}
	else { s = parameters[0]; cout << parameters[0] << endl; }
}
