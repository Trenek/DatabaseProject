#define _WINSOCKAPI_

#include <WTypesbase.h>

#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

int QUERY(const char* query, char* errorMessage, int(*function)(SQLHANDLE, void*), void* message);