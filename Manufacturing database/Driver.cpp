#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>

#include "FileClass.h"
#include "Implementation.h"

using namespace std;

ProductType Initialize_ProductType();
void ManufactureSomething(char itemName[]);
double ManufactureSomething(char itemName[], bool something, double ME_Job, int jobRuns, bool mineralPriceTrue_marketPriceFalse);
double CostToManufacture(ProductType &item, double ME_Job, bool mineralPriceTrue_marketPriceFalse /*, double &doubleTotal*/ );
void Case9();

int main(int choice, char Pname[])
{
START:
	cout << "Options: \n"
		 << "1)  Add new Product \n"
		 << "2)  Update mineral Prices \n"
		 << "3)  Update ore Prices \n"
		 << "4)  Update Product \n"
		 << "6)  View All Products \n"
		 << "7)  View All ores/minerals \n"
		 << "8)  Manufacture something \n"
		 << "9)  Sort Best to Manufacture \n"
		 << "10) Quit \n"
		 << endl;
	
	char parseChoiceNumber[2501] = {0};
	int choiceNumber = 0;

//WHICH_NUMBER:
	cout << "Press ENTER" << endl;
	cin.ignore();

	cout << "Which Number: ";
	cin.getline(parseChoiceNumber, 2500);

	//if(parseChoiceNumber[0] == ' ')
	//	goto WHICH_NUMBER;

	if(isalpha(parseChoiceNumber[0]) || atoi(parseChoiceNumber) == 5)
	{
		cout << "Not a number. Or you typed \"5\" \n" << endl;
		goto START;
	}

	choiceNumber = atoi(parseChoiceNumber);

	cout << endl;

	while(choiceNumber != 10)
	{
		switch (choiceNumber)
		{
			case 1:	// Add new Product
			{
				ProductType newProduct = Initialize_ProductType();

//				cout << "Note: Use \"_\" in the place of spaces. \n";
				cout << "Product Name: ";
				cin >> ws;
				cin.getline(newProduct.Name, 254);
				
				ofstream ProductListFileOut;

				ProductListFileOut.open("ProductList.txt" , ios::app ); 
				ProductListFileOut << newProduct.Name
					               << endl;

				for (int j = 0; j < 255; j++)
						tolower(newProduct.Name[j]);

				char input[255] = {0};
				int i = 0;
				
				do
				{
					// part name
					cout << "\n"
						 << i + 1
						 << ") Part Name: ";
					cin >> ws;
					cin.getline(input, 254);

					for (int j = 0; j < 255; j++)
						tolower(input[j]);

					if(strcmp(input, "done") == 0)
					{
						strcpy(newProduct.parts[i].partName, "None");
						newProduct.partQuantities[i] = 0;
						break;
					}

					if(strcmp(input, "cancel") == 0)
					{
						goto START;
					}

					strcpy(newProduct.parts[i].partName, input);
					// end part name

					// part Quantities
					cout << "How much of this ingredient: ";
					cin  >> newProduct.partQuantities[i];

					newProduct.numParts = i;	// saves the number of parts (i) before 'i' is incremented.

				}
				while( (strcmp(input, "done") != 0)  && (++i < 100) );

				cout << "\n"
					 << "Please list the item's price at the 5 trade Hubs (Amarr, Jita, Hek, Rens, Dodixie)."
					 << "\n"
					 << "If you do not want to list a specific price, then input the price as \"0\"." //  (out of lazyness ;)  )
					 << "\n"
					 << "Wait for the name of the Trade Hub to appear before inputing the item's price."
					 << endl;

				cout << "Amarr: ";
				cin  >> newProduct.Price[0];

				cout << "Jita: ";
				cin  >> newProduct.Price[1];

				cout << "Hek: ";
				cin  >> newProduct.Price[2];

				cout << "Rens: ";
				cin  >> newProduct.Price[3];

				cout << "Dodixie: ";
				cin  >> newProduct.Price[4];

				
				cout << "\n \n"
					 << "Item type: ";
				cin  >> newProduct.Type;
				
				cout << "\n \n"
					 << "BluePrint ME: ";
				cin  >> newProduct.ME;

				cout << "\n \n"
					 << "Units Produced per Job Run: ";
				cin  >> newProduct.UnitsProduced;

				cout << "\n"
					 << "Adding Item to Database..."
					 << endl;

				FileClass newFile;

				newFile.SavetoFile(newProduct);

				goto START;

			}
			
			case 2:	// Update Mineral Prices
			{
				ProductType mineral;

				cout << "When the mineral name appears, type the price for that mineral."
					 << "\n"
					 << "For each mineral you will also need to type in 5 prices associated with each trade hub."
					 << "\n"
					 << "If you don't know a trade hub price, or do not want to update a mineral's price, type '0'"
					 << "\n"
					 << endl;

				for(int i = 0; i < 8; i++)
				{
					ProductType mineralProduct = Initialize_ProductType();

					switch (i)
					{
					case 0:	// Tritanium
						strcpy(mineralProduct.Name, "Tritanium");
						cout << "\n"
							 << "Tritanium: "
							 << "\n";
						break;
					case 1:	// Pyerite
						strcpy(mineralProduct.Name, "Pyerite");
						cout << "\n"
							 << "Pyerite: "
							 << "\n";
						break;
					case 2:	// Mexallon
						strcpy(mineralProduct.Name, "Mexallon");
						cout << "\n"
							 << "Mexallon: "
							 << "\n";
						break;
					case 3:	// Isogen
						strcpy(mineralProduct.Name, "Isogen");
						cout << "\n"
							 << "Isogen: "
							 << "\n";
						break;
					case 4:	// Nocxium
						strcpy(mineralProduct.Name, "Nocxium");
						cout << "\n"
							 << "Nocxium: "
							 << "\n";
						break;
					case 5:	// Megacyte
						strcpy(mineralProduct.Name, "Zydrine");
						cout << "\n"
							 << "Zydrine: "
							 << "\n";
						break;
					case 6:	// Zydrine
						strcpy(mineralProduct.Name, "Megacyte");
						cout << "\n"
							 << "Megacyte: "
							 << "\n";
						break;
					case 7:	// Morhpite
						strcpy(mineralProduct.Name, "Morphite");
						cout << "\n"
							 << "Morphite: "
							 << "\n";
						break;
					}

					FileClass MineralFile;

					MineralFile.ReadFromFile(mineralProduct);
					double tempPrice = 0.00;
					
					cout << "Amarr: ";
					cin  >> tempPrice;
					if(tempPrice != 0)
						mineralProduct.Price[0] = tempPrice;

					cout << "Jita: ";
					cin  >> tempPrice;
					if(tempPrice != 0)
						mineralProduct.Price[1] = tempPrice;

					cout << "Hek: ";
					cin  >> tempPrice;
					if(tempPrice != 0)
						mineralProduct.Price[2] = tempPrice;

					cout << "Rens: ";
					cin  >> tempPrice;
					if(tempPrice != 0)
						mineralProduct.Price[3] = tempPrice;

					cout << "Dodixie: ";
					cin  >> tempPrice;
					if(tempPrice != 0)
						mineralProduct.Price[4] = tempPrice;

					mineralProduct.Type = 13;

					MineralFile.SavetoFile(mineralProduct);

					cout << "\n"
						 << "Adding Item to Database..."
						 << endl;
				}
				goto START;
			}

			case 3:	// Update Ore Prices
			{
				
				goto START;
			}
			
			case 4:	// Update Product
			{
				
				START4:
				cout << "What do you want to Update?"
					 << "\n"
					 << "1) Update Market Price \n"
					 << "2) Add a component \n"				// increases number of parts
					 << "3) Remove a component \n"			// decreases number of parts
					 << "4) Update a component amount \n"
					 << "5) Change a component name \n"
					 << "6) Change the Product's type \n"
					 << "7) Done. \n"
					 << endl;

				choiceNumber = 0;

				cin  >> choiceNumber;

				switch (choiceNumber)
				{
				case 1:	// Update Market Price of an item
				{
					char itemName[304] = {0};
					ProductType item;

					cout << "Name of Item: ";
					cin  >> ws;
					cin.getline(itemName, 303);

					strcpy(item.Name, itemName);	// this will probably be needed else-where

					FileClass itemFile;
					itemFile.ReadFromFile(item);

					double tempPrice = 0.00;
					
					cout << "Amarr: ";
					cin  >> tempPrice;
					if(tempPrice != 0)
						item.Price[0] = tempPrice;

					cout << "Jita: ";
					cin  >> tempPrice;
					if(tempPrice != 0)
						item.Price[1] = tempPrice;

					cout << "Hek: ";
					cin  >> tempPrice;
					if(tempPrice != 0)
						item.Price[2] = tempPrice;

					cout << "Rens: ";
					cin  >> tempPrice;
					if(tempPrice != 0)
						item.Price[3] = tempPrice;

					cout << "Dodixie: ";
					cin  >> tempPrice;
					if(tempPrice != 0)
						item.Price[4] = tempPrice;

					itemFile.SavetoFile(item);

					cout << "Saving Update to DataBase... \n"
						 << endl;

					goto START4;
				}
				case 2:	// Add a component to an item.
				{
					char itemName[304] = {0};
					ProductType item;

					cout << "Name of Item: ";
					cin  >> ws;
					cin.getline(itemName, 303);
					strcpy(item.Name, itemName);

					FileClass itemFile;
					itemFile.ReadFromFile(item);

					int index = item.numParts;
					do
					{
						cout << "Type the component name or type \"done\" if you are... done \n"
							 << "Component name: ";
						cin  >> ws;
						cin.getline(itemName, 303);

						// check if the inputed component name already exists within the product file or if the user is done.
						for (int i = 0; i < index; i++)
						{
							if(strcmp(itemName, item.parts[i].partName) == 0 || strcmp(itemName, "done") == 0)
							{
								cout << "Sorry, that component already exists. \n"
									 << "Would you like to (1) add another component or (2) stop adding new components?"
									 << endl;
								int choice = 0;
								cin >> choice;

								if(choice == 1)
									goto ENDWHILE2;
								if(choice == 2)
									goto ENDDO2;
							}
						}

						index++; // make room for a new component in the array.
						strcpy(item.parts[index].partName, itemName);

						cout << "Quantity of these components: ";
						cin >> item.partQuantities[index];
ENDDO2:;				
					}
					while(index < 99);
ENDWHILE2:;
					item.numParts = index;
					itemFile.SavetoFile(item);

					goto START4;
				}
				case 3:	// Remove a component from an item.
				{
					char itemName[304] = {0};
					ProductType item;

					cout << "Name of Item: ";
					cin  >> ws;
					cin.getline(itemName, 303);

					FileClass itemFile;
					itemFile.ReadFromFile(item);

					int index = item.numParts;
					do
					{
						cout << "Type the component name or type \"done\" if you are... done \n"
							 << "Component name: ";
						cin  >> ws;
						cin.getline(itemName, 303);

						// check if the inputed component name does not exist within the product file or if the user is done.
						int i = 0;
						for (; i < index; i++)
						{
							if(strcmp(itemName, item.parts[i].partName) != 0 || strcmp(itemName, "done") == 0)
							{
								cout << "Sorry, that component does not exist. \n"
									 << "Would you like to (1) remove another component or (2) stop removing components?"
									 << endl;
								int choice = 0;
								cin >> choice;

								if(choice == 1)
									goto ENDWHILE3;
								if(choice == 2)
									goto ENDDO3;
							}
						}

						// shunts products in the array to wash over the old component that was removed.
						for(i; i <= index; i++)
						{
							strcpy(item.parts[i].partName, item.parts[i+1].partName);
							item.partQuantities[i] = item.partQuantities[i+1];
						}
ENDDO3:;				
					}
					while(index > 1);
ENDWHILE3:;
					item.numParts = index;
					itemFile.SavetoFile(item);
					goto START4;
				}
				case 4:	// Update a component amount.
				{
					char itemName[304] = {0};
					ProductType item;

					cout << "Name of Item: ";
					cin  >> ws;
					cin.getline(itemName, 303);

					FileClass itemFile;
					itemFile.ReadFromFile(item);

					int index = item.numParts;
					do
					{
						cout << "Type the component name or type \"done\" if you are... done \n"
							 << "Component name: ";
						cin  >> ws;
						cin.getline(itemName, 303);

						// check if the inputed component name does not exist within the product file or if the user is done.
						int i = 0;
						for (; i < index; i++)
						{
							if(strcmp(itemName, item.parts[i].partName) != 0 || strcmp(itemName, "done") == 0)
							{
								cout << "Sorry, that component does not exist. \n"
									 << "Would you like to (1) remove another component or (2) stop removing components?"
									 << endl;
								int choice = 0;
								cin >> choice;

								if(choice == 1)
									goto ENDWHILE4;
								if(choice == 2)
									goto ENDDO4;
							}
						}

						cout << "New Quantity of these components: ";
						cin >> item.partQuantities[i];
ENDDO4:;				
					}
					while(index < 99);
ENDWHILE4:;
					itemFile.SavetoFile(item);
					goto START4;
				}
				case 5:	// Change a component name.
				{
					char itemName[304] = {0};
					ProductType item;

					cout << "Name of Item: ";
					cin  >> ws;
					cin.getline(itemName, 303);

					FileClass itemFile;
					itemFile.ReadFromFile(item);

					int index = item.numParts;
					do
					{
						cout << "Type the component name or type \"done\" if you are... done \n"
							 << "Component name: ";
						cin  >> ws;
						cin.getline(itemName, 303);

						// check if the inputed component name does not exist within the product file or if the user is done.
						int i = 0;
						for (; i < index; i++)
						{
							if(strcmp(itemName, item.parts[i].partName) != 0 || strcmp(itemName, "done") == 0)
							{
								cout << "Sorry, that component does not exist. \n"
									 << "Would you like to (1) remove another component or (2) stop removing components?"
									 << endl;
								int choice = 0;
								cin >> choice;

								if(choice == 1)
									goto ENDWHILE5;
								if(choice == 2)
									goto ENDDO5;
							}
						}

						char newName[304] = {0};
						cout << "The new component name for "
							 << item.Name
							 << " is: ";
						cin  >> ws;
						cin.getline(newName, 303);

						strcpy(item.parts[i].partName, newName);
ENDDO5:;				
					}
					while(index < 99);
ENDWHILE5:;
					itemFile.SavetoFile(item);
					goto START4;
				}
				case 6:	// Change a product's type.
				{
					char itemName[304] = {0};
					ProductType item;

					cout << "Name of Item: ";
					cin  >> ws;
					cin.getline(itemName, 303);

					FileClass itemFile;
					itemFile.ReadFromFile(item);

					cout << "The Item's current type is: "
						 << item.Type
						 << ". \n"
						 << "The Item's new Type will be: ";

/*						 << ". Do you still want to change the type? (Y/N) \n";
					char YesNo[26] = {0};
					cin.getline(YesNo, 25);

					if(tolower(YesNo[0]) == 'n')
						goto START4;

					// else 'y'
*/
					cin >> item.Type;

					itemFile.SavetoFile(item);

					goto START4;
				}
				case 7:	// Done.
				{

					goto START;
				}
				}
				



				goto START;
			}
			/*
			case 5:
			{
				
				goto START;
			}*/
			
			case 6:	// View All Products
			{
				ifstream ProductListFileIn;
				ProductListFileIn.open("ProductList.txt");

				char productName[301];

				while(!ProductListFileIn.eof())
				{
					ProductListFileIn.getline(productName, 300);
					cout << productName
						 << endl;
				}
				goto START;
			}
			
			case 7:	// View All Ores/Minerals
			{
				
				goto START;
			}

			case 8:	// Manufacture Something
			{
				// Purpose: This part of the program is designed to Find out how much it would cost to build something,
				//          How much money could be made from selling it at each trade hub,
				//          Which trade hubs to get each component from at the cheapest price (component as the x, hub as the y),
				//          ...
				
				char itemName[304] = {0};

				cout << "Name of Item to Manufacture: ";
				//cin >> ws;
				cin.getline(itemName, 303);

				ManufactureSomething(itemName);
				
				goto START;
			}

			case 9:
			{
				Case9();
			}
			goto START;
		}


	}


	return 0;
}

