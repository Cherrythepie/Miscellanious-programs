#ifndef FILECLASS_H
#define FILECLASS_H

#include <iostream>
#include <fstream>ss
#include <iomanip>
#include <string>
#include <cctype>

#include "Implementation.h"

using namespace std;

class FileClass
{
private:

public:
//	FileClass();
//	~FileClass();

void FileClass::SavetoFile(ProductType &Product);	// Saves a Product's information to its Product File

void FileClass::ReadFromFile(ProductType &Product);	// gets the file name from the name of the product.

void FileClass::Empty(char buffer[]);	// Empties an array of text.

};

#endif;