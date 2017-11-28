#ifndef DECODE_H
#define DECODE_H

void defSpecialMat(string s, string varNames[100], string varContent[100], string outToFile[100] , int& variablesNo, int& outFileSize); // Hanaa /* Define special matrices like B = rand(2, 3), C = eye(2, 4), d = F = ones(2, 3) and g = zeros(5, 4) */
void defMat(string s, string varNames[100], string varContent[100], string outToFile[100] , int& variablesNo, int& outFileSize); // Mina Mouries /* Define matrices that contain variables like b = [1; 2] a = [5] A = a = [1 3 4 5 a sin(0.4); 3 2 3 4 [9 2]; [2 3 4 2 1; 2 3 4 5 6], b] i.e: any matrix other than special matrices defined above*/
void doOperatrion(string s, string varNames[100], string varContent[100], string outToFile[100] , int& variablesNo, int& outFileSize); // Peter /* Will take a string input like A = 3 * sin(0.2) + d (9 + b * exp(3)) where d and b might be matrices*/ 
void print(string s, string varNames[100], string varContent[100], int& variableNo);// Beshoy /* Takes the file name as input and prints all the data in it */
void decode(string s, string varNames[100], string varContent[100], int& variableNo); // Beshoy /* Takes line by line from main function and determine how to work on each line */

#endif
