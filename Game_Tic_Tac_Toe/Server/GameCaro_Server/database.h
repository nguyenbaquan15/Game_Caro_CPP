#pragma once

#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>


/* Read/Write data in SQL Server */
typedef struct data
{
	std::string Name;
	int Win;
	int Lose;
	int Equal;

} Data_t;


class sqlserver
{
	private:
		SQLHANDLE SQLEnvHandle = NULL;
		SQLHANDLE SQLConnectionHandle = NULL;
		SQLHANDLE SQLStatementHandle = NULL;
		SQLRETURN retCode = 0;

	public:

		/* Connect into database */
		void Connect();

		/* Disconnect into database */
		void DisConnect();

		/* Check Username and password into database */
		int LogIn(std::string UserName, std::string PassWord);

		/* Write username and password into database */
		bool SignUp(std::string UserName, std::string PassWord);

		/* Read data of player into database */
		bool GetDataPlayer(Data_t *Data);

		/* Write data of player into database */
		bool SetDataPlayer(Data_t *Data);

		/* Hash password before write into database */
		std::size_t HashPassword(std::string PassWord);

		/* Show error when connect to database */
		void showSQLError(unsigned int handleType, const SQLHANDLE& handle);

};