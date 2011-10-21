/* 
   Author: Karthikeyan
   Date: 20/10/2011
   Module: NikBloomFilter.cpp
*/

#include "NikBloomFilter.h"
#include "NikBloomUtils.h"
#include <math.h>

const double ln2 = 0.693147;
const double falseDropBase = 0.6185;

NikBloomFilter::NikBloomFilter(unsigned int expectedFields, double falseProbability)
{
	// Bloom filter has zero fields inserted.
	int bufferingFactor = (int)(log10(falseProbability) / log10(falseDropBase));
	unsigned int BloomSize = bufferingFactor * expectedFields;
	NumberOfIndices = (unsigned int)(ln2 * bufferingFactor);
	bloomBits.resize(BloomSize, 0);
}

bool NikBloomFilter::Insert(std::vector<unsigned char> inBytes)
{
	unsigned int *indicesToSet = GetIndices(inBytes);

	for( int i = 0; i < NumberOfIndices; i++)
	{
		bloomBits[indicesToSet[i]] = 1;
	}

	return true;
}

unsigned int *NikBloomFilter::GetIndices(std::vector<unsigned char> inBytes)
{
	unsigned int *indicesToSet = GetBloomIndices(inBytes, NumberOfIndices);
	unsigned int bloomSize = bloomBits.size();
	for( int i = 0; i < NumberOfIndices; i++)
	{
		indicesToSet[i] = indicesToSet[i] % bloomSize;
	}

	return indicesToSet;
}

bool NikBloomFilter::IsPresent(std::vector<unsigned char> inBytes)
{
	unsigned int *indicesToSet = GetIndices(inBytes);

	for( int i = 0; i < NumberOfIndices; i++)
	{
		if(false == bloomBits[indicesToSet[i]])
			return false;
	}
	return true;
}