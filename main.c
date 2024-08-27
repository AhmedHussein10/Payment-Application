#include "System/Libraries/standard_libraries.h"
#include "System/Payment_System/Server/server.h"
#include "System/Data_Structures/List/list.h"
#include "System/Data_Bases/File_Handling/file_handling.h"
#include "System/Application/application.h"


int main()
{
    list l;
    create_list (&l);
    Read_AccounDB_FromFile (&l);
    printf ("%d",list_size (&l));
    //App_Start();
    /*getCardHolderNameTest();
    getCardExpiryDateTest();
    getCardPANTest();
    //getTransactionDateTest();
    isCardExpriedTest();
    getTransactionAmountTest();
    isBelowMaxAmountTest();
    setMaxAmountTest();
    isValidCardPANTest();*/

    return 0;
}
