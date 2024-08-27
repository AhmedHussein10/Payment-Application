#include "../../Libraries/standard_libraries.h"
#include "file_handling.h"
#include "../../Payment_System/Server/server.h"
#include "../../Data_Structures/List/list.h"

void Read_AccounDB_FromFile(list *pl)
{
    FILE *file;
    file= fopen("C:/Users/Ahmed/Desktop/Payment_Application/System/Data_Bases/Data/AccountsDB.txt", "r");
    if (!file)
    {
        printf("Error, File Not Found \n");
        return;
    }
    ST_accountsDB_t *account;
    float amount;
    uint8_t pan[20];
    char state[8];
    uint8_t i=0;
    while (fscanf(file, "%f %s %s", &amount, pan, state) != EOF)
    {
        account=(ST_accountsDB_t *)malloc(sizeof(ST_accountsDB_t));
        account->balance = amount;
        strncpy((char*)account->primaryAccountNumber,(char*) pan, sizeof(account->primaryAccountNumber));
        account->state = (strcmp(state, "RUNNING") == 0) ? RUNNING : BLOCKED;
        insert_Account(i,account,pl);
        i++;
    }
    fclose(file);
}

void Update_AccountDB(list *pl)
{
    FILE *file;
    file = fopen("C:/Users/Ahmed/Desktop/Payment_Application/System/Data_Bases/Data/AccountsDB.txt", "w");
    if (file == NULL)
    {
        printf("Error, File is Not Found\n");
        return;
    }

    node *pn = pl->head;
    while (pn)
    {
        ST_accountsDB_t *PtrAccount = (ST_accountsDB_t *)pn->ptr;
        fprintf(file, "%f %s %d\n", PtrAccount->balance, PtrAccount->primaryAccountNumber, PtrAccount->state);
        pn = pn->next;
    }
    fclose(file);
}

