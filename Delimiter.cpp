#include <cstring>
#include "Delimiter.h"

#include <string>
#include <iostream>

using namespace std;

Delimiter::Delimiter()
{
	this->dataFile = new DataFile((char *)"delimiterfile.dat");
}

Delimiter::~Delimiter()
{
	delete this->dataFile;
}

void Delimiter::writeIntoFile()
{
	this->dataFile->open(std::ios::app | std::ios::in | std::ios::out | std::ios::binary);

	if (this->dataFile->isEmpty())
	{
		this->dataFile->write((char *)"|", sizeof(char));
	}

	this->dataFile->write(this->toChar(), this->getSize());
	this->dataFile->close();
}
char *Delimiter::toChar()
{
	char recordDelimiter = '|';
	char fieldDelimiter = ';';
	char *data = new char[this->getSize()];

	memcpy(data, reinterpret_cast<char *>(&this->id), sizeof(int));
	data += sizeof(int);
	memcpy(data, &fieldDelimiter, sizeof(char));
	data += sizeof(char);
	memcpy(data, reinterpret_cast<char *>(this->name), strlen(this->name));
	data += strlen(this->name);
	memcpy(data, &fieldDelimiter, sizeof(char));
	data += sizeof(char);
	memcpy(data, reinterpret_cast<char *>(&this->salary), sizeof(double));
	data += sizeof(double);
	memcpy(data, &fieldDelimiter, sizeof(char));
	data += sizeof(char);
	memcpy(data, reinterpret_cast<char *>(this->job), strlen(this->job));
	data += strlen(this->job);
	memcpy(data, &recordDelimiter, sizeof(char));

	return data;
}

void Delimiter::fromChar(char *data)
{
	char recordDelimiter = '|';
	char fieldDelimiter = ';';

	int position = 0;

	char *token = strtok(data, &fieldDelimiter);
	int length = strlen(token);

	memcpy(&this->id, &data[position], sizeof(int));
	position += sizeof(int) + 1;

	token = strtok(nullptr, &fieldDelimiter);
	length = strlen(token);

	memcpy(this->name, &data[position], length);
	position += length + 1;

	token = strtok(nullptr, &fieldDelimiter);

	memcpy(&this->salary, &data[position], sizeof(double));
	position += sizeof(double) + 1;

	token = strtok(nullptr, &recordDelimiter);
	length = strlen(token);
	memcpy(this->job, &data[position], length);
}

void Delimiter::printRegister()
{
	std::cout << "Id: " << this->id << endl;
	std::cout << "Name: " << this->name << endl;
	std::cout << "Job: " << this->job << endl;
	std::cout << "Salary: " << this->salary << endl;
}

void Delimiter::readFromFile(int position)
{
	char *data;

	char *byte = this->dataFile->read(0, 1);

	char fieldDelimiter = '|';

	while (byte != &fieldDelimiter)
	{
		memcpy(&data[position], byte, 1);
		byte = this->dataFile->read(0, 1);
	}

	if (byte == &fieldDelimiter)
	{
		memcpy(&data[position], byte, 1);
	}

	fromChar(data);
}

int Delimiter::getSize()
{
	return sizeof(this->id) + strlen(this->name) + sizeof(this->salary) + strlen(this->job) + 1 + 3;
}