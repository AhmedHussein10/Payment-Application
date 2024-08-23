#include "../../Libraries/standard_libraries.h"
#include "terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    if (termData==NULL)
        return WRONG_DATE;
    time_t t=time(NULL);
    struct tm *d=localtime(&t);
    uint8_t date[11];
    strftime (date,11,"%d/%m/%Y",d);
    if (strlen(date)!=10               ||
       (date[2]!='/' && date[5]!='/')  ||
       (date[4]<'1'  && date[3]<'1')   ||
       (date[3]=='1' && date[4]>'2')   ||
        date[3]>'1')
        return WRONG_DATE;
    for (size_t i=0;i<strlen(date);i++)
    {
        if (!((date[i]>='0' && date[i]<='9') || (date[i]=='/')))
            return WRONG_DATE;
    }
    for (size_t i=0;i<strlen(date);i++)
    {
        termData->transactionDate[i]=date[i];
    }
    termData->transactionDate[strlen(date)]='\0';
    return TERMINAL_OK;
}



EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    if (termData==NULL || cardData==NULL)
        return EXPIRED_CARD;
    if (cardData->cardExpirationDate[3]<termData->transactionDate[8]    ||            //comparison between the years

        (cardData->cardExpirationDate[3]==termData->transactionDate[8] &&
        cardData->cardExpirationDate[4]<termData->transactionDate[9]))
           return EXPIRED_CARD;
    else if((cardData->cardExpirationDate[3]==termData->transactionDate[8]  &&        //comparison between months if it is the same year
           cardData->cardExpirationDate[4]==termData->transactionDate[9]))
           {
               if (cardData->cardExpirationDate[3]<termData->transactionDate[8]   ||

                  (cardData->cardExpirationDate[0]==termData->transactionDate[3] &&
                  cardData->cardExpirationDate[1]<termData->transactionDate[4]))
                      return EXPIRED_CARD;
           }
    return CARD_OK;
}



EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    if (termData==NULL)
        return INVALID_AMOUNT;
    float amount;
    printf ("Enter transaction amount : ");
    scanf  ("%f",&amount);
    if (amount<=0)
        return INVALID_AMOUNT;
    termData->transAmount=amount;
    return TERMINAL_OK;
}



EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if (termData==NULL)
        return EXCEED_MAX_AMOUNT;
    if (termData->transAmount > termData->maxTransAmount)
        return EXCEED_MAX_AMOUNT;
    return TERMINAL_OK;
}



EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
    if (termData==NULL)
        return INVALID_MAX_AMOUNT;
    if (maxAmount<=0)
        return INVALID_MAX_AMOUNT;
    termData->maxTransAmount=maxAmount;
    return TERMINAL_OK;
}



EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
    if (cardData==NULL)
        return INVALID_CARD;
    int OddSum=0;
    int EvenDouble=0;
    int EvenSum=0;
    int len=strlen(cardData->primaryAccountNumber);

    for (size_t i=0;i<len;i++)
    {
        uint8_t digit =cardData->primaryAccountNumber[i]-48;
        if (i%2==0)
        {
            EvenDouble=digit*2;
            if (EvenDouble>9)
                EvenDouble-=9;
            EvenSum+=EvenDouble;
        }
        else
            OddSum+=digit;
    }
    if ((EvenSum+OddSum)%10!=0)
        return INVALID_CARD;
    return TERMINAL_OK;
}
