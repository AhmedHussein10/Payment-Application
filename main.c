#include "System/Libraries/standard_libraries.h"
#include "System/Payment_System/Server/server.h"
#include "System/Data_Structures/List/list.h"


int main()
{
    list l;
    create_list (&l);
    getCardHolderNameTest();
    getCardExpiryDateTest();
    getCardPANTest();
    //getTransactionDateTest();
    isCardExpriedTest();
    getTransactionAmountTest();
    isBelowMaxAmountTest();
    setMaxAmountTest();
    isValidCardPANTest();

    return 0;
}
