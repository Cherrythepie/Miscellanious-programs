#include "FileClass.h"

/*
FileClass::FileClass()
{

}
*/

void FileClass::SavetoFile(ProductType &Product)
{
	char FilePath[304] = {0};
	if(Product.Type != 13)
		Product.numParts++;	// in the Driver, the number of parts starts at 0. We have to increase the count on numParts, so that all the items are included in the save file.

	if(Product.Type == 13)
	{
		Product.ME = 0;
		Product.UnitsProduced = 0;
	}

//	strcat(FilePath, "\\Items\\");
	strcat(FilePath, Product.Name);
	strcat(FilePath, ".txt");

	ofstream WriteFile(FilePath);

	WriteFile << Product.Name
		      << "\n"
			  << Product.numParts
			  << "\n";

	for (int i = 0; i < Product.numParts; i++)
	{
		WriteFile << Product.parts[i].partName
			      << "\n"
		          << Product.partQuantities[i]
		          << "\n";
	}

	for (int i = 0; i < 5; i++)
	{
		WriteFile << fixed << Product.Price[i]
				  << "\n";
	}

	WriteFile << Product.Type
			  << "\n"
			  << Product.ME
			  << "\n"
			  << Product.UnitsProduced
			  << "\n";

	WriteFile.close();
}

void FileClass::ReadFromFile(ProductType &Product)
{
	char FilePath[304] = {0};

//	strcat(FilePath, "\\Items\\");
	strcat(FilePath, Product.Name);
	strcat(FilePath, ".txt");

	ifstream ReadFile(FilePath);

	if(!ReadFile)
	{
		ReadFile.close();
		ofstream newFile(FilePath);
		newFile << "  ";
		newFile.close();
		return;
	}

	ReadFile.getline(Product.Name, 254);
	
	char temp[304] = {0};

	ReadFile.getline(temp, 303);
	Product.numParts = atoi(temp);
	Empty(temp);	// empties 'temp'

	for(int i = 0; i < Product.numParts; i++)
	{
		ReadFile.getline(Product.parts[i].partName, 254);
		ReadFile.getline(temp, 303);

		Product.partQuantities[i] = atoi(temp);
		Empty(temp);	// empties 'temp'
	}

	// starts getting the hub prices

	// Amarr
	ReadFile.getline(temp, 303);
	Product.Price[0] = atof(temp);
	Empty(temp);	// empties 'temp'
	
	// Jita
	ReadFile.getline(temp, 303);
	Product.Price[1] = atof(temp);
	Empty(temp);	// empties 'temp'
	
	// Hek
	ReadFile.getline(temp, 303);
	Product.Price[2] = atof(temp);
	Empty(temp);	// empties 'temp'
	
	// Rens
	ReadFile.getline(temp, 303);
	Product.Price[3] = atof(temp);
	Empty(temp);	// empties 'temp'
	
	// Dodixie
	ReadFile.getline(temp, 303);
	Product.Price[4] = atof(temp);
	Empty(temp);	// empties 'temp'

	ReadFile >> ws
		     >> Product.Type
		     >> ws;

	ReadFile >> Product.ME
		     >> ws;

	ReadFile >> Product.UnitsProduced
		     >> ws;

}

void FileClass::Empty(char buffer[])
{
	// Purpose: Fills the character array, "buffer", with spaces(blanks).

	for(int i = 0; i < sizeof(buffer); i++)
		buffer[i] = ' ';
}







/*
FileClass::~FileClass()
{

}
*/