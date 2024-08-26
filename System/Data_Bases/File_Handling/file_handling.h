#ifndef FILE_HANDLING_H_INCLUDED
#define FILE_HANDLING_H_INCLUDED

#include "../../Libraries/standard_libraries.h"
#include "../../Data_Structures/List/list.h"
#include "../../Payment_System/Server/server.h"

void Read_AccounDB_FromFile (list *pl);
void Update_AccountDB(list *pl);

#endif // FILE_HANDLING_H_INCLUDED
