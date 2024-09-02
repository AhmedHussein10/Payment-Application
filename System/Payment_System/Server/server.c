#include "../../Libraries/standard_libraries.h"
#include "../../Libraries/platform_type.h"
#include "../../Data_Bases/File_Handling/file_handling.h"
#include "../../Data_Structures/List/list.h"
#include "server.h"

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    if (transData == NULL)
        return INTERNAL_SERVER_ERROR;

    ST_accountsDB_t *PtrAccount=NULL;

    node *pn=Account_DB.head;

    while (pn)
    {
        if (strcmp(transData->cardHolderData.primaryAccountNumber,((ST_accountsDB_t*)pn->ptr)->primaryAccountNumber) == 0)
        {
            PtrAccount=pn->ptr;
            break;
        }
        pn=pn->next;
    }

    if(isValidAccount(&transData->cardHolderData,PtrAccount) == ACCOUNT_NOT_FOUND)
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

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
    if (cardData == NULL)
        return ACCOUNT_NOT_FOUND;

    node *pn=Account_DB.head;

    while (pn)
    {
        if (strcmp(cardData->primaryAccountNumber,((ST_accountsDB_t*)pn->ptr)->primaryAccountNumber) == 0)
        {
            accountRefrence=pn->ptr;
            break;
        }
        pn=pn->next;
    }

    if (accountRefrence==NULL)
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

