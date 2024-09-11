#include "System/Libraries/standard_libraries.h"
#include "System/Application/application.h"
#include "System/Data_Structures/List/list.h"
#include "System/Data_Bases/File_Handling/file_handling.h"
#include "System/Payment_System/Server/server.h"


int main()
{

    int userChoice=1;

    while (userChoice)
    {
        create_list (&Transaction_DB);
        create_list (&Account_DB);

        do {
                printf("\n------- PAYMENT APPLICATION --------\n");
                printf(" __________________________________\n");
                printf("|                                  |\n");
                printf("|     1. Do a transaction          |\n");
                printf("|                                  |\n");
                printf("|     2. Display transactions list |\n");
                printf("|                                  |\n");
                printf("|     0. Exit                      |\n");
                printf("|__________________________________|\n");
                printf("\nPlease select your choice : ");
                scanf(" %d", &userChoice);
                fflush(stdin);
                system("cls");
                if (userChoice == 1)
                {
                    userChoice = 1;
                    App_Start();
                    break;
                }
                else if (userChoice == 2)
                {
                    userChoice = 2;
                    Read_TransactionDB_FromFile ();
                    system("cls");
                    listSavedTransactions ();
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

    clear_list (&Account_DB);
    clear_list (&Transaction_DB);

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
