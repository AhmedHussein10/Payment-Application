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


EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    uint8_t date[6];
    printf ("Enter card's expiry date (MM/YY) : ");
    gets  ((char*)date);
    if (strlen((char*)date)!=5       ||
        date[2]!='/'                 ||
        date[0]>'1'                  ||
        (date[1]<'1' && date[0]<'1') ||
        (date[0]=='1' && date[1]>'2'))
        return WRONG_EXP_DATE;
    for (size_t i=0;i<strlen((char*)date);i++)
    {
        if (!((date[i]>='0' && date[i]<='9') || (date[i]=='/')))
            return WRONG_EXP_DATE;
    }
    strcpy((char*)cardData->cardExpirationDate,(char*)date);
    return CARD_OK;
}


EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    uint8_t pan[20];
    printf ("Enter card's PAN : ");
    gets ((char*)pan);
    if (strlen((char*)pan)>19 || strlen((char*)pan)<16)
        return WRONG_PAN;
    for (size_t i=0;i<strlen((char*)pan);i++)
    {
        if (!(pan[i]>='0' && pan[i]<='9'))
            return WRONG_PAN;
    }
    strcpy((char*)cardData->primaryAccountNumber,(char*)pan);
    return CARD_OK;
}