ProductType Initialize_ProductType()
{
	ProductType newProduct;

	for(int i = 0; i < 255; i++)
		newProduct.Name[i] = ' ';

	for(int i = 0; i < 100; i++)
		for(int j = 0; j < 255; j++)
			newProduct.parts[i].partName[j] = ' ';


	for(int i = 0; i < 5; i++)
		newProduct.Price[i] = 0;

	for(int i = 0; i < 100; i++)
		newProduct.partQuantities[i] = 0;

	newProduct.Type = 0;
	newProduct.numParts = 0;

	newProduct.Next = newProduct.Previous = newProduct.Root = NULL;

	newProduct.netProfit = 0;

	return newProduct;
}

void ManufactureSomething(char itemName[])
{
				std::locale loc("");
				std::cout.imbue(loc);

				ProductType item;
				bool mineralPriceTrue_marketPriceFalse = true;
				
				strcpy(item.Name, itemName);

				FileClass itemFile;
				itemFile.ReadFromFile(item);

				double ME_Job = 0;
				int jobRuns = 0;
				/*
				cout << "\n"
					 << "Blueprint (Integer) ME: ";
				cin  >> ME_Job;
				*/

				cout << "\n"
					 << "1) Station \n"
					 << "2) Assembly Array (2%) \n"
					 << "3) Thukker Component Assembly Array (15%) \n";
				cin  >> jobRuns;

				if(jobRuns == 2)
					item.ME += item.ME * .02;

				if(jobRuns == 3)
					item.ME += item.ME * .15;

				cout << "\n"
					 << "1) Use base material prices as costs \n"
					 << "2) Use component Prices as cost \n";
				cin  >> jobRuns;

				if(jobRuns == 1)
					mineralPriceTrue_marketPriceFalse = true;
				
				if(jobRuns == 2)
					mineralPriceTrue_marketPriceFalse = false;

				double totalCostToManufacture = CostToManufacture(item, item.ME, mineralPriceTrue_marketPriceFalse);

				cout << "\n"
					 << "Job cost for 1 run: ";
				cin  >> ME_Job;

				totalCostToManufacture += ME_Job;

				cout << "Number of Job Runs: ";
				cin  >> jobRuns;

				totalCostToManufacture *= jobRuns;

				double taxRate = 0;
				cout << "Tax percent on sell orders: ";
				cin  >> taxRate;

				char PrintOutSheetPath[301] = {0};
				strcpy(PrintOutSheetPath, itemName);
				strcat(PrintOutSheetPath, "_Figures.txt");
				ofstream PrintOutSheetFile(PrintOutSheetPath);


				cout << "\n"
					 << "The Cost to manufacture "
					 << jobRuns
					 << " runs of "
					 << item.UnitsProduced 
					 << " "
					 << itemName
					 << " is: "
					 << fixed << totalCostToManufacture
					 << endl;

				cout << "\n"
					 << "The Value of "
					 << jobRuns * item.UnitsProduced
					 << " "
					 << itemName
					 << " is: "
					 << fixed << item.Price[0] * jobRuns * item.UnitsProduced
					 << " isk."
					 << endl;

				cout << "\n"
					 << "The net value of Manufacturing this... is: "
					 << fixed << (item.Price[0] * jobRuns * item.UnitsProduced) - (totalCostToManufacture + item.Price[0] * .01 * taxRate)
					 << " isk."
					 << endl;

				cout << "For "
					 << jobRuns
					 << " runs of "
					 << item.UnitsProduced 
					 << " "
					 << itemName
					 << " "
					 << "per run, you will need: ";

				PrintOutSheetFile << "\n"
					 << "The Cost to manufacture "
					 << jobRuns
					 << " runs of "
					 << item.UnitsProduced 
					 << " "
					 << itemName
					 << " is: "
					 << fixed << totalCostToManufacture
					 << endl;

				PrintOutSheetFile << "\n"
					 << "The Value of "
					 << jobRuns * item.UnitsProduced
					 << " "
					 << itemName
					 << " is: "
					 << fixed << item.Price[0] * jobRuns * item.UnitsProduced
					 << " isk."
					 << endl;

				PrintOutSheetFile << "\n"
					 << "The net value of Manufacturing this... is: "
					 << fixed << (item.Price[0] * jobRuns * item.UnitsProduced) - (totalCostToManufacture + item.Price[0] * .01 * taxRate)
					 << " isk."
					 << endl;

				PrintOutSheetFile << "For "
					 << jobRuns
					 << " runs of "
					 << item.UnitsProduced 
					 << " "
					 << itemName
					 << " "
					 << "per run, you will need: ";


				for(int i = 0; i < item.numParts; i++)
				{
					ProductType componentItem;
					strcpy(componentItem.Name, item.parts[i].partName);

					itemFile.ReadFromFile(componentItem);
					
					cout << "\n"
						 << item.parts[i].partName
						 << ": "
						 << fixed << item.partQuantities[i] * jobRuns - item.partQuantities[i] * item.ME * 0.01 * jobRuns
						 << " * "
						 << componentItem.Price[0]
						 << " = "
						 << fixed << (item.partQuantities[i] * jobRuns - item.partQuantities[i] * item.ME * 0.01 * jobRuns) * componentItem.Price[0]
						 << " isk."
						 << endl;
				}

				for(int i = 0; i < item.numParts; i++)
				{
					ProductType componentItem;
					strcpy(componentItem.Name, item.parts[i].partName);

					itemFile.ReadFromFile(componentItem);
					
					PrintOutSheetFile << "\n"
						 << item.parts[i].partName
						 << ": "
						 << fixed << item.partQuantities[i] * jobRuns - item.partQuantities[i] * item.ME * 0.01 * jobRuns
						 << " * "
						 << componentItem.Price[0]
						 << " = "
						 << fixed << (item.partQuantities[i] * jobRuns - item.partQuantities[i] * item.ME * 0.01 * jobRuns) * componentItem.Price[0]
						 << " isk."
						 << endl;
				}

				/*for (int index = 0; index < item.numParts; index++)
				{
					ProductType component;
					strcpy(component.Name, item.parts[index].partName);

					FileClass componentFile;
					componentFile.ReadFromFile(component);

					
				}*/
}

