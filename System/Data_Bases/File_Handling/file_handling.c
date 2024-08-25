#include "../../Libraries/standard_libraries.h"
#include "file_handling.h"
#include "../../Payment_System/Server/server.h"
#include "../../Data_Structures/List/list.h"

void Read_AccounDB_FromFile ()
{
    FILE *file;
    file= fopen("C:/Users/Ahmed/Desktop/Payment_Application/System/Data_Bases/Data/AccountsDB.txt", "r");
    if (!file)
    {
        printf("Error, File Not Found \n");
        return;
    }
    create_list (&Account_DB);
    ST_accountsDB_t account;
    float amount;
    uint8_t pan[20];
    char state[8];
    uint8_t i=0;
    while (fscanf(file, "%f %s %s", &amount, pan, state) != EOF)
    {
        account.balance = amount;
        strncpy((char*)account.primaryAccountNumber,(char*) pan, sizeof(account.primaryAccountNumber));
        account.state = (strcmp(state, "RUNNING") == 0) ? RUNNING : BLOCKED;
        insert_Account(i,account,&Account_DB);
        i++;
    }
    fclose(file);
}
