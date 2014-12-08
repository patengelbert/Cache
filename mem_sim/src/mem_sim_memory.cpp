#include "mem_sim_memory.h"


Memory::Memory(
	unsigned addressBits,
	unsigned bytesPerWord,
	unsigned wordsPerBlock,
	unsigned memReadTime,
	unsigned memWriteTime
	) : bytesPerWord(bytesPerWord), wordsPerBlock(wordsPerBlock), memReadTime(memReadTime), memWriteTime(memWriteTime)
{
	blockLength = wordsPerBlock*bytesPerWord;
	memorySize = (2 << (addressBits-1)) / blockLength;
	bytesPerBlock = bytesPerWord*wordsPerBlock;
	data = new char*[memorySize];
	for (unsigned i = 0; i < memorySize; i++)
	{
		data[i] = new char[blockLength];
		for (unsigned j = 0; j < blockLength; j++)
			data[i][j] = 0;
	}
}

Memory::~Memory()
{
	for (unsigned i = 0; i < memorySize; i++)
		delete[] data[i];
	delete[] data;
}

void Memory::read(char dataOut[], unsigned address, unsigned loadLength)
{
	unsigned blockNumber = address / bytesPerBlock;
	unsigned offset = address - (blockNumber*bytesPerBlock);
	int blocksToLoad = ((offset + loadLength) / bytesPerBlock) + ((offset+loadLength)% bytesPerBlock != 0)
	while (blocksToLoad > 0)
	{
		readWord(dataOut, blockNumber);
		blocksToLoad--;
		dataOut += bytesPerBlock;
		blockNumber++;
	}

}

void Memory::write(char dataIn[], unsigned address, unsigned loadLength)
{

}

void Memory::readWord(char dataOut[], unsigned blockNumber)
{
	for (int i = 0; i < bytesPerBlock; i++)
		dataOut[i] = data[blockNumber][i];
}

void Memory::writeWord(char dataIn[], unsigned blockNumber)
{
	for (int i = 0; i < bytesPerBlock; i++)
		data[blockNumber][i] = dataIn[i];
}