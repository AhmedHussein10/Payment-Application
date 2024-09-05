#include "System/Libraries/standard_libraries.h"
#include "System/Application/application.h"


int main()
{

    int userChoice=1;

    while (userChoice)
    {
        App_Start();

        do {
                printf("\t\t\t _________________________________\n");
                printf("\t\t\t|                                 |\n");
                printf("\t\t\t|     1. Do another transaction   |\n");
                printf("\t\t\t|                                 |\n");
                printf("\t\t\t|     0. Exit                     |\n");
                printf("\t\t\t|_________________________________|\n");
                printf("\nPlease select your choice : ");
                scanf(" %d", &userChoice);
                fflush(stdin);
                if (userChoice == 1)
                {
                    userChoice = 1;
                    break;
                }
                else if (userChoice == 0)
                {
                    userChoice = 0;
                    break;
                }
                else
                {
                    printf("Invalid input, Please enter '1' or '0'.\n");
                }
            }

         while (1);
    }

    /*getCardHolderNameTest();
    getCardExpiryDateTest();
    getCardPANTest();
    getTransactionDateTest();
    isCardExpriedTest();
    getTransactionAmountTest();
    isBelowMaxAmountTest();
    setMaxAmountTest();
    isValidCardPANTest();*/

    return 0;
}
