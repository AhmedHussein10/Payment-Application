#include "../../Libraries/standard_libraries.h"
#include "../../Libraries/platform_type.h"
#include "../../Data_Bases/File_Handling/file_handling.h"
#include "../../Data_Structures/List/list.h"
#include "server.h"

#define MAX_AMOUNT 1000

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    if (transData == NULL)
        return INTERNAL_SERVER_ERROR;

    ST_accountsDB_t *PtrAccount=NULL;

    EN_cardError_t Card_State;
    EN_terminalError_t Term_State;

    Card_State = getCardHolderName (&transData->cardHolderData);
    while (Card_State != CARD_OK)
    {
        printf ("Wrong name, ");
        printf("Please try again.\n");
        Card_State = getCardHolderName(&transData->cardHolderData);
    }

    Card_State = getCardPAN (&transData->cardHolderData);
    while (Card_State != CARD_OK)
    {
        printf ("Wrong PAN, ");
        printf("Please try again.\n");
        Card_State = getCardPAN(&transData->cardHolderData);
    }

    Card_State = getCardExpiryDate (&transData->cardHolderData);
    while (Card_State != CARD_OK)
    {
        printf ("Wrong date, ");
        printf("Please try again.\n");
        Card_State = getCardExpiryDate(&transData->cardHolderData);
    }

    Term_State = getTransactionDate(&transData->terminalData);
    while (Term_State != TERMINAL_OK)
    {
        printf(" Wrong date, ");
        printf("Please try again.\n");
        Term_State = getTransactionDate(&transData->terminalData);
    }

    Term_State = setMaxAmount(&transData->terminalData,MAX_AMOUNT);
    while (Term_State != TERMINAL_OK)
    {
        printf("Invalid amount, ");
        printf("Please try again.\n");
        Term_State = setMaxAmount(&transData->terminalData,MAX_AMOUNT);
    }

    Term_State = getTransactionAmount(&transData->terminalData);
    while (Term_State != TERMINAL_OK)
    {
        printf("INVALID amount, ");
        printf("Please try again.\n");
        Term_State = getTransactionAmount(&transData->terminalData);
    }


    if(isValidAccount(&transData->cardHolderData,&PtrAccount) == ACCOUNT_NOT_FOUND)
    {
        transData->transState = FRAUD_CARD;
        return FRAUD_CARD;
    }

    if(isBlockedAccount(PtrAccount) == BLOCKED_ACCOUNT || isBlockedAccount(PtrAccount) == ACCOUNT_NOT_FOUND)
    {
        transData->transState = DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD ;
    }

    if(isAmountAvailable(&transData->terminalData,PtrAccount) == LOW_BALANCE || isAmountAvailable(&transData->terminalData,PtrAccount) == ACCOUNT_NOT_FOUND)
    {
        transData->transState = DECLINED_INSUFFECIENT_FUND;
        return DECLINED_INSUFFECIENT_FUND;
    }

    PtrAccount->balance -= transData->terminalData.transAmount;

    Update_AccountDB ();
    return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t **accountRefrence)
{
    if (cardData == NULL)
        return ACCOUNT_NOT_FOUND;

    node *pn=Account_DB.head;

    while (pn)
    {
        if (strcmp( (char *)cardData->primaryAccountNumber, (char *)((ST_accountsDB_t*)pn->ptr)->primaryAccountNumber) == 0)
        {
            *accountRefrence=pn->ptr;
            break;
        }
        pn=pn->next;
    }

    if (*accountRefrence==NULL)
        return ACCOUNT_NOT_FOUND;
    return SERVER_OK;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    if (accountRefrence == NULL)
        return ACCOUNT_NOT_FOUND;
    if (accountRefrence->state==BLOCKED)
        return BLOCKED_ACCOUNT;
    return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData,ST_accountsDB_t *accountRefrence)
{
    if (accountRefrence == NULL || termData == NULL)
        return ACCOUNT_NOT_FOUND;
    if (termData->transAmount > accountRefrence->balance)
        return LOW_BALANCE;
    return SERVER_OK;

}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    if (transData == NULL)
        return SAVING_FAILED;

    int32_t count=Read_TransactionDB_FromFile ();

    insert_Account (count,transData,&Transaction_DB);

    if (Write_TransactionDB_ToFile () != 1)
        return SAVING_FAILED;

    return SERVER_OK;

}


void listSavedTransactions(void)
{
    node *pn = Transaction_DB.head;
    char state[30];
    while (pn)
    {
        ST_transaction_t *PtrAccount = (ST_transaction_t *)pn->ptr;

        if      (PtrAccount->transState == APPROVED)                      strcpy (state,"APPROVED");
        else if (PtrAccount->transState == DECLINED_INSUFFECIENT_FUND)    strcpy (state,"DECLINED_INSUFFECIENT_FUND");
        else if (PtrAccount->transState == DECLINED_STOLEN_CARD)          strcpy (state,"DECLINED_STOLEN_CARD");
        else if (PtrAccount->transState == FRAUD_CARD)                    strcpy (state,"FRAUD_CARD");
        else if (PtrAccount->transState == INTERNAL_SERVER_ERROR)         strcpy (state,"INTERNAL_SERVER_ERROR");
        else                                                              strcpy (state,"ERROR");

        printf("\n#####################################\n");
        printf("Transaction Sequence Number: %d\n" ,PtrAccount->transactionSequenceNumber );
        printf("Transaction Date: %s\n"            ,PtrAccount->terminalData.transactionDate);
        printf("Transaction Amount: %.2f\n"        ,PtrAccount->terminalData.transAmount);
        printf("Transaction State: %s\n"           ,state);
        printf("Terminal Max Amount: %.2f\n"       ,PtrAccount->terminalData.maxTransAmount);
        printf("Cardholder Name: %s\n"             ,PtrAccount->cardHolderData.cardHolderName);
        printf("PAN: %s\n"                         ,PtrAccount->cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date: %s\n"        ,PtrAccount->cardHolderData.cardExpirationDate);
        printf("#####################################\n");

        pn=pn->next;
    }
}
