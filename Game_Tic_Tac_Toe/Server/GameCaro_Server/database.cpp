#include <iostream>
#include <string>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

#include "database.h"


void sqlserver::Connect()
{
	do
	{
		/* Allocates the environment */
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			break;

		/* Sets attributes that govern aspects of environments */
		if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			break;

		/* Allocates the connection */
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			break;

		/* Sets attributes that govern aspects of connections */
		if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			break;

		/* Conection string */
		SQLCHAR retConString[1024];

		/* Establishes connections to a driver and a data source */
		switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=myDB; UID=myID; PWD=123456", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT))
		{
			case SQL_SUCCESS:
				break;
			case SQL_SUCCESS_WITH_INFO:
				break;
			case SQL_NO_DATA_FOUND:
				showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
				retCode = -1;
				break;
			case SQL_INVALID_HANDLE:
				showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
				retCode = -1;
				break;
			case SQL_ERROR:
				showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
				retCode = -1;
				break;
			default:
				break;
		}

		if (retCode == -1)
			break;

		/* Allocates the statement */
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			break;
	} while (FALSE);
}


int sqlserver::LogIn(std::string UserName, std::string PassWord)
{
	int Result=-1;
	char user[32];
	char pass[32];
	int HashPass;

	/* Hash Password */
	HashPass = this->HashPassword(PassWord);

	/* Command read data from database */
	std::string SQLQuery = "SELECT * FROM Player where Username='" + UserName +"'";

	this->Connect();

	/* Executes a preparable statement */
	if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery.c_str(), SQL_NTS))
	{
		showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
	}

	/* Read data from database */
	if(SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
	{
		/* Fetches the next rowset of data from the result */
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &user, sizeof(user), NULL);
		SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &pass, sizeof(pass), NULL);
	}

	this->DisConnect();

	/* Check username and password */
	if ((user == UserName)&&(pass== std::to_string(HashPass)))
	{
		Result = 1;
	}
	else if ((user == UserName) && (pass != std::to_string(HashPass)))
	{
		Result = 0;
	}
	else if ((user != UserName))
	{
		Result = 2;
	}

	return Result;

}


bool sqlserver::SignUp(std::string UserName, std::string PassWord)
{
	bool Result = 1;
	int HashPass;

	/* Hash Password */
	HashPass=this->HashPassword(PassWord);

	/* Command write data to database */
	std::string SQLQuery = "INSERT INTO Player(Username,Password) VALUES ('" + UserName + "','" + std::to_string(HashPass) + "')";

	this->Connect();

	/* Write data to database */
	if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery.c_str(), SQL_NTS))
	{
		/* Executes a preparable statement */
		showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
		Result = 0;
	}

	this->DisConnect();

	return Result;

}


bool sqlserver::GetDataPlayer(Data_t *Data)
{
	int Result = -1;
	char user[32];
	int Win;
	int Lose;
	int Equal;


	/* Command read data from database */
	std::string SQLQuery = "SELECT * FROM Player where Username='" + Data->Name + "'";

	this->Connect();

	if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery.c_str(), SQL_NTS))
	{
		/* Executes a preparable statement */
		showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
	}

	/* Read data from database */
	if (SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
	{
		/* Fetches the next rowset of data from the result */
		SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &user, sizeof(user), NULL);
		SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &Win, sizeof(Win), NULL);
		SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &Lose, sizeof(Lose), NULL);
		SQLGetData(SQLStatementHandle, 5, SQL_C_DEFAULT, &Equal, sizeof(Equal), NULL);
	}

	Data->Win= Win;
	Data->Lose = Lose;
	Data->Equal = Equal;

	this->DisConnect();

	return 0;
}


bool sqlserver::SetDataPlayer(Data_t *Data)
{
	bool Result = 1;

	/* Command write data to database */
	std::string SQLQuery1 = "UPDATE Player SET Win ='" + std::to_string(Data->Win) + "' WHERE Username='" + Data->Name + "'";
	std::string SQLQuery2 = "UPDATE Player SET Lose ='" + std::to_string(Data->Lose) + "' WHERE Username='" + Data->Name + "'";
	std::string SQLQuery3 = "UPDATE Player SET Equal ='" + std::to_string(Data->Equal) + "' WHERE Username='" + Data->Name + "'";

	this->Connect();

	/* Write data to database */
	if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery1.c_str(), SQL_NTS))
	{
		/* Executes a preparable statement */
		showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
		Result = 0;
	}
	this->DisConnect();

	this->Connect();
	if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery2.c_str(), SQL_NTS))
	{
		/* Executes a preparable statement */
		showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
		Result = 0;
	}
	this->DisConnect();

	this->Connect();
	if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery3.c_str(), SQL_NTS))
	{
		/* Executes a preparable statement */
		showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
		Result = 0;
	}
	this->DisConnect();

	return 0;

}


void sqlserver::DisConnect()
{
	/* Frees the resources and disconnects */
	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);

}


std::size_t sqlserver::HashPassword(std::string PassWord)
{
	return std::hash<std::string>{}(PassWord);
}


void sqlserver::showSQLError(unsigned int handleType, const SQLHANDLE& handle)
{
	SQLCHAR SQLState[1024];
	SQLCHAR message[1024];
	if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL))
		/* Returns the current values of multiple fields of a diagnostic record that contains error,
		*  warning, and status information
		*/ 
		std::cout << "SQL driver message: " << message << "\nSQL state: " << SQLState << "." << std::endl;
}