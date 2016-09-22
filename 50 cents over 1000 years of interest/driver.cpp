#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	double total = 0.750;
	cin >> total;

	for(int i = 0; i < 1000; i++)
	{
		total = (total + total *.01);
		cout << i << ") " << fixed << total << endl;

		//if(i % 100 == 0)
		//	cin.ignore();
	}

	cin.ignore();
	cin.ignore();
	return 0;
}