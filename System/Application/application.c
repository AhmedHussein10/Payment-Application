#include "../Libraries/standard_libraries.h"
#include "../Libraries/platform_type.h"
#include "application.h"
#include "../Data_Bases/File_Handling/file_handling.h"
#include "../Data_Structures/List/list.h"
#include "../Payment_System/Card/card.h"
#include "../Payment_System/Server/server.h"
#include "../Payment_System/Terminal/terminal.h"

void App_Start (void)
{
    create_list (&Transaction_DB);
    create_list (&Account_DB);
    Read_AccounDB_FromFile ();

    ST_cardData_t *cardData = (ST_cardData_t *)malloc(sizeof(ST_cardData_t));
    if (cardData == NULL)
    {
        printf("Out Of Memory \n");
        return;
    }
    ST_terminalData_t *termData = (ST_terminalData_t *)malloc(sizeof(ST_terminalData_t));
    if (termData == NULL)
    {
        printf("Out Of Memory \n");
        return;
    }
    ST_transaction_t *transData = (ST_transaction_t *)malloc(sizeof(ST_transaction_t));
    if (transData == NULL)
    {
        printf("Out Of Memory \n");
        return;
    }

    EN_cardError_t Card_State;
    EN_terminalError_t Term_State;
    EN_transState_t Trans_State;

    Card_State = getCardHolderName (cardData);
    while (Card_State != CARD_OK)
    {
        printf ("Wrong name, ");
        printf("Please try again.\n");
        Card_State = getCardHolderName(cardData);
    }

    Card_State = getCardExpiryDate (cardData);
    while (Card_State != CARD_OK)
    {
        printf ("Wrong date, ");
        printf("Please try again.\n");
        Card_State = getCardExpiryDate(cardData);
    }

    Term_State = getTransactionDate(termData);
    while (Term_State != TERMINAL_OK)
    {
        printf(" Wrong date, ");
        printf("Please try again.\n");
        Term_State = getTransactionDate(termData);
    }

    Term_State = isCardExpired(cardData, termData);
    while (Term_State != TERMINAL_OK)
    {
        printf("Card is expired\n");
        return;
    }

    Card_State = getCardPAN (cardData);
    while (Card_State != CARD_OK)
    {
        printf ("Wrong PAN, ");
        printf("Please try again.\n");
        Card_State = getCardPAN(cardData);
    }

    Term_State = isValidCardPAN (cardData);
    while (Term_State != TERMINAL_OK)
    {
        printf("Invalid PAN\n");
        return;
    }

    Term_State = setMaxAmount(termData,1000);
    while (Term_State != TERMINAL_OK)
    {
        printf("Invalid amount, ");
        printf("Please try again.\n");
        Term_State = setMaxAmount(termData,1000);
    }

    Term_State = getTransactionAmount(termData);
    while (Term_State != TERMINAL_OK)
    {
        printf("INVALID amount, ");
        printf("Please try again.\n");
        Term_State = getTransactionAmount(termData);
    }

    Term_State = isBelowMaxAmount(termData);
    if (Term_State != TERMINAL_OK)
    {
        printf("Amount Exceeds maximum allowed\n");
        return;
    }

    transData->cardHolderData= *cardData;
    transData->terminalData= *termData;

    Trans_State=recieveTransactionData (transData);
    if (Trans_State == INTERNAL_SERVER_ERROR)
    {
        printf("Transaction can't be saved\n");
    }
    else if (Trans_State == FRAUD_CARD)
    {
        printf("Account doesn't exist\n");
    }
    else if (Trans_State == DECLINED_INSUFFECIENT_FUND)
    {
        printf("Amount isn't available\n");
    }
    else if (Trans_State == DECLINED_STOLEN_CARD)
    {
        printf("Account is blocked\n");
    }
    else if (Trans_State == APPROVED)
    {
        printf("Transaction Approved\n");

        EN_serverError_t Server_State = saveTransaction(transData);
        if (Server_State == SAVING_FAILED)
            printf("Failed to save transaction data.\n");
    }

    listSavedTransactions();

}

