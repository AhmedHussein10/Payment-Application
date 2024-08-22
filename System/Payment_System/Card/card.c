#include "../../Libraries/standard_libraries.h"
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    uint8_t name[25];
    printf ("Enter card holder's name (20:24 alphabetic characters) : ");
    gets  ((char*)name);
    if (strlen((char*)name)>24 || strlen((char*)name)<20)
        return WRONG_NAME;
    for (size_t i=0;i<strlen((char*)name);i++)
    {
        if (!((name[i]>='a' && name[i]<='z') ||
              (name[i]>='A' && name[i]<='Z') ||
              (name[i]==' ')))
            return WRONG_NAME;
    }
    strcpy ((char*)cardData->cardHolderName,(char*)name);
    return CARD_OK;
}
