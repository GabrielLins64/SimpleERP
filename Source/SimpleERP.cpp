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
#include "LogSystem.hpp"
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
	mysql_library_init(argc, argv, NULL);

	bool menu = true;
	unsigned int choice;

	DbConnection* db = new DbConnection();

	// Clear screen if program is called directly
	ClearScreen();

	do
	{
		cout << "\t[ SimpleERP ERP System ]" << endl << endl;
		
		cout << "\t1. Customer" << endl;
		cout << "\t2. Product" << endl;
		cout << "\t3. Sales" << endl;
		cout << "\t4. Users" << endl;
		cout << "\t5. Settings" << endl << endl;

		cout << "\tYour option: ";
		cin >> choice;
		cout << endl << endl;

		// Screen is cleared for menu choice
		ClearScreen();

		switch (choice)
		{
			case 1:
			{
				cout << "Test query: " << endl << endl;
				db->query("SHOW DATABASES;", 16);
				cout << db->getQueryData() << endl;

				system("pause");
				menu = false;
				break;
			};

			case 2:
			{
				cout << "To be implemented" << endl << endl;
				ClearScreen();
				break;
			};

			case 3:
			{
				cout << "To be implemented" << endl << endl;
				ClearScreen();
				break;
			};

			case 4:
			{
				cout << "To be implemented" << endl << endl;
				ClearScreen();
				break;
			};

			case 5:
			{
				cout << "To be implemented" << endl << endl;
				ClearScreen();
				break;
			};

			case 6:
			{
				cout << "To be implemented" << endl << endl;
				ClearScreen();
				break;
			};

			default:
			{
				cout << "You have to choose an valid option from the menu (1-6)" << endl << endl;
				ClearScreen();
				break;
			};
		};
	}
	while (menu);

	db->~DbConnection();
	
	mysql_library_end();
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
	if (!FillConsoleOutputCharacter(output, (char)32, cells, terminal, &count))
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