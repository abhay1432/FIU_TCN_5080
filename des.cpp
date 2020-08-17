//============================================================================
// Name        : TCN 5080 Secure Telecom Transaction. Project 1
// Author      :  Abhaykumar Kumbhar 5115320 
// Version     :
// File name:  :  des.cpp
// Description : Class file for simplified DES
//============================================================================

//system header includes

//user define includes
#include "defs.h"
#include "des.h"
#include "utility.h"

// Globals 
// This permutation table combination is picked from the C-3 page of the handout 
const int des::m_permutationTable[PERMUTE_TABLE_SIZE] = {2,6,3,1,4,8,5,7}; 
const int des::m_inversePermutationTable[PERMUTE_TABLE_SIZE] = {4,1,3,5,7,2,8,6};
const int des::m_p10Table[P10] = {3,5,2,7,4,10,1,9,8,6};
const int des::m_p08Table[P08] = {6,3,7,4,8,5,10,9};
const int des::m_p04Table[P04] = {2,4,3,1};
const int des::m_expandAndPermuteOp[EBOX] = {4,1,2,3,2,3,4,1};

extern utility* myUtility;

//=============================================
//Function: des::des
//Varibles: None
//Return Value: None
//Description: Contructor for des class
//=============================================
des::des()
{
	m_subKey0 = string("");
	m_subKey1 = string("");
}


//=============================================
//Function: des::~des
//Varibles: None
//Return Value: None
//Description: destructor for des class
//=============================================
des::~des()
{

}


//=============================================
//Function: des::initialPermutation
//input Variables: string inputStr ( string to permute)
//Return Value: string outputStr (permutated string)
//Description: based on the permutation table rearrange the input string.
//             used in encrption    
//=============================================
string des::initialPermutation(string inputStr)
{
	string outputStr = string("");

	for(unsigned int i = 0; i < PERMUTE_TABLE_SIZE; ++i)
	{
		outputStr += inputStr[des::m_permutationTable[i]-1 ];
	}		
	
//	clog << "DEBUG: des::initialPermutation: input string: " << inputStr << endl;
//	clog << "DEBUG: des::initialPermutation: permutated/output string: " << outputStr << endl;

	return outputStr;
}

//=============================================
//Function: des::generateRoundKeys
//input Variables: string inputStr ( init key)

//Return Value: string outputStr (round key

//Description: Generate the round key 
//=============================================
void des::generateRoundKeys(string key)
{

	if(key.size() == DES_KEY_SIZE)
	{
		//perform permutation 10 on this key
		key = p10(key);

		//Split the key and shift
		string keyLeft = myUtility->leftShift(key.substr(0,(DES_KEY_SIZE/2)));
		string keyRight = myUtility->leftShift(key.substr((DES_KEY_SIZE/2), DES_KEY_SIZE));

		//generate subkey 0 with permuatation 8
		m_subKey0 = p08(keyLeft + keyRight);
		cout <<"RESULT: des:generateRoundKeys: k1 " << m_subKey0 << endl;
		
		//Left shift the bits again by 2
		keyLeft  = myUtility->leftShift(keyLeft);
		keyRight = myUtility->leftShift(keyRight);
		keyLeft  = myUtility->leftShift(keyLeft);
		keyRight = myUtility->leftShift(keyRight);

		//Generate subkey 1 with permutation 8
		m_subKey1 = p08(keyLeft + keyRight);
		cout <<"RESULT: des:generateRoundKeys: k2 " << m_subKey1 << endl;
	}
	else
	{
		cerr<< "ERROR: des::generateRoundKeys: wrong key size. " << endl; 
	}
	
}

//=============================================
//Function: des::inversePermutation
//input Variables: string inputStr ( string to permute)

//Return Value: string outputStr (permutated string)

//Description: based on the permutation table rearrange the input string.
//             used in decryption    
//=============================================
string des::inversePermutation(string inputStr)
{

	string outputStr = string("");

	for(unsigned int i = 0; i < PERMUTE_TABLE_SIZE; ++i)
	{
		outputStr += inputStr[des::m_inversePermutationTable[i]-1 ];
	}		
	
//	clog << "DEBUG: des::inverse Permutation: input string: " << inputStr << endl;
//	clog << "DEBUG: des::inverse Permutation: permutated/output string: " << outputStr << endl;

	return outputStr;

}


