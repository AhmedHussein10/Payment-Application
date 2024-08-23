#include "System/Libraries/standard_libraries.h"
#include "System/Payment_System/Card/card.h"
#include "System/Payment_System/Terminal/terminal.h"
#include "System/Payment_System/Server/server.h"


int main()
{
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
