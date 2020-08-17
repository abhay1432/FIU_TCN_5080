//============================================================================
// Name        : TCN 5080 Secure Telecom Transaction. Project 1
// Author      : Abhaykumar Kumbhar 5115320 
// Version     :
// File name:  : utility.cpp
// Description : class file for utility and helper methods
//============================================================================

//system header include
#include <stdlib.h>
#include <stdio.h>
#include<fstream>
#include<iostream>
#include <string.h>
#include <sstream>

//user define
#include "utility.h"
#include "defs.h"


using namespace std;

//=============================================
//Function: utility::utility
//Varibles: None
//Return Value: None
//Description: Contructor for Utility class
//=============================================
utility::utility()
{

}


//=============================================
//Function: ~utility::utility
//Varibles: None
//Return Value: None
//Description: destructor for Utility class
//=============================================
utility::~utility()
{

}



//=============================================
//Function: utility::readCiphertTextFile
//Varibles: None
//Return Value: None
//Description: utility to read cipher text file
//=============================================
void utility::readCiphertTextFile(char* cipherfile)
{

	ifstream cipherFd(cipherfile);

	getline(cipherFd, m_binaryCiphertText);
	
	cout << "INFO: Utility Class: Binary cipher text: " << m_binaryCiphertText << endl; 
	   	
	istringstream iss(m_binaryCiphertText);
	iss >> 	m_binaryCiphertTextLeft >> m_binaryCiphertTextRight;

}



//=============================================
//Function: utility::readPlainTextFile
//Varibles: None
//Return Value: None
//Description: utility to read plain text file
//=============================================
void utility::readPlainTextFile(char* plainfile)
{
	
	ifstream plainFd(plainfile);

	getline(plainFd, m_binaryPlainText);
	
	cout << "INFO: Utility Class: Binary plain text: " << m_binaryPlainText << endl; 
	   	
	istringstream iss(m_binaryPlainText);
	iss >> 	m_binaryPlainTextLeft >> m_binaryPlainTextRight;

}



//=============================================
//Function: utility::getBinaryCiphertTextLeft
//Varibles: None
//Return Value: string
//Description: utility to return first 8 bits of cipher text read from the file in binary form 
//=============================================
string utility::getBinaryCiphertTextLeft(void)
{

	return m_binaryCiphertTextLeft;

}

//=============================================
//Function: utility::getBinaryCiphertTextRight
//Varibles: None
//Return Value: string
//Description: utility to return first 8 bits of cipher text read from the file in binary form 
//=============================================
string utility::getBinaryCiphertTextRight(void)
{

	return m_binaryCiphertTextRight;

}


//=============================================
//Function: utility::getBinaryPlainTextLeft
//Varibles: None
//Return Value: string
//Description: utility to return first 8 bits plain text read from the file in binary form 
//=============================================
string utility::getBinaryPlainTextLeft(void)
{


	return m_binaryPlainTextLeft;

}


//=============================================
//Function: utility::getBinaryPlainTextRight
//Varibles: None
//Return Value: string
//Description: utility to return second 8 bits plain text read from the file in binary form 
//=============================================
string utility::getBinaryPlainTextRight(void)
{


	return m_binaryPlainTextRight;
}

//=============================================
//Function: utility::leftShift
//Variables: string inputStr to shift
//Return Value: string outputStr 
//Description: perform cyclic left shift
//=============================================
string utility::leftShift(string inputStr)
{

	string outputStr =  string("");
//	clog << "DEBUG: subkey before left shift " << inputStr << endl;	

	if(inputStr.size() != 0)
	{       
		//                        [skip 1, take 4]    + [first char goes last] 
		outputStr = inputStr.substr(1,inputStr.size()) + inputStr.substr(0,1);	
	}
	
//	clog << "DEBUG: subkey after left shift " << outputStr << endl;	
	return outputStr;

}


//=============================================
//Function: utility::rightShift
//Variables: string inputStr to shift
//Return Value: string outputStr 
//Description: perform cyclic right shift
//=============================================
string utility::rightShift(string inputStr)
{

	string outputStr =  string("");
//	clog << "DEBUG: subkey before right shift " << inputStr << endl;	

	if(inputStr.size() != 0)
	{
		//                        [last char goes first]                + [take 4, skip last]  		
		outputStr = inputStr.substr(inputStr.size()-1, inputStr.size()) + inputStr.substr(0, inputStr.size()-1); 
	}
	
//	clog << "DEBUG: subkey after right shift " << outputStr << endl;	
	return outputStr;

}

//=============================================
//Function: utility::XOR
//Variables: string inputStr1 and string inputStr2
//Return Value: string outputStr 
//Description: perform XOR operation of the input strings.
//=============================================
string utility::XOR(string inputStr1, string inputStr2)
{
	
	string outputStr =  string("");
	
	//Walk through and XOR each bit
	for(unsigned int i = 0; i < inputStr1.size(); ++i)
	{
		outputStr += (inputStr1[i]^inputStr2[i]) ? "1" : "0";
	}
	
//	clog << "DEBUG:utility::XOR: input string 1  " << inputStr1 << endl;	
//	clog << "DEBUG:utility::XOR: input string 2  " << inputStr2 << endl;	
//	clog << "DEBUG:utility::XOR: output XOR'd string " << outputStr << endl;	

	return outputStr;
	
}


//=============================================
//Function: utility::DecToBin
//Variables: int input 
//Return Value: string outputStr 
//Description: perform XOR operation of the input strings.
//=============================================
string utility::DecToBin (int input)
{
    if ( input == 0 ) return "0";
    if ( input == 1 ) return "1";

    if ( input % 2 == 0 )
        return DecToBin(input / 2) + "0";
    else
        return DecToBin(input / 2) + "1";
}

//=============================================
//Function: utility::BinToDec
//Variables: string inputStr
//Return Value: int result
//Description: perform binary to decimal conversion
//=============================================
int utility::BinToDec(string inputStr)
{
    int result = 0, pow = 1;
    for ( int i = inputStr.length() - 1; i >= 0; --i, pow <<= 1 )
        result += (inputStr[i] - '0') * pow;

    return result;
}


//=============================================
//Function: utility::CheckifStringIsBinary
//Variables: string inputStr
//Return Value: bool result
//Description: verify the string is a binary string
//=============================================
bool utility::CheckifStringIsBinary(string inputStr)
{

	bool retVal = true; // we always assume the user has given us valid string
	int size = inputStr.size();
	
	//size of string is not zero check every element of the string
	if( size != 0)
	{
		for(unsigned int i = 0; i < size; ++i)
		{
			if(inputStr[i] != '0' && inputStr[i] != '1')
			{
				retVal = false;
				break;
			}
		}
	}
	else
	{
		retVal = false;
	}

	return retVal;
}



//=============================================
//Function: utility::writeText2File
//Variables: string inputStr
//Return Value: none
//Description: write the text to the file 
//=============================================
void utility::writeText2File(char* filename, string inputStr)
{

	ofstream file2Write;
	file2Write.open (filename);
	file2Write << inputStr;
	file2Write.close();

}


