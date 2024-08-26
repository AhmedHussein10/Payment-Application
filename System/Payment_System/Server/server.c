#include "../../Libraries/standard_libraries.h"
#include "../../Libraries/platform_type.h"
#include "../../Data_Structures/List/list.h"
#include "server.h"

EN_transState_t recieveTransactionData(ST_transaction_t *transData,list *Account_DB)
{
    if (transData==NULL || Account_DB==NULL)
        return INTERNAL_SERVER_ERROR;
    node *pn=Account_DB->head;
    ST_accountsDB_t *Account=NULL;
    ST_accountsDB_t *PtrAccount =(ST_accountsDB_t *)pn->ptr;
    while (pn)
    {
        if (strcmp(transData->cardHolderData.primaryAccountNumber,PtrAccount->primaryAccountNumber) == 0)
        {
            Account=PtrAccount;
            break;
        }

        pn=pn->next;
    }

    if (Account==NULL)
        return FRAUD_CARD;

    if(isAmountAvailable(&transData->terminalData,Account) == LOW_BALANCE)
    {
        transData->transState = DECLINED_INSUFFECIENT_FUND;
        return DECLINED_INSUFFECIENT_FUND;
    }
    if(isBlockedAccount(Account) == BLOCKED_ACCOUNT)
    {
        transData->transState = DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD ;
    }

    Account->balance -= transData->terminalData.transAmount;
    saveTransaction(transData);
    return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{

}
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{

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



