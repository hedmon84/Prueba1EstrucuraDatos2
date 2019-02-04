#include <cstring>
#include <iostream>
#include "SizeDesco.h"

using namespace std;

SizeDesco::SizeDesco()
{
	this->name = new char[30];
	this->job = new char[20];
}

SizeDesco::~SizeDesco()
{
	delete[] this->name;
	delete[] this->job;
	delete this->dataFile;
}

void SizeDesco::printRegister()
{
	cout << "Id: " << this->id << endl;
	cout << "Name: " << this->name << endl;
	cout << "Job: " << this->job << endl;
	cout << "Salary: " << this->salary << endl;
}

char *SizeDesco::toChar()
{
	const int size = this->getSize();
	char *data = new char[size];
	int position = 0;

	memcpy(&data[position], reinterpret_cast<char *>(&this->id), sizeof(this->id));
	position += sizeof(this->id);
	memcpy(&data[position], this->name, 30);
	position += 30;
	memcpy(&data[position], reinterpret_cast<char *>(&this->salary), sizeof(this->salary));
	position += sizeof(this->salary);
	memcpy(&data[position], this->job, 20);

	return data;
}

void SizeDesco::fromChar(char *data)
{
	int postion = 0;
	memcpy(&this->id, &data[postion], sizeof(this->id));
	postion += sizeof(this->id);
	memcpy(this->name, &data[postion], 30);
	postion += 30;
	memcpy(&this->salary, &data[postion], sizeof(this->salary));
	postion += sizeof(this->salary);
	memcpy(this->job, &data[postion], 20);
}

void SizeDesco::openFile(char *name)
{
	this->dataFile = new DataFile(name);
}

void SizeDesco::writeIntoFile()
{
	this->dataFile->open(std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
	this->dataFile->write(this->toChar(), this->getSize());
	this->dataFile->close();
}

void SizeDesco::readIntoFile(int position)
{
	this->dataFile->open();
	char *data = this->dataFile->read(position, this->getSize());
	this->fromChar(data);
	this->dataFile->close();
	delete data;
}

void SizeDesco::closeFile()
{
	this->dataFile->close();
}

int SizeDesco::getSize()
{
	return sizeof(this->id) + 30 + 20 + sizeof(this->salary);
}
