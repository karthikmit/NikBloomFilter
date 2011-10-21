#ifndef _NICBLOOMUTILS_H_
#define _NICBLOOMUTILS_H_

/* 
   Author: Karthikeyan
   Date: 20/10/2011
   Module: NikBloomUtils.h
*/

// MD5 Module: RSA Data Security, Inc., MD5 message-digest algorithm

#include "MD5.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

// Return 16 Bytes of MD5ied input of size, inputSize.
unsigned char* MD5Bytes(unsigned char* input, unsigned int inputSize)
{
	MD5 context;

	context.update(input, inputSize); 
	context.finalize();
	//cout << context.hex_digest();
	return context.raw_digest();
}

unsigned int *GetMD5Indices(unsigned char* input, int size)
{
	unsigned char* hashBytes = MD5Bytes(input, size);
	return (unsigned int *) hashBytes;
}

// Get 'numberOfIndices' of integers of MD5 output for inBytes.
unsigned int *GetBloomIndices(vector<unsigned char> inBytes, int numberOfIndices = 4)
{
	int toBeSpawnedoutBytesArray = 1;
	if( numberOfIndices > 4)
	{
		toBeSpawnedoutBytesArray = numberOfIndices / 4;
		if( numberOfIndices % 4 != 0)
			toBeSpawnedoutBytesArray += 1;
	}

	unsigned int inputSize = inBytes.size();
	unsigned char *input = new unsigned char[inputSize];
	unsigned int *returnValue = new unsigned int[numberOfIndices];

	copy(inBytes.begin(), inBytes.end(), input);

	if( toBeSpawnedoutBytesArray > 1)
	{
		inputSize += 1; delete [] input; input = NULL;
		input = new unsigned char[inputSize];
		copy(inBytes.begin(), inBytes.end(), input);
		unsigned char pad = 0;
		vector<unsigned int> indicesVector;
		
		while(toBeSpawnedoutBytesArray--)
		{
			input[inputSize-1] = pad++;
			unsigned int *out = GetMD5Indices(input, inputSize);

			for( int k = 0; k < 4; k++)
				indicesVector.push_back(out[k]);
		}
		
		copy(indicesVector.begin(), indicesVector.begin() + numberOfIndices, returnValue);
	}
	else
	{
		returnValue = GetMD5Indices(input, inputSize);
	}
	
	return returnValue;
}

void TestUtils()
{
	char test[] = "karthik";
	vector<unsigned char> bytesArr(sizeof(test));
	copy(test, test+strlen(test), bytesArr.begin());

	unsigned int *out = GetBloomIndices(bytesArr, 7);
	for( int i = 0; i < 7; i++)
	{
		out[i] = out[i] % 100;
	}
	copy(out, out + 7, ostream_iterator<unsigned int>(cout, " "));
}


#endif