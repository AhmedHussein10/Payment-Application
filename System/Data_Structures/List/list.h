#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "../../Libraries/standard_libraries.h"
#include "../../Payment_System/Server/server.h"

int create_list (list *pl);
int is_list_empty (list *pl);
int is_list_full (list *pl);
int insert_Account (int pos,ST_accountsDB_t Account,list *pl);
int delete_Account (int pos,ST_accountsDB_t *pAccount,list *pl);
int list_size (list *pl);
int retrieve_Account (int pos,ST_accountsDB_t *pAccount,list *pl);
int traverse_Accounts (list *pl,void (*pf) (ST_accountsDB_t));
int clear_list (list *pl);
void display (ST_accountsDB_t Account);

#endif // LIST_H_INCLUDED
