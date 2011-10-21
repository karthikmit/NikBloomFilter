/* 
   Author: Karthikeyan
   Date: 20/10/2011
   Module: MainDriver.cpp
*/

#include <iostream>
#include <string>
#include "NikBloomFilter.h"
using namespace std;

vector<unsigned char> CreateByteArray(string in)
{
	int length = in.size();
	char *input = (char *)in.c_str();

	vector<unsigned char> bytesArr(length);
	copy(input, input+length, bytesArr.begin());

	return bytesArr;
}

void TestBloom()
{
	NikBloomFilter filter(1000, 0.002);

	for( int i = 0; i < 1000; i++)
	{
		char buf[10] = {0};
		itoa(i, buf, 10);
		filter.Insert(CreateByteArray(buf));
	}

	int i1 = 0;
	for( int i = 1000; i < 2000; i++)
	{
		char buf[10] = {0};
		itoa(i, buf, 10);
		
		if(false == filter.IsPresent(CreateByteArray(buf)))
		{
			//cout << "Error" << endl;
			i1++;
		}
	}

	cout << "No of falses: " << i1 << endl;

	cout << "Completed" << endl;
}

int main()
{
	TestBloom();
}