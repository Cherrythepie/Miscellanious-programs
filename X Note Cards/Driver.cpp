#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>

struct FileName
{
	char ncfile[112];
};

using namespace std;

int  addFileNames	(ifstream	&configFile,	char list[][112]	);		// add files from config to ram
bool checkIfDigit	(char		misc[]								);		// checks if the string entered by user is a file number or new file name
void getQuestion	(ifstream	&inputFile,		char ncQuestion[]	);
void printQuestion	(char		ncQuestion[]						);
void getUserAnswer	(char		answer[]							);
void getncAnswer	(ifstream	&inputFile,		char ncAnswer[]		);
bool checkAnswer	(char		ncAnswer[],		char answer[]		);
bool STOPorGO		(char		ncQuestion[]						);

int main()
{
	int  sentinel = 0;
	int  fileNum = 0;
	char fileName[112];
	char list[100][112];	// array of file names
	char ncfile[112];
	char ncQuestion[2501];
	char ncAnswer[2501];
	char answer[2501];
	char misc[112];
	int  qn = 0;
	int  numCorrect = 0;

	cout << "Welcome to X Note Cards!\n"
		 << "If you would you like to add a new file to use, type \"add\".\n"
		 << "Otherwise pick the number of a file that you want to use.\n"
//		 << "Type in the name of the file that you want to use. \n(DON'T ADD THE EXTENSION, i.e. \".txt\").\n"
		 << endl;

	ifstream configFile("XNC config.txt");		// Open config file
	
	sentinel = addFileNames(configFile, list);	// get the sentinel and add file names from config to ram

	for(int i = 0; i < sentinel; i++)			// print file names (and numbers) to screen
	{
		cout << i
			 << ") ";

			 for(int j = 0; j < 111; j++)
			 {
				 cout	<< list[i][j];
			 }

		cout << endl;
	}

	cin.ignore();
	
	// needs reworking. I NEED my book back. this can go anywhere that uses 2d arrays

	cin.getline(misc, 111);

	if(checkIfDigit(misc))
	{
		fileNum = atoi(misc);
		strcpy(ncfile, list[fileNum]);
	}


//	cin.getline(ncfile, 100);

	strcat(ncfile, ".txt");

	cout << "The file you chose was "
		 << ncfile
		 << "\n"
		 << endl;

	ifstream inputFile(ncfile);

	inputFile.getline(ncQuestion, 100) >> ws;

	cout << "something: "
		 << ncQuestion
		 << "\n"
		 << endl;

	getQuestion(inputFile, ncQuestion);

	while(STOPorGO(ncQuestion))
	{
		cout << "Question "
			 << ++qn
			 << ":"
			 << endl;

		printQuestion(ncQuestion);

		getncAnswer(inputFile, ncAnswer);
		getUserAnswer(answer);

		if(!checkAnswer(ncAnswer, answer))
		{
			cout << "The correct answer is:\n"
				 << ncAnswer
				 << "\n"
				 << endl;
		}
		else
		{
			numCorrect++;
		}

		getQuestion(inputFile, ncQuestion);
	}

	cout << "Good Job Doing Your Studying!\n"
		 << "You got "
		 << numCorrect
		 << " of "
		 << qn
		 << " correct.\n"
		 << "Press any key to continue"
		 << endl;

	cin.ignore();

	return 0;
}

int addFileNames(ifstream &configFile, char list[][112])
{
	char  junk[112];
	short i, sentinel;
	configFile.getline(junk, 111);

	configFile.getline(junk, 111);
	sentinel = atoi(junk);

	// needs reworking. I NEED my book back

	for(i = 0; i < sentinel; i++)
	{
		configFile.getline(junk, 111);

		for(short j = 0; j < 111; j++)
		{
			list[i][j] = junk[j];
		}
	}

	return sentinel;
}

bool checkIfDigit(char misc[])
{
	for(int i = 0; i < 112; i++)
	{
		if(!isdigit(misc[i]))
		{
			return false;
		}
	}
	return true;
}


void getQuestion(ifstream &inputFile, char ncQuestion[])
{
	inputFile >> ws;
	inputFile.getline(ncQuestion, 2500) >> ws;
}

void printQuestion(char ncQuestion[])
{
	cout << ncQuestion
		 << endl;
}

void getUserAnswer(char answer[])
{
	cin.getline(answer, 2500);
}

void getncAnswer(ifstream &inputFile, char ncAnswer[])
{
	inputFile.getline(ncAnswer, 2500) >> ws;
}

bool checkAnswer(char ncAnswer[], char answer[])
{
	if(strcmp(ncAnswer, answer) == 0)
	{
		cout << "Correct!\n"
		     << endl;
		return true;
	}
	else
	{
		cout << "\nIncorrect."
			 << endl;
		return false;
	}
}

bool STOPorGO(char ncQuestion[])
{
	char sentinel[2501] = "stop";

	if(strcmp(ncQuestion, sentinel) == 0)
		return false;
	else
		return true;
}