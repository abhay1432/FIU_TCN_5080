//============================================================================
// Name        : TCN 5080 Secure Telecom Transaction. Project 1
// Author      :  Abhaykumar Kumbhar 5115320 
// Version     :
// File name:  : tcn5080project1.cpp
// Description : Main function for simplifies DES encrption/decrption.
//============================================================================


//system defined header inclusion
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <boost/algorithm/string.hpp> //used in string compare operation

//user defined header inclusion
#include "utility.h"
#include "defs.h"
#include "des.h"

//Namespace
using namespace std;

//Macros 

//global variables
utility* myUtility;
des* myDes;

int main(int argc, char *argv[]) {


	if(argc != NUM_OF_INPUT_PARAMS ) 
	{
		cerr << "ERROR: Main Func: Not enough parameters." << endl;
	}
	else 
	{
		// Read all the user inputs and save it in variables 
//		clog << "DEBUG: Main Func: valid number of parameters." << endl;
		string desTask        = argv[1]; 
		string initKey        = argv[2];
		string initVector     = argv[3];
		string plaintextFile  = argv[4];
		string ciphertextFile = argv[5];
		
		// convert the file names from string to char
		char *cipherBinaryFile = &ciphertextFile[0u];
		char *plainBinaryFile  = &plaintextFile[0u];
	
		cout << "INFO: Main func: user inputs are: \r\n" <<"Encrypt\\Decrypt: " << desTask << "\r\ninitial key:\t" << initKey 
		<<" \r\ninitial Vector\t" << initVector << "\r\nplain text file name\t" << plainBinaryFile << "\r\ncipher text file name \t" << cipherBinaryFile << endl;
		
		
		// create the utilily and DES class 
		myUtility =  new utility();
		myDes = new des();
		
		if ((myUtility != NULL) and (myDes != NULL))
		{
			



			//Based on the user input, we either encrypt or decrypt or do nothing.
			if (boost::iequals(desTask, "encrypt"))
			{
				clog << "DEBUG: Main func: user input task is to encrpyt the binary text"<<endl;
				//Main func: Read the  Binary input from plain text file.
			        myUtility->readPlainTextFile(plainBinaryFile);		
				string binaryStr8Bit1 = myUtility->getBinaryPlainTextLeft();
				clog << "DEBUG: Main func: first block of 8 bits of plain text: " << binaryStr8Bit1 << endl;
				string binaryStr8Bit2 = myUtility->getBinaryPlainTextRight();
				clog << "DEBUG: Main func: second block of 8 bits of plain text: " << binaryStr8Bit2 << endl;					
				
				if (myUtility->CheckifStringIsBinary(binaryStr8Bit1) and 
				    myUtility->CheckifStringIsBinary(binaryStr8Bit2) and 
                                    myUtility->CheckifStringIsBinary(initKey))
				{
//					clog<< "DEBUG: main: Input strings are valid and binary" << endl;  
					myDes->generateRoundKeys(initKey);
					cout << "================== SIMPLE S-DES Encrypt ==================" <<endl; 					
					string simplifedDes1 = myDes->encrypt(binaryStr8Bit1);
				        string simplifedDes2 = myDes->encrypt(binaryStr8Bit2);

					cout<< "Encryption Simplified S-DES for " <<binaryStr8Bit1 <<" " <<binaryStr8Bit2 <<" is "
                                                                                  <<simplifedDes1  <<" " <<simplifedDes2 << endl;

					cout << "==================== CBC S-DES Encrypt ===================" <<endl;
					//from the text Fig.4.5 C1 = IV XOR m1
					string c1 = myDes->encrypt(myUtility->XOR(binaryStr8Bit1, initVector));
					// c2 = c1 XOR m2
					string c2 = myDes->encrypt(myUtility->XOR(binaryStr8Bit2, c1));	
					cout<< "CBC S-DES C1 is " << c1 <<endl;
					cout<< "CBC S-DES C2 is " << c2 <<endl;
					cout<< "Encryption Simplified S-DES for " <<binaryStr8Bit1 <<" " <<binaryStr8Bit2 <<" is " 
									         <<c1             <<" " <<c2 << endl;
					cout << "=========================================================" <<endl;
					//Write the output to file 
					myUtility->writeText2File(cipherBinaryFile, (c1+" "+c2)); 
				}						
			}
			else if (boost::iequals(desTask, "decrypt"))
			{
				clog << "DEBUG: Main func: user input task is to decrpyt the binary text"<<endl;
			        //Main func: Read the  Binary input from cipher text file.
				myUtility->readCiphertTextFile(cipherBinaryFile);
				string binaryStr8Bit1 = myUtility->getBinaryCiphertTextLeft();
				clog << "DEBUG: Main func: first block of 8 bits of cipher text: " << binaryStr8Bit1 << endl;
				string binaryStr8Bit2 = myUtility->getBinaryCiphertTextRight();
				clog << "DEBUG: Main func: second block of 8 bits of cipher text: " << binaryStr8Bit2 << endl;					
				
				if (myUtility->CheckifStringIsBinary(binaryStr8Bit1) and 
				    myUtility->CheckifStringIsBinary(binaryStr8Bit2) and 
                                    myUtility->CheckifStringIsBinary(initKey))
				{
//					clog<< "DEBUG: main: Input strings are valid and binary" << endl;  
					myDes->generateRoundKeys(initKey);
					cout << "================== SIMPLE S-DES Decrypt ==================" <<endl; 					
					string simplifedDes1 = myDes->decrypt(binaryStr8Bit1);
				        string simplifedDes2 = myDes->decrypt(binaryStr8Bit2);

					cout<< "Decryption Simplified S-DES for " <<binaryStr8Bit1 <<" " <<binaryStr8Bit2 <<" is "
                                                                                 <<simplifedDes1   <<" " <<simplifedDes2 << endl;
					cout << "==================== CBC S-DES Decrypt ===================" <<endl;
					//from the text Fig.4.5 m1 = IV XOR D(c1)
					string decrypt1 = myDes->decrypt(binaryStr8Bit1);
					string m1 = myUtility->XOR(decrypt1, initVector);

					string decrypt2 = myDes->decrypt(binaryStr8Bit2);
					string m2 = myUtility->XOR(binaryStr8Bit1, decrypt2);	


					cout<< "CBC S-DES C1 is " << m1 <<endl;
					cout<< "CBC S-DES C2 is " << m2 <<endl;
					cout<< "Decryption Simplified S-DES for " <<binaryStr8Bit1 <<" " <<binaryStr8Bit2 <<" is " 
									          <<m1             <<" " <<m2 << endl;
					cout << "==========================================================" <<endl;
					//Write the output to file 
					myUtility->writeText2File(cipherBinaryFile, (binaryStr8Bit1+" "+binaryStr8Bit2));
					myUtility->writeText2File(plainBinaryFile, (m1+" "+m2)); 
				}
			}
			else
			{
				cerr << "ERROR: main func: Wrong user input task" <<endl;
			}			
		}
		else
		{
			cerr <<"ERROR: Main func: utility object is null." << endl;
		}
		
		//House keeping: free all the memory alloaction
		delete myUtility;
		myUtility = 0;
		delete myDes;
		myDes = 0;
		
	}

	return 0;
}


