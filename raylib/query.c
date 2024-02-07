#include <stdio.h>
#include <stdbool.h>

#include "query.h"

static void showSQLError(unsigned int handleType, const SQLHANDLE *handle, char* query) {
    SQLCHAR SQLState[1024];
    //SQLCHAR message[1024];

    if (SQL_SUCCESS == SQLGetDiagRec((SQLSMALLINT)handleType, *handle, 1, SQLState, NULL, (SQLCHAR*)query, 1024, NULL)) {
        printf("SQL driver message: %s\nSQL state: %s.\n", query, SQLState);
    }
}

static bool setupSQL(SQLHANDLE* SQLEnvHandle, SQLHANDLE* SQLConnectionHandle, SQLHANDLE* SQLStatementHandle, char* query) {
    bool result = false;

    if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, SQLEnvHandle))
    if (SQL_SUCCESS == SQLSetEnvAttr(*SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
    if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_DBC, *SQLEnvHandle, SQLConnectionHandle))
    if (SQL_SUCCESS == SQLSetConnectAttr(*SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
    switch (SQLDriverConnect(*SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=Project; UID=ProjectApplication; PWD=HardPassword", SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT)) {
        case SQL_NO_DATA_FOUND:
        case SQL_INVALID_HANDLE:
        case SQL_ERROR:
            showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle, query);
            break;
        default:
            if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_STMT, *SQLConnectionHandle, SQLStatementHandle))
            switch (SQLExecDirect(*SQLStatementHandle, (SQLCHAR*)query, SQL_NTS)) {
                case SQL_SUCCESS_WITH_INFO:
                    showSQLError(SQL_HANDLE_STMT, SQLStatementHandle, query);
                case SQL_SUCCESS:
                    result = true;
                    break;
                default:
                    showSQLError(SQL_HANDLE_STMT, SQLStatementHandle, query);
            }
    }

    return result;
}

static void clearSQL(SQLHANDLE* SQLEnvHandle, SQLHANDLE* SQLConnectionHandle, SQLHANDLE* SQLStatementHandle) {
    SQLFreeHandle(SQL_HANDLE_STMT, *SQLStatementHandle);
    SQLDisconnect(*SQLConnectionHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, *SQLConnectionHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, *SQLEnvHandle);
}

int QUERY(char* query, int(*function)(SQLHANDLE, void*), void* message) {
    SQLHANDLE SQLEnvHandle = NULL;
    SQLHANDLE SQLConnectionHandle = NULL;
    SQLHANDLE SQLStatementHandle = NULL;
    int result = 0;

    if (setupSQL(&SQLEnvHandle, &SQLConnectionHandle, &SQLStatementHandle, query)) {
        if (function != 0) {
            result = function(SQLStatementHandle, message);
        }
    }

    clearSQL(&SQLEnvHandle, &SQLConnectionHandle, &SQLStatementHandle);

    return result;
}