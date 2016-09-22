#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H

#include <fstream>

using namespace std;

struct PartType
{
	char partName[255];
};

struct ProductType
{
	char Name[255];			// Product Name
	PartType parts[100];	// Product Components
	int partQuantities[100];	// Number of each Product Component

	int numParts;			// Number of Distinct Product Components

	double  Price[5];		/* Product Market Prices;
							
							0 = Amarr
							1 = Dodixie
							2 = Hek
							3 = Jita
							4 = Rens

							*/
	double ME;
	int Type;
	double UnitsProduced;
	double netProfit;		// This variable is not saved in the database.
							// Its use is to help sort Products to determine which product (when manufactured) will give the best profit margin out of all other products in the database.
							/*

							0 = Ammunition & Charges
							1 = Apparel
							2 = Blueprints
							3 = Drones
							4 = Implants & Boosters
							5 = Infantry Gear
							7 = Manufacture & Research
							8 = Pilot's Services
							9 = Planetary Infrastructure
							10= Reactions
							11 = Ship Equipment
							12 = Ship Modifications (Rigs/Subsystems)
			13 = Minerals
							14 = Ships
							15 = Skills
							16 = Special Edition Assets
							17 = Structures
							18 = Trade Goods
							
							*/

	ProductType *Next, *Previous, *Root;	// Used when "Manufacturing" and item.
};

struct findType
{

	char ccode;	// command code (m, z)
	char manuName[301];	// Manufacturer's name.
	char DzipCode[6];	// Dealearship Zipcode.

};

#endif;