double ManufactureSomething(char itemName[], bool something, double ME_Job, int jobRuns, bool mineralPriceTrue_marketPriceFalse)
{
				ProductType item;
				
				strcpy(item.Name, itemName);

				FileClass itemFile;
				itemFile.ReadFromFile(item);

				double totalCostToManufacture = CostToManufacture(item, item.ME, mineralPriceTrue_marketPriceFalse);

				//cout << "\n"
				//	 << "Job cost for 1 run: ";
				//cin  >> ME_Job;

				totalCostToManufacture += ME_Job;

				totalCostToManufacture *= jobRuns;

				//cout << "\n"
				//	 << "The Cost to manufacture "
				//	 << jobRuns
				//	 << " runs of "
				//	 << item.UnitsProduced 
				//	 << " "
				//	 << itemName
				//	 << " is: "
				//	 << fixed << totalCostToManufacture
				//	 << endl;

				//cout << "\n"
				//	 << "The Value of "
				//	 << jobRuns * item.UnitsProduced
				//	 << " "
				//	 << itemName
				//	 << " is: "
				//	 << fixed << item.Price[0] * jobRuns * item.UnitsProduced
				//	 << " isk."
				//	 << endl;

				//cout << "\n"
				//	 << "The net value of Manufacturing this... is: "
				//	 << fixed << (item.Price[0] * jobRuns * item.UnitsProduced) - totalCostToManufacture
				//	 << " isk."
				//	 << endl;
				return totalCostToManufacture;
}

