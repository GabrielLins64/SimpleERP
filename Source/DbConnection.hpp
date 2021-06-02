/*
	SimpleERP ERP System
	Copyright (C) 2021 Miguel Nischor

	File: DbConnection.hpp
	Description: Class for MySQL/MariaDB database connection and control.
	Author: Miguel Nischor <miguel@nischor.com.br>
*/
#ifndef SERP_DBCONNECTION_HPP
#define SERP_DBCONNECTION_HPP

#include <mysql/mysql.h>

namespace SimpleERP
{
	class DbConnection
	{
		public:
			DbConnection();
			virtual ~DbConnection();

			void reconnect();
			void query(const char* Statement, unsigned long Size);

			char* getQueryData();

			bool isConnected();

			MYSQL* getInstance();

		protected:
			MYSQL* dbInstance;
			MYSQL_RES* dbResult;
			MYSQL_DATA* dbData;

			bool connected = false;
	};
};

#endif // SERP_DBCONNECTION_HPP
