#ifndef _NIC_BLOOM_H
#define _NIC_BLOOM_H

/* 
   Author: Karthikeyan
   Date: 20/10/2011
   Module: NikBloomFilter.h
*/

#include <vector>
#include <algorithm>
#include <boost\dynamic_bitset.hpp>

class NikBloomFilter
{
public:
	NikBloomFilter(unsigned int expectedFields, double desiredFalseProbability = 0.1);
	bool Insert(std::vector<unsigned char> inBytes);
	bool Insert(unsigned char *inBytes, int length)
	{
		// Convert into a vector and call Insert(vector);
		std::vector<unsigned char> inBytesVector(length);
		std::copy(inBytes, inBytes + length, inBytesVector.begin());
		return Insert(inBytesVector);
	}

	bool IsPresent(std::vector<unsigned char> inBytes);
	bool IsPresent(unsigned char* inBytes, int length)
	{
		std::vector<unsigned char> inBytesVector(length);
		std::copy(inBytes, inBytes + length, inBytesVector.begin());
		return IsPresent(inBytesVector);
	}
	
private:
	boost::dynamic_bitset<> bloomBits;
	unsigned int NumberOfIndices;

	unsigned int *GetIndices(std::vector<unsigned char> inBytes);
};

#endif