double CostToManufacture(ProductType &item, double ME_Job, bool mineralPriceTrue_marketPriceFalse /*, double &doubleTotal*/ )
{
	double doubleTotal = 0;

	for(int i = 0; i < item.numParts; i++)	// for each specific component
	{
		double componentCost = 0;

		ProductType component = Initialize_ProductType();	// initialize the component.
		strcpy(component.Name, item.parts[i].partName);		// get the component name.
		FileClass componentFile;							// instantiate the file class.
		componentFile.ReadFromFile(component);				// get the component's data from its file.
		
		/*int j = component.numParts;
		while(j != 0)
		{*/

		if(mineralPriceTrue_marketPriceFalse == true)
			componentCost = CostToManufacture(component, 0, true /*, componentCost */);	// find out how much it costs to produce this specific component.
		
		if(mineralPriceTrue_marketPriceFalse == false)
			componentCost = component.Price[0];

		int amountNeeded = (item.partQuantities[i] - item.partQuantities[i] * .01 * ME_Job);	// Find how many of those components are needed.

		componentCost *= amountNeeded;	// Find the total cost to manufacture that component;

		doubleTotal += componentCost;	// add "the cost to manufacture the x number of that component" to doubleTotal.
			
			/*j--;
			
		}*/

		//if(component.numParts == 0)
		//	return /* componentCost */ component.Price[0];	// for now, just amarr price.

		/*return componentCost;
		*/
	}

	if(item.numParts == 0)
		return item.Price[0];	// for now, just amarr price.

	return doubleTotal;

}

