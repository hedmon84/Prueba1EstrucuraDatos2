#ifndef DATAFILE_H
#define DATAFILE_H

#include <fstream>

class DataFile
{
private:
	char *path;

public:
	std::fstream *file;
	DataFile();
	~DataFile();
	DataFile(char *path);
	void open();
	void open(std::ios_base::openmode mode);
	void close();
	void write(char *data, unsigned int position, unsigned int size);
	void write(char *data, unsigned int size);
	char *read(unsigned int position, unsigned int size);
	long tellp();
	long tellg();
	bool isEmpty();
};

#endif