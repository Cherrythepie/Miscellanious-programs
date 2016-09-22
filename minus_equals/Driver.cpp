#include <iostream>

using namespace std;

int main()
{

	double input = 1, output = 0, modifier = 0;

	cout << "Modifier: ";
	cin >> modifier;

	while(input != 0)
	{
		cout << "Original Price: ";
		cin >> input;
		output = input;
		output -= input * (modifier * .01);

		cout << "\n" << "Reduced Price: " << output << "\n\n";


	}

}