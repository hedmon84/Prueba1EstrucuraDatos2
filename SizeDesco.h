#ifndef SizeDisco_H
#define SizeDisco_H

#include "datafile.h"

class SizeDesco
{
private:
	DataFile *dataFile;
	int id;
	char *name;
	double salary;
	char *job;

public:
	SizeDesco();
	~SizeDesco();
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