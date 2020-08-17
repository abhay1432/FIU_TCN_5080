//============================================================================
// Name        : TCN 5080 Secure Telecom Transaction. Project 1
// Author      :  Abhaykumar Kumbhar 5115320 
// Version     :
// File name:  :  des.h
// Description : Header file for simplified DES
//============================================================================

#ifndef DES_H_
#define DES_H_

//system header includes
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <vector>

//user define header includes
#include "defs.h"

using namespace std;
using std::vector;

class des
{

public:
	des(); // Contructor
	~des(); // Destructor
	
	void generateRoundKeys(string key);
	string encrypt(string plainText);
	string decrypt(string cipherText);


protected:

private:
	//DES tables 
	static const int m_permutationTable[PERMUTE_TABLE_SIZE]; // initial permutation table
	static const int m_inversePermutationTable[PERMUTE_TABLE_SIZE]; // inverse permutation table
	static const int m_p10Table[P10]; //permutation 10 table
	static const int m_p08Table[P08]; //permutation 08 table
	static const int m_p04Table[P04]; //permutation 04 table      
	static const int m_expandAndPermuteOp[EBOX]; //expand and permutate operation
	//DES Keys 
	string m_subKey0;
	string m_subKey1; 
	//DES SBOX
	vector< vector<string > > m_sBox0;
	vector< vector<string > > m_sBox1; 
	//DES helper funciton
	void createSbox0(void);
	void createSbox1(void);
	int perfomSboxColOp(string inputStr);
	int perfomSboxRowOp(string inputStr);
	bool verifyKeyAndTextSize(string key, string plainText);
	string inversePermutation(string inputStr);
	string p10(string inputStr);
	string p08(string inputStr);
	string p04(string inputStr);
	string eBox(string inputStr);
	string sBox(string inputStr, short int box);
	string fBox(string inputStr, int round);
	string initialPermutation(string inputStr);

};


#endif /* DES_H_ */

