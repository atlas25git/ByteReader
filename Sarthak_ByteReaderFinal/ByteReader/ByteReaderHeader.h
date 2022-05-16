#pragma once
#include <vector>
using namespace std;

class CByteReader {
	
private:
	vector<char> BUFFER;
	uint16_t m_nTotal;
	uint16_t m_nOffset;

public:
	CByteReader();
	CByteReader(int cap, char* BUFFER);
	void Reset(int cap, char* BUFFER);
	string ReadString(int n);
	unsigned long ReadBE(int n);  //read big endian, internal offset updated, the value of n is from 1 to 4
	unsigned long ReadLE(int n); //read litle endian, internal offset updated
	unsigned long ShowBE(int n); //just return big endian, without updating internal offset
	unsigned long ShowLE(int n); //just return big endian, without updating internal offsetun
	int Tell();  // returns the current postion(offset) in internal buffer
	int Total();  // returns the total size of internal buffer
	int Remaining();  // returns the remaining bytes in internal buffer
	void Flush(int n); // moves the current position ahead by n bytes
};