//=============================================
//Function: des::p10
//input Variables: string inputStr 
//Return Value: string outputStr 
//Description: Permutation 10 table
//=============================================
string des::p10(string inputStr)
{
	string outputStr = string("");

	for(unsigned int i = 0; i < P10; ++i)
	{
		outputStr += inputStr[des::m_p10Table[i]-1 ];
	}		
	
//	clog << "DEBUG: des::p10 input string for P10: " << inputStr << endl;
//	clog << "DEBUG: des::p10 output string after p10: " << outputStr << endl;

	return outputStr;
}


//=============================================
//Function: des::p08
//input Variables: string inputStr 
//Return Value: string outputStr 
//Description: Permutation 08 table
//=============================================
string des::p08(string inputStr)
{
	string outputStr = string("");

	for(unsigned int i = 0; i < P08; ++i)
	{
		outputStr += inputStr[des::m_p08Table[i]-1 ];
	}		
	
//	clog << "DEBUG: des::p08 input string for P08: " << inputStr << endl;
//	clog << "DEBUG: des::p08 output string after P08: " << outputStr << endl;

	return outputStr;
}


//=============================================
//Function: des::p04
//input Variables: string inputStr 
//Return Value: string outputStr 
//Description: Permutation 4 table
//=============================================
string des::p04(string inputStr)
{
	string outputStr = string("");

	for(unsigned int i = 0; i < P04; ++i)
	{
		outputStr += inputStr[des::m_p04Table[i]-1 ];
	}

	return outputStr;
}


//=============================================
//Function: des::eBox
//input Variables: string inputStr 
//Return Value: string outputStr 
//Description: Map an input with the expansion and 
//             permutation table and return the result
//             Will expand a 4-bit string to 8-bits
//=============================================
string des::eBox(string inputStr)
{
	string outputStr = string("");

	for(unsigned int i = 0; i < EBOX; ++i)
	{
		outputStr += inputStr[ m_expandAndPermuteOp[i]-1 ];
	}

//	clog << "DEBUG: des::eBox: output " <<outputStr <<endl;
	return outputStr;

}


//=============================================
//Function: des::createSbox0
//input Variables: None
//Return Value: none
//Description: creates S box 0 as show on C-5
//=============================================
void des::createSbox0(void)
{

	//Fill the s box 0 
	vector<string> row;

	row.push_back("01");
	row.push_back("00");
	row.push_back("11");
	row.push_back("10");
	m_sBox0.push_back(row);

	row.clear();
	row.push_back("11");
	row.push_back("10");
	row.push_back("01");
	row.push_back("00");
	m_sBox0.push_back(row);

	row.clear();
	row.push_back("00");
	row.push_back("10");
	row.push_back("01");
	row.push_back("11");
	m_sBox0.push_back(row);

	row.clear();
	row.push_back("11");
	row.push_back("01");
	row.push_back("11");
	row.push_back("10");
	m_sBox0.push_back(row);

}


//=============================================
//Function: des::createSbox1
//input Variables: None
//Return Value: none
//Description: creates S box 1 as show on C-5
//=============================================
void des::createSbox1(void)
{

	vector<string> row;

	row.push_back("00");
	row.push_back("01");
	row.push_back("10");
	row.push_back("11");
	m_sBox1.push_back(row);

	row.clear();
	row.push_back("10");
	row.push_back("00");
	row.push_back("01");
	row.push_back("11");
	m_sBox1.push_back(row);

	row.clear();
	row.push_back("11");
	row.push_back("00");
	row.push_back("01");
	row.push_back("00");
	m_sBox1.push_back(row);

	row.clear();
	row.push_back("10");
	row.push_back("01");
	row.push_back("00");
	row.push_back("10");
	m_sBox1.push_back(row);

}


//=============================================
//Function: des::perfomSboxColOp
//input Variables: string inputStr
//Return Value: string outputStr 
//Description: Sbox column manipulation
//=============================================
int des::perfomSboxColOp(string inputStr)
{
	//Use Bit-2 and Bit-3 for column
	string colBin = string("");
	colBin += inputStr[1];
	colBin += inputStr[2];
	int col = myUtility->BinToDec(colBin);

	return col;
}


//=============================================
//Function: des::perfomSboxRowOp
//input Variables: string inputStr
//Return Value: string outputStr 
//Description: Sbox row manipulation
//=============================================
int des::perfomSboxRowOp(string inputStr)
{

	//Use Bit-1 and Bit-4 for row
	string rowBin = string("");
	rowBin += inputStr[0];
	rowBin += inputStr[3];
	int row = myUtility->BinToDec(rowBin);

	return row;
}


