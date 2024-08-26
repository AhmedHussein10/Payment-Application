#include "../../Libraries/standard_libraries.h"
#include "file_handling.h"
#include "../../Payment_System/Server/server.h"
#include "../../Data_Structures/List/list.h"

void Read_AccounDB_FromFile(list *pl)
{
    FILE *file;
    file = fopen("C:/Users/Ahmed/Desktop/Payment_Application/System/Data_Bases/Data/AccountsDB.txt", "r");
    if (file == NULL)
    {
        printf("Error, File is Not Found\n");
        return;
    }

    ST_accountsDB_t *Account;
    uint8_t i = 0;
    while (1)
    {
        Account = (ST_accountsDB_t *)malloc(sizeof(ST_accountsDB_t));
        if (Account == NULL)
        {
            printf("Out of memory\n");
            fclose(file);
            return;
        }

        if (fscanf(file, "%f %19s %d", &Account->balance, Account->primaryAccountNumber, &Account->state) != 3)
        {
            free(Account); // Free the last allocation before exiting
            break;
        }

        insert_Account(i, Account, pl);
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
