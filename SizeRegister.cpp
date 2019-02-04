#include <iostream>
#include "SizeRegister.h"
#include "cstring"

using namespace std;

SizeRegister::SizeRegister()
{
}

SizeRegister::~SizeRegister()
{
	delete[] this->name;
	delete[] this->job;
	delete this->dataFile;
}

void SizeRegister::printRegister()
{
	cout << "Id: " << this->id << endl;
	cout << "Name: " << this->name << endl;
	cout << "Job: " << this->job << endl;
	cout << "Salary: " << this->salary << endl;
}

char *SizeRegister::toChar()
{
	const int size = this->getSize();
	char *data = new char[size];

	memcpy(data, reinterpret_cast<char *>(&this->id), sizeof(this->id));
	memcpy(data + sizeof(this->id), reinterpret_cast<char *>(&this->sizeName), sizeof(this->sizeName));
	memcpy(data + sizeof(this->id) + sizeof(this->sizeName), this->name, this->sizeName);
	memcpy(data + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName, reinterpret_cast<char *>(&this->salary), sizeof(this->salary));
	memcpy(data + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary), reinterpret_cast<char *>(&this->sizeJob), sizeof(this->sizeJob));
	memcpy(data + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary) + sizeof(this->sizeJob), this->job, this->sizeJob);

	return data;
}

void SizeRegister::fromChar(char *data)
{
	memcpy(&this->id, data, sizeof(this->id));

	memcpy(&this->sizeName, data + sizeof(this->id), sizeof(this->sizeName));
	this->name = new char[this->sizeName];

	memcpy(this->name, data + sizeof(this->id) + sizeof(this->sizeName), this->sizeName);

	memcpy(&this->salary, data + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName, sizeof(this->salary));

	memcpy(&this->sizeJob, data + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary), sizeof(this->sizeJob));
	this->job = new char[this->sizeJob];

	memcpy(this->job, data + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary) + sizeof(this->sizeJob), this->sizeJob);
}

void SizeRegister::openFile(char *name)
{
	this->dataFile = new DataFile(name);
}

void SizeRegister::writeIntoFile()
{
	this->dataFile->open(std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
	this->dataFile->write(this->toChar(), this->getSize());
	this->dataFile->close();
}

void SizeRegister::readIntoFile(int position)
{
	this->dataFile->open();
	int countSize = 0;

	for (int i = 0; i <= position; i++)
	{
		this->id = *(reinterpret_cast<int *>(this->dataFile->read(countSize, sizeof(int))));
		this->sizeName = *(reinterpret_cast<int *>(this->dataFile->read(countSize + sizeof(int), sizeof(int))));
		this->name = this->dataFile->read(countSize + sizeof(this->id) + sizeof(this->sizeName), this->sizeName);
		this->salary = *(reinterpret_cast<double *>(this->dataFile->read(countSize + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName, sizeof(double))));
		this->sizeJob = *(reinterpret_cast<int *>(this->dataFile->read(countSize + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary), sizeof(int))));
		this->job = this->dataFile->read(countSize + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary) + sizeof(this->sizeJob), this->sizeJob);

		countSize += this->getSize();
	}
	this->dataFile->close();
}

void SizeRegister::closeFile()
{
	this->dataFile->close();
}

int SizeRegister::getSize()
{
	return sizeof(this->id) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary) + sizeof(this->sizeJob) + this->sizeJob;
}