//=============================================
//Function: des::sBox
//input Variables: string inputStr and int box number
//Return Value: string outputStr 
//Description: Sbox manipulation
//=============================================
string des::sBox(string inputStr, short int box)
{
	string outputStr = string("");
	
	if (box == SBOX0)
	{
		createSbox0();
		return m_sBox0[perfomSboxRowOp(inputStr)][perfomSboxColOp(inputStr)];		
		
	}
	else if (box == SBOX1)
	{
		createSbox1();
		return m_sBox1[perfomSboxRowOp(inputStr)][perfomSboxColOp(inputStr)];
	}
	else
	{
		return outputStr;
	}
	
}


//=============================================
//Function: des::fBox
//input Variables: string inputStr and int round number
//Return Value: string outputStr 
//Description: Permutation 4 table
//=============================================
string des::fBox(string inputStr, int round)
{      
        string outputStr = string("");

	//Expand the input from 4-bits to 8-bits using ebox
	inputStr = eBox(inputStr);

	//XOR the input with the key for this round
	if(round == ROUND0)
	{
		inputStr = myUtility->XOR(inputStr, m_subKey0);
	}
	else if (round == ROUND1)
	{
		inputStr = myUtility->XOR(inputStr, m_subKey1);
	} 

	//Left half goes to sBox 0
	string left = inputStr.substr(0,(inputStr.length()/2));
	left = sBox(left, SBOX0);

	//Right half goes to sBox 1
	string right = inputStr.substr((inputStr.length()/2), inputStr.length());
	right = sBox(right, SBOX1);

	outputStr = left + right;
	outputStr = p04(outputStr);

//	clog <<"DEBUG: des:fBox: output " <<outputStr <<endl;
	return outputStr;

}


//=============================================
//Function: des::verifyKeyAndTextSize
//input Variables: string key, string plainText
//Return Value: bool 
//Description: returns true if the key and plain text are of right size
//             else false 
//=============================================
bool des::verifyKeyAndTextSize(string key, string plainText)
{
	
	bool retValue = false; //default value 
	if ((key.size() == DES_KEY_SIZE) and (plainText.size() == BLOCK_SIZE))
	{
		retValue =  true;
	}
	else
	{
		cerr <<"ERROR: des::verifyKeyAndTextSize " <<endl; 
	}		
	
	return retValue;	
	
}

//=============================================
//Function: des::encrypt
//input Variables: None
//Return Value: string outputStr 
//Description: des encryption 
//=============================================

string des::encrypt(string plainText)
{

	string outputStr =  string("");
	string permutatedString =  string("");
	string left = string("");
	string right = string("");
	
	//Do the initial permutation
	permutatedString = initialPermutation(plainText);
	
	//split the string
	left  = permutatedString.substr(0,(permutatedString.size()/2));
	right = permutatedString.substr((permutatedString.size()/2), permutatedString.size());

	//Apply XOR to the left half and fBox to the right half
	left = myUtility->XOR(left, fBox(right, ROUND0));

	//Swap left and right
	left.swap(right);

	//Apply XOR of left half and fBox of right half
	left = myUtility->XOR(left, fBox(right, ROUND1));	

	//Do inverse initial permutation to get the cipher text
	outputStr  = inversePermutation((left+right));
	
//	cout << "RESULT: des::encryt: cipher text "<< outputStr << endl;
	return outputStr;

}


//=============================================
//Function: des::decrypt
//input Variables: None
//Return Value: string outputStr 
//Description: des decryption 
//=============================================
string des::decrypt(string cipherText)
{
	string outputStr =  string("");
	string permutatedString =  string("");
	string left = string("");
	string right = string("");

	//Do the initial permutation
	permutatedString = initialPermutation(cipherText);

	//split the string
	left  = permutatedString.substr(0,(permutatedString.size()/2));
	right = permutatedString.substr((permutatedString.size()/2), permutatedString.size());

	//Apply XOR of left half and fBox of right half
	left = myUtility->XOR(left, fBox(right, ROUND1));	

	//Swap left and right
	left.swap(right);

	//Apply XOR to the left half and fBox to the right half
	left = myUtility->XOR(left, fBox(right, ROUND0));

	//Do inverse initial permutation to get the cipher text
	outputStr  = inversePermutation((left+right));
	
//	cout << "RESULT: des::decryt: plain text "<< outputStr << endl;
	return outputStr;

}

