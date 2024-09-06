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

    Read_AccounDB_FromFile ();

    ST_transaction_t *transData = (ST_transaction_t *)malloc(sizeof(ST_transaction_t));
    if (transData == NULL)
    {
        printf("Out Of Memory \n");
        return;
    }

    EN_transState_t Trans_State;

    Trans_State=recieveTransactionData (transData);



    if (Trans_State == INTERNAL_SERVER_ERROR)
    {
        printf("\nTransaction can't be saved\n");
    }
    else if (Trans_State == FRAUD_CARD)
    {
        printf("\nAccount doesn't exist\n");
    }
    else if (Trans_State == DECLINED_INSUFFECIENT_FUND)
    {
        printf("\nAmount isn't available\n");
    }
    else if (Trans_State == DECLINED_STOLEN_CARD)
    {
        printf("\nAccount is blocked\n");
    }
    else if (Trans_State == APPROVED)
    {
        printf("\nTransaction Approved\n");
    }

    EN_serverError_t Server_State = saveTransaction(transData);

    if (Server_State == SAVING_FAILED)
        printf("\nFailed to save transaction data.\n");


    free (transData);

}

