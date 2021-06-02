/*
	SimpleERP ERP System
	Copyright (C) 2021 Miguel Nischor

	File: LogSystem.hpp
	Description: Class for logging messages and errors from databases and system.
	Author: Miguel Nischor <miguel@nischor.com.br>
*/
#ifndef SERP_LOGSYSTEM_HPP
#define SERP_LOGSYSTEM_HPP

namespace SimpleERP
{
	class LogSystem
	{
		public:
			LogSystem();
			virtual ~LogSystem();

			void write(const char* message);
	};
};

#endif // SERP_LOGSYSTEM_HPP
