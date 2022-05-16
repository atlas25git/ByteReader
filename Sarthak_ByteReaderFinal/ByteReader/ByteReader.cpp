#include "macros.h"

int BUFFER_SIZE = 36;
using namespace std;


int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		cout << "CMD argument not set\n";
	}



	string fileName = argv[1];
	cout << "FileName: " << fileName << "\n";
	ifstream in(fileName, ios::binary);
	char* BUFFER = new char[BUFFER_SIZE];
	in.seekg(0, ios::end);
	size_t totalBytes = in.tellg();
	in.seekg(0, ios::beg);

	BUFFER_SIZE = min(totalBytes, (size_t)BUFFER_SIZE);
	in.read(BUFFER, BUFFER_SIZE);

#ifdef DEBUG
	cout << "BYTES Read : " << BUFFER_SIZE << "\n";
#endif // DEBUG


	CByteReader ByteReader(BUFFER_SIZE, BUFFER);

	//Chunk ID:
	cout << "ChunkID: long " << ByteReader.ShowBE(4) << "\n";
	cout << "ChunkID: " << ByteReader.ReadString(4) << "\n";
#ifdef DEBUG
	cout << ByteReader.Total() << " " << ByteReader.Remaining() << " " << ByteReader.Tell() << "\n";
#endif // DEBUG

	//SubChunk1ID:
#ifdef DEBUG
	cout << ByteReader.ShowBE(4) << " " << ByteReader.ShowLE(4) << "\n";
	cout << ByteReader.Total() << " " << ByteReader.Remaining() << " " << ByteReader.Tell() << "\n";
#endif 

	ByteReader.Flush(8);
	cout << "SubChunkID: long " << ByteReader.ShowBE(4) << "\n";
	cout << "SubChunkID: " << ByteReader.ReadString(4) << "\n";
#ifdef DEBUG
	cout << ByteReader.Total() << " " << ByteReader.Remaining() << " " << ByteReader.Tell() << "\n";
#endif
	//Channel Count
#ifdef DEBUG
	cout << ByteReader.Tell() << "\n";
#endif
	ByteReader.Flush(6);
	cout << "NumChannels: " << ByteReader.ReadLE(2) << "\n";

	//Sampling freq.
	cout << "SamplingFreq: " << ByteReader.ReadLE(4) << "\n";

	//BitsPerSample:
	ByteReader.Flush(6);
	cout << "BitsPerSample: " << ByteReader.ReadLE(2) << "\n";

#ifdef DEBUG
	cout << ByteReader.Tell() << "\n";
#endif // DEBUG


	//SubChunk2ID:
	int count = 0;
	while (in.peek() != 'd')
	{	
		count++;
#ifdef DEBUG
		cout << (int)(in.peek()) << " ";
#endif // DEBUG
		in.ignore(1);
	};
#ifdef DEBUG
	cout << count << "\n";
#endif // DEBUG

	int pos = in.tellg();
	in.seekg(pos, ios::end);

	totalBytes = in.tellg();
	in.seekg(pos, ios::beg);

	BUFFER_SIZE = min(totalBytes, (size_t)BUFFER_SIZE);

	in.read(BUFFER, BUFFER_SIZE);

#ifdef DEBUG
	cout << "BYTES Read : " << BUFFER_SIZE << "\n";
#endif // DEBUG

	ByteReader.Reset(BUFFER_SIZE, BUFFER);

	//ByteReader.Flush(count);
	cout << "SubChunk2ID: long " << ByteReader.ShowBE(4) << "\n";
	cout << "SubChunk2ID: " << ByteReader.ReadString(4) << "\n";
	delete [] BUFFER;
	return 0;
}

