
#include <sstream>
#include <iostream>
#include "mem_sim_cache.h"
#include "mem_sim_memory.h"
#include "mem_sim_parser.h"
#include "mem_sim_debugger.h"
#include "mem_sim_exceptions.h"


int main(int argc, char *argv[]){
	unsigned addressBits;
	unsigned bytesPerWord;
	unsigned wordsPerBlock;
	unsigned blocksPerSet;
	unsigned setsPerCache;
	unsigned hitTime;
	unsigned memReadTime;
	unsigned memWriteTime;
	if (argc < 8)
	{
		addressBits = 10;
		bytesPerWord = 8;
		wordsPerBlock = 4;
		blocksPerSet = 2;
		setsPerCache = 10;
		hitTime = 0;
		memReadTime = 0;
		memWriteTime = 0;
	}
	else
	{
		addressBits = *(unsigned*)argv[0];
		bytesPerWord = *(unsigned*)argv[1];
		wordsPerBlock = *(unsigned*)argv[2];
		blocksPerSet = *(unsigned*)argv[3];
		setsPerCache = *(unsigned*)argv[4];
		hitTime = *(unsigned*)argv[5];
		memReadTime = *(unsigned*)argv[6];
		memWriteTime = *(unsigned*)argv[7];
	}

	Memory memory(
		addressBits,
		bytesPerWord,
		wordsPerBlock,
		memReadTime,
		memWriteTime
		);

	Cache cache(
		bytesPerWord,
		wordsPerBlock,
		blocksPerSet,
		setsPerCache,
		hitTime,
		&memory
	);

	

	Debugger debugger;
	std::stringstream dataTest;
	unsigned bytesToLoad = 32;
	char* dataOut = new char[bytesToLoad];
	char dataIn[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2 };
	//debugger.forceCache(&cache);

	debugger.printCache(dataTest, &cache);
	std::cout << dataTest.str() << std::endl;
	dataTest.str("");
	cache.store(dataIn, 5, 2*bytesPerWord);
	debugger.printCache(dataTest, &cache);
	std::cout << dataTest.str() << std::endl;
	cache.load(dataOut, 10, bytesToLoad);
	for (unsigned i = 0; i < bytesToLoad; i++)
		std::cout << (unsigned)dataOut[i];
	std::cout << std::endl;
	getchar();
	delete[] dataOut;
}