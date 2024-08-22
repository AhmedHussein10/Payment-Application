#include "../../Libraries/standard_libraries.h"
#include "terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    time_t t=time(NULL);
    struct tm *d=localtime(&t);
    uint8_t date[11];
    strftime ((char*)date,11,"%d/%m/%Y",d);
    if (strlen((char*)date)!=10         ||
       (date[2]!='/' &&  date[5]!='/')  ||
       (date[4]<'1'  && date[3]<'1')    ||
       (date[3]=='1' && date[4]>'2')    ||
        date[3]>'1')
        return WRONG_DATE;
    for (size_t i=0;i<strlen((char*)date);i++)
    {
        if (!((date[i]>='0' && date[i]<='9') || (date[i]=='/')))
            return WRONG_DATE;
    }
    strcpy((char*)termData->transactionDate,(char*)date);
    return TERMINAL_OK;
}



EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    if (cardData->cardExpirationDate[3]<termData->transactionDate[8]    ||            //comparison between the years

        (cardData->cardExpirationDate[3]==termData->transactionDate[8] &&
        cardData->cardExpirationDate[4]<termData->transactionDate[9]))
           return EXPIRED_CARD;
    else if((cardData->cardExpirationDate[3]==termData->transactionDate[8]  &&        //comparison between months if the same year
           cardData->cardExpirationDate[4]==termData->transactionDate[9]))
           {
               if (cardData->cardExpirationDate[3]<termData->transactionDate[8]   ||

                  (cardData->cardExpirationDate[0]==termData->transactionDate[3] &&
                  cardData->cardExpirationDate[1]<termData->transactionDate[4]))
                      return EXPIRED_CARD;
           }
    return CARD_OK;
}
