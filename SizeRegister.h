#ifndef SizeRegister_H
#define SizeRegister_H

#include "datafile.h"

class SizeRegister
{
private:
	DataFile *dataFile;
	int id;
	int sizeName;
	char *name;
	double salary;
	int sizeJob;
	char *job;

public:
	SizeRegister();
	~SizeRegister();

	void printRegister();
	char *toChar();
	void fromChar(char *data);
	void openFile(char *name);
	void writeIntoFile();
	void readIntoFile(int position);
	void closeFile();
	int getSize();
};

#endif