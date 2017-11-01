#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool isLetter(char B);
bool isWhite(char C);
bool isSentEnder(char D);

int main() {

	char Z; //to stop file exiting before output is shown

	char A; //characters
	int CharCount = 0;

	int TObjCount = 0; //text objects
	bool TObjStart = true;
	bool TObjStarted = false;

	bool WordStart = true; // words, also using WordStart as sentence start marker
	bool WStarted = false;
	int WordCount = 0;

	//total sentences
	int SenCount = 0;
	
	//total exclamatory and interrogative sentences
	int SenExcCount = 0;
	int SenQCount = 0;

	string Filename; //filename

	cout << "Please enter filename with extension: ";
	cin >> Filename;

	ifstream MyFile(Filename);
		
	while (true)
	{
		MyFile.read(&A, 1);
		
		if (!(MyFile.good()))
		{
			if (TObjStarted) TObjCount++;
			
			if (WStarted) WordCount++;
		
			cout << "******************************************************\n";

			if (CharCount == 0) //for an empty file
			{
				cout << "\nThis is an empty file\n";
				cout << "\n******************************************************\n";
				cout << "Press any key to continue "; cin >> Z;
				break;
			}
			
			cout << "\nThere are	" << CharCount << " characters,\n";
			cout << "\n		" << TObjCount << " text objects,\n";
			cout << "\n		" << WordCount << " words,\n";
			cout << "\n		" << SenCount << " sentences,\n";
			cout << "\n		" << SenQCount << " interrogative sentences and\n";
			cout << "\n		" << SenExcCount << " exclamatory sentences in this file\n";
			cout << "\n******************************************************\n";
			cout << "Press any key to continue "; cin >> Z;

			break;
		}
		
		CharCount++; //it will always be executed, if at end of loop can be skipped, also doesnt count eof file character

		if (!isWhite(A))
		{
			if (TObjStart)
			{
				TObjStart = false;
				TObjStarted = true;
			}
		}
		
		if (isLetter(A))
		{
			if (WordStart)
			{
				WordStart = false;
				WStarted = true;
			}

			continue;
		}
				
		if (isWhite(A))
		{
			if (TObjStarted) TObjCount++; //text object counter
	
			TObjStart = true;
			TObjStarted = false;

			if (WStarted) WordCount++; //for words

			WordStart = true;
			WStarted = false;
						
			continue;
		}
		
		if (A == ',')
		{
			if (WStarted) WordCount++; //for words

			WordStart = false;
			WStarted = false;
			continue;
		}

		if (isSentEnder(A))
		{
			if (WStarted)
			{

				SenCount++;
				WordCount++;
				
				if (A == '?')
				{
				SenQCount++;
				}
				else if (A == '!')
				{
				SenExcCount++;
				}
									
			}

			WordStart = false;
			WStarted = false;
			continue;
		}
		
	WordStart = false;
	WStarted = false;
		
	}
	
	return 0;
}

bool isLetter(char B)
{
	bool result;
	result = (B >= 'A' && B <= 'Z') || (B >= 'a' && B <= 'z');
	return result;
}

bool isWhite(char C)
{
	bool result;
	result = (C == ' ' || C == '\n' || C == '\t');
	return result;
}

bool isSentEnder(char D)
{
	bool result;
	result = (D == '.' || D == '!' || D == '?');
	return result;
}