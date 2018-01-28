CMatrix solveCMatrix(string s, string varNames[100], string varContent[100], int& variablesNo)  
{
	string operand1 , operand2 ;  CMatrix valueOfOperand1 , valueOfOperand2 ;  string numberString ; int operand1index , operand2index;
	int op1const=1 , op2const=1;   int foundString=0;
	int findMatrixString = s.find("[") ; 
	int placeOfOPerator = s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_ ;[]" , 1) ;
	if (placeOfOPerator != std::string::npos)
		{
			if(s.substr(placeOfOPerator+1,1)=="-"&&s.substr(placeOfOPerator,2)!=".-") {op2const=-1; s.erase(placeOfOPerator+1,1);}
			if(s.substr(placeOfOPerator+1,1)=="-"&&s.substr(placeOfOPerator,2)==".-") {op2const=1;}
			if(s.substr(placeOfOPerator+2,1)=="-") {op2const=-1; s.erase(placeOfOPerator+2,1);}
	                if(s.substr(0,1)=="-") {op1const=-1; s.erase(0,1);}
	        placeOfOPerator = s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_ ;[]" , 1) ;
		if (s[placeOfOPerator] == 43 || s[placeOfOPerator] == 45 || s[placeOfOPerator] == 42 || s[placeOfOPerator] == 47 || s[placeOfOPerator] == 92 || s[placeOfOPerator] == 38 || s[placeOfOPerator] == 124)
		{
			
			{
				 if(findMatrixString != std::string::npos)
				{
					foundString=1;   
					int endOfMatrixString = s.find("]",findMatrixString);
					if(findMatrixString<placeOfOPerator)
					{
						valueOfOperand1 = CMatrix(s.substr(findMatrixString,endOfMatrixString+1));
						findMatrixString = s.find("[",endOfMatrixString);
			            if(findMatrixString != std::string::npos)
						{
							endOfMatrixString = s.find("]",findMatrixString);
							valueOfOperand2 = CMatrix(s.substr(findMatrixString,endOfMatrixString));
						}
						else
						{
							int findDoubleOfOp2 = s.find_first_of("0123456789",endOfMatrixString);   
			                int endDoubleOfOp2 = s.find_first_not_of("0123456789", findDoubleOfOp2);
				            if (findDoubleOfOp2 != std::string::npos && s.substr(findDoubleOfOp2-1,1)!="[")
							{
								numberString = s.substr(findDoubleOfOp2, endDoubleOfOp2 != std::string::npos ? endDoubleOfOp2-findDoubleOfOp2 : endDoubleOfOp2) ;
						    	valueOfOperand2 = CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op2const * stod(numberString)) ;
							}
							else
							{
								operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(placeOfOPerator+1,s.length()) ) );
								int foundMatrix2 = varContent [operand2index] . find ("[");
			                    if(foundMatrix2 != std::string::npos)
								{
									valueOfOperand2 = CMatrix (varContent[operand2index]);
			                        valueOfOperand2 = valueOfOperand2 . dotMul( CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op2const) );
								}
							}
						}
					}
					else if(findMatrixString>placeOfOPerator)
					valueOfOperand2 = CMatrix(s.substr(findMatrixString,endOfMatrixString)); 
				}
			
				int findDouble = s.find_first_of("0123456789");   
				int endDouble = s.find_first_not_of("0123456789", findDouble);
				if (findDouble != std::string::npos && s.substr(findDouble-1,1)!="[" && foundString==0)
				{
					if(findDouble<placeOfOPerator)
						{
							//operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(placeOfOPerator+1,s.length()) ) );
				            //valueOfOperand2 = CMatrix (varContent[operand2index]);
							//valueOfOperand2 = valueOfOperand2 . dotMul( CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op2const) );
							numberString = s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) ;
							valueOfOperand1 = CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op1const * stod(numberString)) ;
					    }
					
					else
						{
							//operand1index = distance( varNames, find( varNames , varNames + 100 , s.substr(0,placeOfOPerator) ) ); 
				            //valueOfOperand1 = CMatrix (varContent[operand1index]);
							//valueOfOperand1 = valueOfOperand1 . dotMul( CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op1const) );
							numberString = s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) ;
							valueOfOperand2 = CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op2const * stod(numberString)) ;
					    }
					
				} 
			  

				else if(foundString==0)
				{
					operand1index = distance( varNames, find( varNames , varNames + 100 , s.substr(0,placeOfOPerator) ) );
                    operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(placeOfOPerator+1,s.length()) ) );
					int foundMatrix1 = varContent [operand1index] . find ("[");
					int foundMatrix2 = varContent [operand2index] . find ("[");
					if(foundMatrix2 == std::string::npos) 
						{
							valueOfOperand1 = CMatrix (varContent[operand1index]);
							valueOfOperand1 = valueOfOperand1 . dotMul( CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op1const) );
							valueOfOperand2 = CMatrix (valueOfOperand1.getnR() , valueOfOperand1.getnC() , 4 , stod(varContent[operand2index]));
					    }
					else if(foundMatrix1 == std::string::npos)
						{
							valueOfOperand2 = CMatrix (varContent[operand2index]);
							valueOfOperand2 = valueOfOperand2 . dotMul( CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op2const) );
							valueOfOperand1 = CMatrix (valueOfOperand2.getnR() , valueOfOperand2.getnC() , 4 , stod(varContent[operand1index]));
					    }
					else 
					{
						valueOfOperand1 = CMatrix (varContent[operand1index]);
						valueOfOperand1 = valueOfOperand1 . dotMul( CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op1const) );
						valueOfOperand2 = CMatrix (varContent[operand2index]);
						valueOfOperand2 = valueOfOperand2 . dotMul( CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op2const) );
			        }
					
				}
			 }

			 
			
			if (s[placeOfOPerator] == 43)        return (valueOfOperand1 + valueOfOperand2);
			else if (s[placeOfOPerator] == 45)   return valueOfOperand1 - valueOfOperand2;
			else if (s[placeOfOPerator] == 42)   return valueOfOperand1 * valueOfOperand2;
			else if (s[placeOfOPerator] == 47)   return valueOfOperand1 / valueOfOperand2;
			else if (s[placeOfOPerator] == 92)   return valueOfOperand1.lDiv(valueOfOperand2);
			//else if(s[placeOfOPerator]==38)   return valueOfOperand1 & valueOfOperand2 ;
			//else if(s[placeOfOPerator]==124)  return valueOfOperand1 | valueOfOperand2 ;

		
		}

		else if ((s[placeOfOPerator]) == 40)                        // (
		{
			int p = s.find(")");

			if (s.substr(0, placeOfOPerator) != "pow")
			{
				if(findMatrixString != std::string::npos)
				{
					foundString=1;   
					int endOfMatrixString = s.find("]",findMatrixString);
					valueOfOperand2 = CMatrix(s.substr(findMatrixString,endOfMatrixString+1));
				}
				else if(foundString==0)
				{
					operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(placeOfOPerator+1,p-placeOfOPerator-1) ) );
			        valueOfOperand2 = CMatrix (varContent[operand2index]);
			        valueOfOperand2 = valueOfOperand2 . dotMul( CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op2const) );
				}
			}

			if (s.substr(0, placeOfOPerator) == "sin")          return sin(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "cos")     return cos(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "tan")     return tan(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "sec")     return sec(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "csc")     return csc(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "cot")     return cot(valueOfOperand2);
			/*else if (s.substr(0, placeOfOPerator) == "sinh")     return sinh(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "cosh")     return cosh(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "tanh")     return tanh(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "tanh")     return sech(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "tanh")     return csch(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "tanh")     return coth(valueOfOperand2);*/

			else if (s.substr(0, placeOfOPerator) == "asin")    return asin(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "acos")    return acos(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "atan")    return atan(valueOfOperand2);
			//else if(s.substr(0,placeOfOPerator)=="sqrt")    return sqrt  (valueOfOperand2) ;
			else if (s.substr(0, placeOfOPerator) == "exp")     return exp(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "log")     return log(valueOfOperand2);
			else if (s.substr(0, placeOfOPerator) == "log10")   return log10(valueOfOperand2);

			/*else if(s.substr(0,placeOfOPerator)=="pow")
			{
			int findDouble = s.find_first_of("0123456789");
			if (findDouble != std::string::npos)
			{
			int endDouble = s.find_first_not_of("0123456789", findDouble);
			valueOfOperand2 = CMatrix (s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) ) ;
			}
			operand1index = distance( varNames, find( varNames , varNames + 100 , s.substr(0,placeOfOPerator-3) ) );
			valueOfOperand1 = CMatrix (varContent[operand1index]);
			return valueOfOperand1 . pow ( valueOfOperand2 ) ;
			}*/
		}

		else if (s[placeOfOPerator] == 46)                      // .
		{
			  
             {
				 if(findMatrixString != std::string::npos)
				{
					foundString=1;   
					int endOfMatrixString = s.find("]",findMatrixString);
					if(findMatrixString<placeOfOPerator)
					{
						valueOfOperand1 = CMatrix(s.substr(findMatrixString,endOfMatrixString+1));
						findMatrixString = s.find("[",endOfMatrixString);
			            if(findMatrixString != std::string::npos)
						{
							endOfMatrixString = s.find("]",findMatrixString);
							valueOfOperand2 = CMatrix(s.substr(findMatrixString,endOfMatrixString));
						}
						else
						{
							int findDoubleOfOp2 = s.find_first_of("0123456789",endOfMatrixString);   
			                int endDoubleOfOp2 = s.find_first_not_of("0123456789", findDoubleOfOp2);
				            if (findDoubleOfOp2 != std::string::npos && s.substr(findDoubleOfOp2-1,1)!="[")
							{
								numberString = s.substr(findDoubleOfOp2, endDoubleOfOp2 != std::string::npos ? endDoubleOfOp2-findDoubleOfOp2 : endDoubleOfOp2) ;
						    	valueOfOperand2 = CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op2const * stod(numberString)) ;
							}
							else
							{
								operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(placeOfOPerator+2,s.length()) ) );
								int foundMatrix2 = varContent [operand2index] . find ("[");
			                    if(foundMatrix2 != std::string::npos)
								{
									valueOfOperand2 = CMatrix (varContent[operand2index]);
			                        valueOfOperand2 = valueOfOperand2 . dotMul( CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op2const) );
								}
							}
						}
					}
					else if(findMatrixString>placeOfOPerator)
					valueOfOperand2 = CMatrix(s.substr(findMatrixString,endOfMatrixString)); 
				}
				 
				int findDouble = s.find_first_of("0123456789"); 
			    int endDouble = s.find_first_not_of("0123456789", findDouble);
				if (findDouble != std::string::npos && s.substr(findDouble-1,1)!="[" && foundString==0)
				{
					if(findDouble<placeOfOPerator)
						{
							//operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(placeOfOPerator+2,s.length()) ) );
				            //valueOfOperand2 = CMatrix (varContent[operand2index]);
							//valueOfOperand2 = valueOfOperand2 . dotMul( CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op2const) );
							numberString = s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) ;
							valueOfOperand1 = CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op1const * stod(numberString)) ;
					    }
					
					else
						{
							//operand1index = distance( varNames, find( varNames , varNames + 100 , s.substr(0,placeOfOPerator) ) ); 
				            //valueOfOperand1 = CMatrix (varContent[operand1index]);
							//valueOfOperand1 = valueOfOperand1 . dotMul( CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op1const) );
							numberString = s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) ;
							valueOfOperand2 = CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op2const * stod(numberString)) ;
					    }
					
				} 
			  
				else if(foundString==0)
				{
					operand1index = distance( varNames, find( varNames , varNames + 100 , s.substr(0,placeOfOPerator) ) );
                    operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(placeOfOPerator+2,s.length()) ) );
					int foundMatrix1 = varContent [operand1index] . find ("[");
					int foundMatrix2 = varContent [operand2index] . find ("[");
					if(foundMatrix2 == std::string::npos) 
						{
							valueOfOperand1 = CMatrix (varContent[operand1index]);
							valueOfOperand1 = valueOfOperand1 . dotMul( CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op1const) );
							valueOfOperand2 = CMatrix (valueOfOperand1.getnR() , valueOfOperand1.getnC() , 4 , stod(varContent[operand2index]));
					    }
					else if(foundMatrix1 == std::string::npos)
						{
							valueOfOperand2 = CMatrix (varContent[operand2index]);
							valueOfOperand2 = valueOfOperand2 . dotMul( CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op2const) );
							valueOfOperand1 = CMatrix (valueOfOperand2.getnR() , valueOfOperand2.getnC() , 4 , stod(varContent[operand1index]));
					    }
					else 
					{
						valueOfOperand1 = CMatrix (varContent[operand1index]);
						valueOfOperand1 = valueOfOperand1 . dotMul( CMatrix(valueOfOperand1.getnR(), valueOfOperand1.getnC(), 4, op1const) );
						valueOfOperand2 = CMatrix (varContent[operand2index]);
						valueOfOperand2 = valueOfOperand2 . dotMul( CMatrix(valueOfOperand2.getnR(), valueOfOperand2.getnC(), 4, op2const) );
			        }
					
				}
			 }
			
			if (s[placeOfOPerator+1] == 43)          return (valueOfOperand1 + valueOfOperand2);
			else if (s[placeOfOPerator+1] == 45)     return valueOfOperand1 - valueOfOperand2;
			else if (s[placeOfOPerator + 1] == 42)   return valueOfOperand1.dotMul(valueOfOperand2);       // **
			else if (s[placeOfOPerator + 1] == 47)   return valueOfOperand1.dotDiv(valueOfOperand2);       // **
			else if (s[placeOfOPerator + 1] == 93)   return valueOfOperand1.dotLDiv(valueOfOperand2);       // **
			else if (s.substr(placeOfOPerator + 1, placeOfOPerator + 3) == "pow(" || s[placeOfOPerator] == 94)
			{
				int findDouble = s.find_first_of("0123456789");
				if (findDouble != std::string::npos)
				{
					int endDouble = s.find_first_not_of("0123456789", findDouble);
					return valueOfOperand1.dotPow(stod(s.substr(findDouble, endDouble != std::string::npos ? endDouble - findDouble : endDouble)));                                  //      **
				}
			}


		}

	}
}
