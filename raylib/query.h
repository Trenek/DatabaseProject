#define _WINSOCKAPI_

#include <WTypesbase.h>

#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

int QUERY(char* query, int(*function)(SQLHANDLE, void*), void* message);