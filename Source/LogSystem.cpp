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

LogSystem::LogSystem()
{
	// Create the log file and set stderr as the buffer
	freopen("log.txt", "w+", stderr);
};

LogSystem::~LogSystem()
{
	// Close stderr handle and finalize log output
	fclose(stderr);
};

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