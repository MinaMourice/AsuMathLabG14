CMatrix solveCMatrix(string s, string varNames[100], string varContent[100] , int& variablesNo, int& outFileSize)  // Verina /* Takes a string as input and returns a matrix output, Input may contain previous predefined variables and/or normal numbers */
	{
		string operand1 , operand2 ;  

		int placeOfOPerator = s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") ;
		if (placeOfOPerator != std::string::npos)
		{
			
			if((s[placeOfOPerator])==40)                        // (
			{
			    int p = s.find(")");

				if (s.substr(0,placeOfOPerator)!="pow")
				{
					int operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(placeOfOPerator+1,p-placeOfOPerator-1) ) ); 
			    	CMatrix valueOfOperand2 = CMatrix (varContent[operand2index]);
				}
				
				
				if(s.substr(0,placeOfOPerator)=="sin")          return sin   (valueOfOperand2) ;
				else if(s.substr(0,placeOfOPerator)=="cos")     return cos   (valueOfOperand2) ;
				else if(s.substr(0,placeOfOPerator)=="tan")     return tan   (valueOfOperand2) ;
				else if(s.substr(0,placeOfOPerator)=="asin")    return asin  (valueOfOperand2) ;
				else if(s.substr(0,placeOfOPerator)=="acos")    return acos  (valueOfOperand2) ;
				else if(s.substr(0,placeOfOPerator)=="atan")    return atan  (valueOfOperand2) ;
				else if(s.substr(0,placeOfOPerator)=="sqrt")    return sqrt  (valueOfOperand2) ;
				else if(s.substr(0,placeOfOPerator)=="exp")     return exp   (valueOfOperand2) ;
				else if(s.substr(0,placeOfOPerator)=="log")     return log   (valueOfOperand2) ;
				else if(s.substr(0,placeOfOPerator)=="log10")   return log10 (valueOfOperand2) ;
				else if(s.substr(0,placeOfOPerator)=="pow")    
					{
						size_t const findDouble = s.find_first_of("0123456789");
						if (findDouble != std::string::npos)
						{
							size_t const endDouble = s.find_first_not_of("0123456789", findDouble);
							double valueOfOperand2 = stod ( s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) );
						}

						int operand1index = distance( varNames, find( varNames , varNames + 100 , s.substr(0,placeOfOPerator-3) ) );
				        CMatrix valueOfOperand1 = CMatrix (varContent[operand1index]);

				        return valueOfOperand1 pow ( valueOfOperand2 ) ;
				    }

			}
						
			else if(s[placeOfOPerator]==46)                      // .
			{
				size_t const findDouble = s.find_first_of("0123456789");  
		{
				if (findDouble != std::string::npos)
		         {
					size_t const endDouble = s.find_first_not_of("0123456789", findDouble);
					if(findDouble<placeOfOPerator)
						{
							double valueOfOperand1 = stod ( s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) );
							int operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(placeOfOPerator+2,s.length()) ) );
				            CMatrix valueOfOperand2 = CMatrix (varContent[operand2index]);
					    }
					else
						{
							double valueOfOperand2 = stod ( s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) );
							int operand1index = distance( varNames, find( varNames , varNames + 100 , s.substr(0,placeOfOPerator) ) ); 
				            CMatrix valueOfOperand1 = CMatrix (varContent[operand1index]);
					    }

				}
 
				else 
				{
					int operand1index = distance( varNames, find( varNames , varNames + 100 , s.substr(0,placeOfOPerator) ) ); 
				    CMatrix valueOfOperand1 = CMatrix (varContent[operand1index]);					
				
					int operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(placeOfOPerator+2,s.length()) ) );
				    CMatrix valueOfOperand2 = CMatrix (varContent[operand2index]);
				}
     	}
				
				if(s[placeOfOPerator]==42)        return valueOfOperand1 .* valueOfOperand2 ;
				else if(s[placeOfOPerator]==47)   return valueOfOperand1 ./ valueOfOperand2 ;
				else if(s[placeOfOPerator]==93)   return valueOfOperand1 .\ valueOfOperand2 ;
				else if(s[placeOfOPerator]==94)   return valueOfOperand1 .^ valueOfOperand2 ;
				else if(s.substr(placeOfOPerator+1,placeOfOPerator+3)=="pow(")   
					{
						size_t const findDouble = s.find_first_of("0123456789");
						if (findDouble != std::string::npos)
						{
							size_t const endDouble = s.find_first_not_of("0123456789", findDouble);
							double valueOfOperand2 = stod ( s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) );
						}	
					 return valueOfOperand1 .pow (valueOfOperand2) ;

				    }
						
			}
		 	
			
			else if(s[placeOfOPerator]==43 || s[placeOfOPerator]==45 || s[placeOfOPerator]==42 || s[placeOfOPerator]==47 || s[placeOfOPerator]==92 || s[placeOfOPerator]==38 || s[placeOfOPerator]==124)
			{
				size_t const findDouble = s.find_first_of("0123456789");  
             {
				if (findDouble != std::string::npos)
				{
					size_t const endDouble = s.find_first_not_of("0123456789", findDouble);
					if(findDouble<placeOfOPerator)
						{
							double valueOfOperand1 = stod ( s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) );
							int operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(placeOfOPerator+1,s.length()) ) );
				            CMatrix valueOfOperand2 = CMatrix (varContent[operand2index]);
					    }
					else
						{
							double valueOfOperand2 = stod ( s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) );
							int operand1index = distance( varNames, find( varNames , varNames + 100 , s.substr(0,placeOfOPerator) ) ); 
				            CMatrix valueOfOperand1 = CMatrix (varContent[operand1index]);
					    }

				}
 
				else 
				{
					int operand1index = distance( varNames, find( varNames , varNames + 100 , s.substr(0,placeOfOPerator) ) ); 
				    CMatrix valueOfOperand1 = CMatrix (varContent[operand1index]);					
				
					int operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(placeOfOPerator+1,s.length()) ) );
				    CMatrix valueOfOperand2 = CMatrix (varContent[operand2index]);
				}
			}

				if(s[placeOfOPerator]==43)        return valueOfOperand1 + valueOfOperand2 ;
				else if(s[placeOfOPerator]==45)   return valueOfOperand1 - valueOfOperand2 ;
				else if(s[placeOfOPerator]==42)   return valueOfOperand1 * valueOfOperand2 ;
				else if(s[placeOfOPerator]==47)   return valueOfOperand1 / valueOfOperand2 ;
				else if(s[placeOfOPerator]==92)   return valueOfOperand1 \ valueOfOperand2 ;
				else if(s[placeOfOPerator]==38)   return valueOfOperand1 & valueOfOperand2 ;
				else if(s[placeOfOPerator]==124)  return valueOfOperand1 | valueOfOperand2 ;

			}
			
			
			
			
			 
		}

}
