/*
	SimpleERP ERP System
	Copyright (C) 2021 Miguel Nischor

	File: LogSystem.cpp
	Description: Implementation for LogSystem class.
	Author: Miguel Nischor <miguel@nischor.com.br>
*/
#include "LogSystem.hpp"
#include "DbConnection.hpp"
#include <iostream>
#include <cstdio>
#include <time.h>

using namespace SimpleERP;
using namespace std;

/*
	Function: LogSystem()
	Description: Default constructor, initialize log file handle
	Return value: No return value
*/
LogSystem::LogSystem()
{
	// Get current time
	time_t now = time(0);

	// Organize time as a structure
	tm tstruct = *localtime(&now);
	
	// Buffer to store time as text
	char buffer[80];

	// Buffer to store file name
	char filename[80] = {"serp_log-"};

	// Write formatted time to buffer
	strftime(buffer, sizeof(buffer), "%d-%m-%Y", &tstruct);

	// Append formatted time buffer to file name (serp_log-DD-MM-YYYY.log)
	strcat(filename, buffer);
	strcat(filename, ".log");

	// Create the log file and set stderr as the buffer
	freopen(filename, "a+", stderr);
};

/*
	Function: ~LogSystem()
	Description: Default destructor, closes log file handle
	Return value: No return value
*/
LogSystem::~LogSystem()
{
	// Close stderr handle and finalize log output
	fclose(stderr);
};

/*
	Function: write(const char*)
	Description: Write a single parameter with timestamp for the log file
	Return value: No return value
*/
void LogSystem::write(const char* message)
{
	// Get current time
	time_t now = time(0);

	// Organize time as a structure
	tm tstruct = *localtime(&now);
	
	// Buffer to store time as text
	char buffer[80];

	// Write formatted time to buffer
	strftime(buffer, sizeof(buffer), "[%d-%m-%Y %H:%M:%S]", &tstruct);

	// Write message to log output with formatted time
	clog << buffer << "\t" << message << endl;
};

/*
	Function: write(const char*, const char*)
	Description: Write both parameters with timestamp for the log file
	Return value: No return value
*/
void LogSystem::write(const char* message, const char* append)
{
	// Get current time
	time_t now = time(0);

	// Organize time as a structure
	tm tstruct = *localtime(&now);
	
	// Buffer to store time as text
	char buffer[80];

	// Write formatted time to buffer
	strftime(buffer, sizeof(buffer), "[%d-%m-%Y %H:%M:%S]", &tstruct);

	// Write message to log output with formatted time
	clog << buffer << "\t" << message << append << endl;
};