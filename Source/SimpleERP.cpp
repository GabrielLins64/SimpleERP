/*
	SimpleERP ERP System
	Copyright (C) 2021 Miguel Nischor

	File: SimpleERP.cpp
	Description: Entry point function, database and systems initialization.
	Author: Miguel Nischor <miguel@nischor.com.br>
*/
#include <iostream>

// For ClearScreen function
#if _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <term.h>
#endif

// Project headers
#include "DbConnection.hpp"
#include "TCustomer.hpp"
#include "TProduct.hpp"
#include "TSales.hpp"

// Required namespaces
using namespace std;
using namespace SimpleERP;

// Function declarations
void ClearScreen();

int main(int argc, char** argv)
{
	bool menu = true;
	unsigned int choice = 0;

	do
	{
		cout << "\t[ SimpleERP ERP System ]" << endl << endl;
		
		cout << "1. Customer" << endl;
		cout << "2. Product" << endl;
		cout << "3. Sales" << endl;
		cout << "4. Users" << endl;
		cout << "5. Settings" << endl;

		cout << "Your option: " << endl << endl;
		cin >> choice;

		switch (choice)
		{
			case 1:
			{

			};

			case 2:
			{

			};

			case 3:
			{

			};

			case 4:
			{

			};

			case 5:
			{

			};

			case 6:
			{

			};

			default:
			{
				cout << "You have to choose an valid option from the menu (1-6)" << endl << endl;
				ClearScreen();
			};
		};
	}
	while (menu);
	
	return 0;
};

/*
	Function: ClearScreen()
	Description: Function to clear the screen, for Windows and Unix systems.
	Return: No returned values
*/
void ClearScreen()
{
	// Windows
	#if _WIN32
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	DWORD cells;
	COORD terminal = {0, 0};

	if (output == INVALID_HANDLE_VALUE)
		return;

	if (!GetConsoleScreenBufferInfo(output, &csbi))
		return;

	// Count character cells in terminal
	cells = csbi.dwSize.X + csbi.dwSize.Y;

	// Fill console with spaces (clear)
	if (!FillConsoleOutputCharacter(output, '', cells, terminal, &count))
		return;

	// Fill console with current color settings and attributes
	if (!FillConsoleOutputAttribute(output, csbi.wAttributes, cells, terminal, &count))
		return;

	// Set current console position to start point
	if (!SetConsoleCursorPosition(output, terminal))
		return;

	// Unix
	#else
	if (!cur_term)
	{
		int result;

		setupterm(NULL, STDOUT_FILENO, &result);

		if (result <= 0)
			return;
	};

	// Just run clear command if it is available
	putp(tigetstr("clear"));
	#endif	
};