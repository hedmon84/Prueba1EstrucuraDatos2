#include "datafile.h"

class Delimiter
{
private:
	DataFile *dataFile;

	int id;
	char *name;
	double salary;
	char *job;

public:
	Delimiter();
	~Delimiter();

	void printRegister();
	char *toChar();
	void fromChar(char *data);
	void readFromFile(int position);
	void writeIntoFile();
	int getSize();
};
