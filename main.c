#include "System/Libraries/standard_libraries.h"
#include "System/Payment_System/Server/server.h"
#include "System/Data_Structures/List/list.h"
#include "System/Data_Bases/File_Handling/file_handling.h"


int main()
{
    Read_AccounDB_FromFile ();
    traverse_Accounts (&Account_DB,display);
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
