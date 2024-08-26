#include "../../Libraries/standard_libraries.h"
#include "../../Libraries/platform_type.h"
#include "../../Data_Structures/List/list.h"
#include "server.h"

EN_transState_t recieveTransactionData(ST_transaction_t *transData,list *Account_DB)
{
    if (transData==NULL || Account_DB==NULL)
        return INTERNAL_SERVER_ERROR;

    ST_accountsDB_t *PtrAccount=NULL;

    if(isValidAccount(&transData->cardHolderData,PtrAccount,Account_DB) == ACCOUNT_NOT_FOUND)
    {
        transData->transState = FRAUD_CARD;
        return FRAUD_CARD;
    }
    if(isAmountAvailable(&transData->terminalData,PtrAccount) == LOW_BALANCE)
    {
        transData->transState = DECLINED_INSUFFECIENT_FUND;
        return DECLINED_INSUFFECIENT_FUND;
    }
    if(isBlockedAccount(PtrAccount) == BLOCKED_ACCOUNT)
    {
        transData->transState = DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD ;
    }

    PtrAccount->balance -= transData->terminalData.transAmount;
    saveTransaction(transData);
    return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence,list *Account_DB)
{
    if (cardData==NULL || Account_DB==NULL)
        return INTERNAL_SERVER_ERROR;

    node *pn=Account_DB->head;

    while (pn)
    {
        ST_accountsDB_t *PtrAccount = (ST_accountsDB_t*)pn->ptr;
        if (strcmp(cardData->primaryAccountNumber,PtrAccount->primaryAccountNumber) == 0)
        {
            accountRefrence=PtrAccount;
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

}
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{

}
void listSavedTransactions(void)
{

}



