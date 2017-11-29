CMatrix solveCMatrix(string s, string varNames[100], string varContent[100] , int& variablesNo, int& outFileSize)  // Verina /* Takes a string as input and returns a matrix output, Input may contain previous predefined variables and/or normal numbers */
     	{
		string operand1 , operand2 ; 

		int place = s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") ;
		if (place != std::string::npos)
		{
			
			if((s[place])==40)                        // (
			{
			    int p = s.find(")");

				int operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(place+1,p-place-1) ) ); 
				double valueOfOperand2 = stod (varContent[operand2index]);
				
				
				if(s.substr(0,place)=="sin")          return sin   (valueOfOperand2) ;
				else if(s.substr(0,place)=="cos")     return cos   (valueOfOperand2) ;
				else if(s.substr(0,place)=="tan")     return tan   (valueOfOperand2) ;
				else if(s.substr(0,place)=="asin")    return asin  (valueOfOperand2) ;
				else if(s.substr(0,place)=="acos")    return acos  (valueOfOperand2) ;
				else if(s.substr(0,place)=="atan")    return atan  (valueOfOperand2) ;
				else if(s.substr(0,place)=="sqrt")    return sqrt  (valueOfOperand2) ;
				else if(s.substr(0,place)=="exp")     return exp   (valueOfOperand2) ;
				else if(s.substr(0,place)=="log")     return log   (valueOfOperand2) ;
				else if(s.substr(0,place)=="log10")   return log10 (valueOfOperand2) ;
				else if(s.substr(0,place)=="pow")    
					{
						size_t const findDouble = s.find_first_of("0123456789");
						if (findDouble != std::string::npos)
						{
							size_t const endDouble = s.find_first_not_of("0123456789", findDouble);
							valueOfOperand2 = stod ( s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) );
						}

						int operand1index = distance( varNames, find( varNames , varNames + 100 , s.substr(0,place-3) ) );
				        double valueOfOperand1 = stod (varContent[operand1index]);

				        return valueOfOperand1 pow ( valueOfOperand2 ) ;
				    }

			}
						
			else if(s[place]==46)                      // .
			{
				size_t const findDouble = s.find_first_of("0123456789");  double valueOfOperand1 , valueOfOperand2 = 0;
		{
				if (findDouble != std::string::npos)
		         {
					size_t const endDouble = s.find_first_not_of("0123456789", findDouble);
					if(findDouble<place)
						{
							valueOfOperand1 = stod ( s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) );
							int operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(place+2,s.length()) ) );
				            valueOfOperand2 = stod (varContent[operand2index]);
					    }
					else
						{
							valueOfOperand2 = stod ( s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) );
							int operand1index = distance( varNames, find( varNames , varNames + 100 , s.substr(0,place) ) ); 
				            valueOfOperand1 = stod (varContent[operand1index]);
					    }

				}
 
				else 
				{
					int operand1index = distance( varNames, find( varNames , varNames + 100 , s.substr(0,place) ) ); 
				    valueOfOperand1 = stod (varContent[operand1index]);					
				
					int operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(place+2,s.length()) ) );
				    valueOfOperand2 = stod (varContent[operand2index]);
				}
     	}
				
				if(s[place]==42)        return valueOfOperand1 .* valueOfOperand2 ;
				else if(s[place]==47)   return valueOfOperand1 ./ valueOfOperand2 ;
				else if(s[place]==93)   return valueOfOperand1 .\ valueOfOperand2 ;
				else if(s[place]==94)   return valueOfOperand1 .^ valueOfOperand2 ;
				else if(s.substr(place+1,place+3)=="pow(")   
					{
						size_t const findDouble = s.find_first_of("0123456789");
						if (findDouble != std::string::npos)
						{
							size_t const endDouble = s.find_first_not_of("0123456789", findDouble);
							valueOfOperand2 = stod ( s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) );
						}	
					 return valueOfOperand1 .pow (valueOfOperand2) ;

				    }
						
			}
		 	
			
			else if(s[place]==43 || s[place]==45 || s[place]==42 || s[place]==47 || s[place]==92 || s[place]==38 || s[place]==124)
			{
				size_t const findDouble = s.find_first_of("0123456789");  double valueOfOperand1 , valueOfOperand2 = 0;
             {
				if (findDouble != std::string::npos)
				{
					size_t const endDouble = s.find_first_not_of("0123456789", findDouble);
					if(n<place)
						{
							valueOfOperand1 = stod ( s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) );
							int operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(place+1,s.length()) ) );
				            valueOfOperand2 = stod (varContent[operand2index]);
					    }
					else
						{
							valueOfOperand2 = stod ( s.substr(findDouble, endDouble != std::string::npos ? endDouble-findDouble : endDouble) );
							int operand1index = distance( varNames, find( varNames , varNames + 100 , s.substr(0,place) ) ); 
				            valueOfOperand1 = stod (varContent[operand1index]);
					    }

				}
 
				else 
				{
					int operand1index = distance( varNames, find( varNames , varNames + 100 , s.substr(0,place) ) ); 
				    valueOfOperand1 = stod (varContent[operand1index]);					
				
					int operand2index = distance( varNames, find( varNames , varNames + 100 , s.substr(place+1,s.length()) ) );
				    valueOfOperand2 = stod (varContent[operand2index]);
				}
			}

				if(s[place]==43)        return valueOfOperand1 + valueOfOperand2 ;
				else if(s[place]==45)   return valueOfOperand1 - valueOfOperand2 ;
				else if(s[place]==42)   return valueOfOperand1 * valueOfOperand2 ;
				else if(s[place]==47)   return valueOfOperand1 / valueOfOperand2 ;
				else if(s[place]==92)   return valueOfOperand1 \ valueOfOperand2 ;
				else if(s[place]==38)   return valueOfOperand1 & valueOfOperand2 ;
				else if(s[place]==124)  return valueOfOperand1 | valueOfOperand2 ;

			}
			
			
			
			
			 
		}

}

	
		   
 
