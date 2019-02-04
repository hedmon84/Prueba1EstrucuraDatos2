#include <cstring>
#include <iostream>
#include "DataFile.h"
#include "Delimiter.h"
#include "SizeDesco.h"
#include "SizeRegister.h"

using namespace std;
#include <iostream>



char *DescoSize(int id, char *name, double salary, char *job, int sizeName, int sizeJob)
{
	char *data = new char[sizeof(id) + sizeof(sizeName) + sizeName + sizeof(salary) + sizeof(sizeJob) + sizeJob];
	int position = 0;

	memcpy(&data[position], reinterpret_cast<char *>(&id), sizeof(id));
	position += +sizeof(id);
	memcpy(&data[position], reinterpret_cast<char *>(&sizeName), sizeof(sizeName));
	position += sizeof(sizeName);
	memcpy(&data[position], name, sizeName);
	position += sizeName;
	memcpy(&data[position], reinterpret_cast<char *>(&salary), sizeof(salary));
	position += sizeof(salary);
	memcpy(&data[position], reinterpret_cast<char *>(&sizeJob), sizeof(sizeJob));
	position += sizeof(sizeJob);
	memcpy(&data[position], job, sizeJob);

	return data;
}

char *FizSize(int id, char name[30], double salary, char job[20])
{
	char *data = new char[sizeof(int) + 30 + 20 + sizeof(salary)];
	int position = 0;

	memcpy(&data[position], reinterpret_cast<char *>(&id), sizeof(int));
	position += sizeof(int);
	memcpy(data, name, 30);
	position += 30;
	memcpy(&data[position], reinterpret_cast<char *>(&salary), sizeof(salary));
	position += sizeof(salary);
	memcpy(&data[position], job, 20);

	return data;
}

int main()
{
	int option;
	char continueInput = 'a';

	while (continueInput == 'a')
	{
	
		cout << "*  1) Escribir fixed size file " << endl;
		cout << "*  2) Leer fixed size file  " << endl;
		cout << "*  3) Escribir known size file" << endl;
		cout << "*  4) Leer known size file " << endl;
		cout << "*  5) Escribir delimiter file" << endl;
		cout << "*  6) Leer delimiter file " << endl;
		

		cout << "Ingrese una opción:" << endl;

		cin >> option;

		switch (option)
		{
		case 1:

		{
			char fixedName[40], fixedJob[30];
			int fixedId;
			double fixedSalary;

			SizeRegister->openFile((char *)"fixedSizeFieldFile.dat");

			cout << "Ingrese el id: " << endl;
			cin >> fixedId;

			cout << "Ingrese el nombre: " << endl;
			cin >> fixedName;

			cout << "Ingrese el trabajo: " << endl;
			cin >> fixedJob;

			cout << "Ingrese el salario: " << endl;
			cin >> fixedSalary;

			char *data = FizSize(fixedId, fixedName, fixedSalary, fixedJob);

			SizeRegister->fromChar(data);
			SizeRegister->writeIntoFile();
			SizeRegister->closeFile();
		}

		break;

		case 2:

		{
			int fixedPosition;
			cout << "Ingrese la posición: " << endl;
			cin >> fixedPosition;

			SizeRegister->openFile((char *)"Filefixed.dat");

			SizeRegister->readIntoFile(fixedPosition);
			SizeRegister->printRegister();
			SizeRegister->closeFile();
		}

		break;

		case 3:

		{
			char knownSizeName[30], knownSizeJob[20];
			int knownSizeId;
			double knownSizeSalary;

			SizeDesco->openFile((char *)"knownSizeFieldFile.dat");

			cout << "Ingrese el id: " << endl;
			cin >> knownSizeId;

			cout << "Ingrese el nombre: " << endl;
			cin >> knownSizeName;

			cout << "Ingrese el trabajo: " << endl;
			cin >> knownSizeJob;

			cout << "Ingrese el salario: " << endl;
			cin >> knownSizeSalary;

			char *data = DescoSize(knownSizeId, knownSizeName, knownSizeSalary, knownSizeJob, sizeof(knownSizeName), sizeof(knownSizeJob));

			SizeDesco->fromChar(data);
			SizeDesco->writeIntoFile();
		}

		break;
		case 4:

		{
			int knownSizePosition;
			cout << "Ingrese la posición: " << endl;
			cin >> knownSizePosition;

			SizeDesco->openFile((char *)"FilseDesco.dat");

			SizeDesco->readIntoFile(knownSizePosition);
			SizeDesco->printRegister();
		}

		break;
		case 5:
		{
			char name[30], job[20];
			int id;
			double salary;

			SizeRegister->openFile((char *)"DelimitefILE.dat");

			cout << "Ingrese el id: " << endl;
			cin >> id;

			cout << "Ingrese el nombre: " << endl;
			cin >> name;

			cout << "Ingrese el trabajo: " << endl;
			cin >> job;

			cout << "Ingrese el salario: " << endl;
			cin >> salary;

			char *data = FizSize(id, name, salary, job);

			SizeRegister->fromChar(data);
			SizeRegister->writeIntoFile();
			SizeRegister->closeFile();
		}

		break;
		case 6:
		{
			int delimiterPosition;
			cout << "Ingrese la posición: " << endl;
			cin >> delimiterPosition;

			Delimiter->readFromFile(delimiterPosition);
			Delimiter->printRegister();
		}
		break;
		}

		cin >> continueInput;
	}

	return 0;
}
