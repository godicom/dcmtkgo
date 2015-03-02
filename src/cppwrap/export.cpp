#include <iostream>
#include <dcmtk/dcmdata/dcdatset.h>

extern "C"
{
	#include "export.h"
}


void doSomeJob()
{
	std::cout << "Hello from lib\n" ;
	std::cout.flush();
}


void printDCMTags(const char * fileName)
{
	DcmDataset ds;
	ds.loadFile(fileName);
	ds.print(std::cout);
}
