#include "Decode.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream read;
	read.exceptions(ifstream::failbit);
	try
	{
		read.open("quote.txt");
		string str, str_add;
		while (!read.eof())
		{
			getline(read, str_add);
			str += str_add;
		}
		Decoding(str);
		read.close();
	}
	catch (const ifstream::failure& e)
	{
		cout << "Exception opening file\n";
	}

	return 0;
}