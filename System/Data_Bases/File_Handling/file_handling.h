#ifndef FILE_HANDLING_H_INCLUDED
#define FILE_HANDLING_H_INCLUDED

#include "../../Libraries/standard_libraries.h"
#include "../../Data_Structures/List/list.h"
#include "../../Payment_System/Server/server.h"

void Read_AccounDB_FromFile (void);
void Update_AccountDB(void);
int Read_TransactionDB_FromFile(void);
int Write_TransactionDB_ToFile(void);

#endif // FILE_HANDLING_H_INCLUDED