void Case9()
{	
	// This function needs to be redone to use pointers instead of just files.												NOT DONE

	// A new type double variable called "netProfit" should be added to the structure that Product information is held in.	DONE
	// "netProfit" should hold the net profit made from manufacturing an item.												NOT WORKING
	// It should load the data from "ProductList.txt" into an LL.															NOT DONE
	// Then calculate netProfit for each Product.																			NOT DONE
	// Then sort the LL from highest "netProfit" to lowest "netProfit".														NOT DONE
	
				int  numBluePrints = 0;
				bool mineralPriceTrue_marketPriceFalse = false;
				
				double ME_Job = 0;
				int jobRuns = 1;

				ProductType ProductLL = Initialize_ProductType();	// this element will be used first. ie, it will contain data.
				ProductType *Current  = &ProductLL;
				ProductType *Previous = NULL;

				cout << "\n"
					 << "1) Station \n"
					 << "2) Assembly Array (2%) \n"
					 << "3) Thukker Component Assembly Array (15%) \n";
				cin  >> jobRuns;

				if(jobRuns == 2)
					ME_Job += ME_Job * .02;

				if(jobRuns == 3)
					ME_Job += ME_Job * .15;
				
				cout << "\n"
					 << "1) Use base material prices as costs \n"
					 << "2) Use component Prices as cost \n";
				cin  >> jobRuns;
				
				if(jobRuns == 1)
					mineralPriceTrue_marketPriceFalse = true;
				
				if(jobRuns == 2)
					mineralPriceTrue_marketPriceFalse = false;
				
				ifstream ProductFile("ProductList.txt");
/*
				char blueprintpre[2000] = {0};
				ProductFile.getline(blueprintpre, 2000);*/

				do	// Find how many blueprints are in the database. Also build the Product/Blueprint LL.
				{
					char blueprint[2000] = {0};
					ProductFile.getline(blueprint, 2000);

					if(ProductFile.eof())
					{
						Current = Current->Previous;
						Current->Next = NULL;
						break;
					}

					strcpy(Current->Name, blueprint);

					Current->Next = new(ProductType);
					Current->Next->Previous = Current;
					Current = Current->Next;

					Current->Root = &ProductLL;
					Current->Next = NULL;

					numBluePrints++;
				}
				while(1);

				ProductFile.close();

				if(numBluePrints >= 1)
					Current = Current->Root;
				else
				{
					cout << "Error: No blueprints in database" << endl;
					return;
				}

				/*try
				{
					if(sizeof(Current->Root->Next) != 0)
						Current = Current->Root->Next;
					else
						throw string("Error: No blueprints in database");
				}
				catch(string s)
				{
					cout << s << endl;
					return;
				}*/

				// Current = Current->Root->Next;
				
				// Find the netProfit for each Blueprint
				while(1) //for(int i = 0; i < numBluePrints; i++)
				{
					Current->netProfit =  ManufactureSomething(Current->Name, true, ME_Job, jobRuns, mineralPriceTrue_marketPriceFalse);
					
					if(Current->Next == NULL)
						break;

					Current = Current->Next;
				}

				bool change = true;

				do
				{
					Current = Current->Root;
					change = false;
					while(Current->Next != NULL)	// Not sorting for some reason.
					{
						if(Current->netProfit <= Current->Next->netProfit)
						{
							/* 1) */ Current = Current->Next;
							/* 1.5) */ Previous = Current->Previous;

							if(Previous->Previous != NULL)
								/* 2) */ Previous->Previous->Next = Current;

							/* 3) */ Current->Previous = Previous->Previous;

							if(Current->Next != NULL)
								/* 4) */ Current->Next->Previous = Previous;

							if(Previous->Previous != NULL)
								/* 5) */ Previous->Previous = Current;

							/* 6) */ Previous->Next = Current->Next;
							/* 7) */ Current->Next = Previous;

							change = true;

							if(Current->Next == NULL)
								break;
						}
						else
							Current = Current->Next;
					}
				}
				while(change == true);

				Current = Current->Root;
				ofstream ProductOutFile("ProductList.txt");

				while(1)
				{
					char BpName[2000] = {0};
					strcpy(BpName, Current->Name);

					ProductOutFile << BpName << endl;

					Current = Current->Next;

					if(Current == NULL)
						break;
				}

				/*for(int i = 0; i < numblueprints; i++)
				{

					double  bestnetprofit = 0;
					char	bestproductname[304] = {0};

					for(int j = 0; j < numblueprints; j++)
					{
    					char productname[304] = {0};
						product.getline(productname, 300);
						double netprofit = manufacturesomething(productname, true, me_job, jobruns, mineralpricetrue_marketpricefalse);

						if(netprofit >= bestnetprofit)
							strcpy(bestproductname, productname);
						else
							newproductlist << productname << endl;

					}

					ofstream bestproducts("bestproducts", ios::app);
					bestproducts << bestproductname
						         << endl;
					bestproducts.close();

					product.close();
					newproductlist.close();

					numblueprints--;
				}*/
}










