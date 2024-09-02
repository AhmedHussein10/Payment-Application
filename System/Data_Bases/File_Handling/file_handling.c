#include "../../Libraries/standard_libraries.h"
#include "file_handling.h"
#include "../../Payment_System/Server/server.h"
#include "../../Data_Structures/List/list.h"

void Read_AccounDB_FromFile()
{
    FILE *file;
    file= fopen("C:/Users/Ahmed/Desktop/Payment_Application/System/Data_Bases/Data/AccountsDB.txt", "r");
    if (!file)
    {
        printf("Error, File Not Found \n");
        return;
    }

    int32_t i=0;
    char state[8];

    while (!feof(file))
    {
        ST_accountsDB_t *account = (ST_accountsDB_t *)malloc(sizeof(ST_accountsDB_t));
        if (account == NULL)
        {
            printf("Memory allocation failed\n");
            fclose(file);
            return;
        }

        if (fscanf(file, "%f %s %s", &account->balance, account->primaryAccountNumber, state) != 3)
        {
            free(account);
            break;
        }

        if (strcmp(state, "RUNNING") == 0)
            account->state = RUNNING;
        else if (strcmp(state, "BLOCKED") == 0)
            account->state = BLOCKED;
        else
        {
            printf("Unknown account state: %s\n", state);
            free(account);
            continue;
        }

        insert_Account(i, account, &Account_DB);
        i++;
    }

    fclose(file);
}

void Update_AccountDB()
{
    FILE *file;
    file = fopen("C:/Users/Ahmed/Desktop/Payment_Application/System/Data_Bases/Data/AccountsDB.txt", "w");
    if (file == NULL)
    {
        printf("Error, File is Not Found\n");
        return;
    }

    char state[8];
    node *pn = Account_DB.head;

    while (pn)
    {
        ST_accountsDB_t *PtrAccount = (ST_accountsDB_t *)pn->ptr;

        if (PtrAccount->state == RUNNING)       strcpy (state,"RUNNING");
        else if (PtrAccount->state == BLOCKED)  strcpy (state,"BLOCKED");
        else                                    strcpy (state,"ERROR");

        fprintf(file, "%f %s %s\n", PtrAccount->balance, PtrAccount->primaryAccountNumber, state);
        pn = pn->next;
    }
    fclose(file);
}


int Read_TransactionDB_FromFile()
{
    FILE *file;
    file= fopen("C:/Users/Ahmed/Desktop/Payment_Application/System/Data_Bases/Data/TransactionsDB.txt", "r");
    if (!file)
    {
        printf("Error, File Not Found \n");
        return -1;
    }

    int32_t count=0;
    char state[30];

    while (!feof(file))
    {
        ST_transaction_t *transaction=(ST_transaction_t *)malloc(sizeof(ST_transaction_t));
        if (transaction == NULL)
        {
            printf("Memory allocation failed\n");
            fclose(file);
            return -1;
        }

        if (fscanf(file,"%d %s %f %s %f %s %s %49[^\n]\n"
                  ,&transaction->transactionSequenceNumber
                  ,transaction->terminalData.transactionDate
                  ,&transaction->terminalData.transAmount
                  ,state
                  ,&transaction->terminalData.maxTransAmount
                  ,transaction->cardHolderData.cardExpirationDate
                  ,transaction->cardHolderData.primaryAccountNumber
                  ,transaction->cardHolderData.cardHolderName) != 8)
        {
            free(transaction);
            break;
        }

        if (strcmp(state, "APPROVED") == 0) transaction->transState = APPROVED;
        else if (strcmp(state, "DECLINED_INSUFFECIENT_FUND") == 0) transaction->transState = DECLINED_INSUFFECIENT_FUND;
        else if (strcmp(state, "DECLINED_STOLEN_CARD") == 0) transaction->transState = DECLINED_STOLEN_CARD;
        else if (strcmp(state, "FRAUD_CARD") == 0) transaction->transState = FRAUD_CARD;
        else if (strcmp(state, "INTERNAL_SERVER_ERROR") == 0) transaction->transState = INTERNAL_SERVER_ERROR;
        else
        {
            printf("Unknown account state: %s\n", state);
            free(transaction);
            continue;
        }

        insert_Account(count, transaction, &Transaction_DB);
        count ++;

    }
    fclose(file);
    return count;
}



int Write_TransactionDB_ToFile()
{
    FILE *file;
    file = fopen("C:/Users/Ahmed/Desktop/Payment_Application/System/Data_Bases/Data/TransactionsDB.txt", "w");
    if (file == NULL)
    {
        printf("Error, File is Not Found\n");
        return -1;
    }

    int count=0;
    char state[30];
    node *pn = Transaction_DB.head;

    while (pn)
    {
        ST_transaction_t *PtrAccount = (ST_transaction_t *)pn->ptr;
        PtrAccount->transactionSequenceNumber=count++;

        if      (PtrAccount->transState == APPROVED)                      strcpy (state,"APPROVED");
        else if (PtrAccount->transState == DECLINED_INSUFFECIENT_FUND)    strcpy (state,"DECLINED_INSUFFECIENT_FUND");
        else if (PtrAccount->transState == DECLINED_STOLEN_CARD)          strcpy (state,"DECLINED_STOLEN_CARD");
        else if (PtrAccount->transState == FRAUD_CARD)                    strcpy (state,"FRAUD_CARD");
        else if (PtrAccount->transState == INTERNAL_SERVER_ERROR)         strcpy (state,"INTERNAL_SERVER_ERROR");
        else                                                              strcpy (state,"ERROR");

        fprintf(file,"%d %s %f %s %f %s %s %s\n"
                  ,PtrAccount->transactionSequenceNumber
                  ,PtrAccount->terminalData.transactionDate
                  ,PtrAccount->terminalData.transAmount
                  ,state
                  ,PtrAccount->terminalData.maxTransAmount
                  ,PtrAccount->cardHolderData.cardExpirationDate
                  ,PtrAccount->cardHolderData.primaryAccountNumber
                  ,PtrAccount->cardHolderData.cardHolderName);

        pn = pn->next;
    }
    fclose(file);
    return 1;
}
