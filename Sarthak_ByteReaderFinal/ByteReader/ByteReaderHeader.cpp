#include "macros.h"
using namespace std;

CByteReader::CByteReader() {
	m_nOffset = 0;
	m_nTotal = 0;
}
CByteReader::CByteReader(int cap, char* BUFFER) {
	m_nTotal = cap;
	for (int i = 0; i < cap; i++)
	{
		this->BUFFER.push_back(BUFFER[i]);
	}
}

void CByteReader::Reset(int cap, char* BUFFER) {
	m_nTotal = cap;
	m_nOffset = 0;
	this->BUFFER.clear();
	for (int i = 0; i < cap; i++)
	{
		this->BUFFER.push_back(BUFFER[i]);
	}
}

string CByteReader::ReadString(int n)
{
	n = min(n, this->Remaining());
	string Value;
	for (int i = 0; i < n; i++)
	{
		Value += BUFFER[m_nOffset++];
	}
	
	return Value;
}

unsigned long CByteReader::ReadBE(int n) {
	if (n < 1 || n>4)
	{	
		cout << "Not a valid input\n"; 
		return -1;
	}
	n = min(n, (int)(m_nTotal - m_nOffset));

	uint8_t a = 0, b = 0, c = 0, d = 0;
	int counter = n;
	if (n)
		n--,
		a = BUFFER[m_nOffset++];
	if (n)
		n--,
		b = BUFFER[m_nOffset++];
	if (n)
		n--,
		c = BUFFER[m_nOffset++];
	if (n)
		n--,
		d = BUFFER[m_nOffset++];

#ifdef DEBUG
	cout << (char)a << " " << (char)b << " " << (char)c << " " << (char)d << "\n";
	cout << (int)a << " " << (int)b << " " << (int)c << " " << (int)d << "\n";
#endif
	unsigned long data = 0;
	switch (counter) {
	case 1:
	{
		data = a;
		break;
	}
	case 2:
	{
		data = (b & 255) + ((a & 255) << 8);
		break;
	}
	case 3:
	{
		data = (c & 255) + ((b & 255) << 8) + ((a & 255) << 16);
		break;
	}
	case 4:
	{
		data = (d & 255) + ((c & 255) << 8) + ((b & 255) << 16) + ((a & 255) << 24);
		break;
	}
	}
	
	return data;
}

unsigned long CByteReader::ReadLE(int n) {
	if (n < 1 || n>4)
	{
		cout << "Not a valid input\n";
		return -1;
	}
	n = min(n, (int)(m_nTotal - m_nOffset));

	uint8_t a = 0, b = 0, c = 0, d = 0;
	
	if (n)
		n--,
		a = BUFFER[m_nOffset++];
	if (n)
		n--,
		b = BUFFER[m_nOffset++];
	if (n)
		n--,
		c = BUFFER[m_nOffset++];
	if (n)
		n--,
		d = BUFFER[m_nOffset++];

#ifdef DEBUG
	cout << (int)a << " " << (int)b << " " << (int)c << " " << (int)d << "\n";
#endif
	unsigned long data = (a & 255) + ((b & 255) << 8) + ((c & 255) << 16) + ((d & 255) << 24);
	

	return data;
}

unsigned long CByteReader::ShowBE(int n) {
	n = min(n, (int)(m_nTotal - m_nOffset));
	unsigned long data = this->ReadBE(n);
	m_nOffset -= n;
	return data;
}

unsigned long CByteReader::ShowLE(int n) {
	n = min(n, (int)(m_nTotal - m_nOffset));
	unsigned long data = this->ReadLE(n);
	m_nOffset -= n;
	return data;
}

int CByteReader:: Tell() {
	return m_nOffset;
}
int CByteReader:: Total() {
	return BUFFER.size();
}
int CByteReader::Remaining() {
	return max((int)BUFFER.size() - m_nOffset,0);
}
void CByteReader:: Flush(int n) {
	m_nOffset += n;
}