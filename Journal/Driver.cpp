#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <ctime>

using namespace std;

int main()
{
	char title[112];

	// current date/time based on current system
	time_t now = time(0);
   
	// convert now to string form
	char* dt = ctime(&now);

//	cout << "The local date and time is: " << dt << endl;

/*   
	// convert now to tm struct for UTC
	tm *gmtm = gmtime(&now);
    dt = asctime(gmtm);
    cout << "The UTC date and time is:"<< dt << endl;
*/


	cout << "This is a journal program. "
		 << "The date is "
		 << dt
		 << endl;

	cout << "What is the title of this journal (max 100 characters)?\n"
		 << "If you do not choose one, then the title will be the time stamp."
		 << endl;

	cin.getline(title, 100);
	if(strcmp(title, "") == 0)
	{
		strcpy(title, dt);
		strcat(title, "dt");
	}

	strcat(title, ".txt");

	char c;
	for(short i = 0, c = title[i]; i < sizeof(title); i++, c = title[i])
	{
		if(c == ':')
			title[i] = '-';
	}
	
	cout << "The name of the file (with extension) will be "
		 << title
		 << endl;

	cout << "You may begin typing whenever you like."
		 << endl;

	char guts[100001];

	cin.getline(guts, 100000);

	ofstream JournalFile(title);
	JournalFile << dt;
	JournalFile << guts;

	cin.ignore();




	return 0;
}