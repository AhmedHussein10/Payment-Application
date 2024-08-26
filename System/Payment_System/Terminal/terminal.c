#include "../../Libraries/standard_libraries.h"
#include "terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    if (termData==NULL)
        return WRONG_DATE;
    time_t t=time(NULL);
    struct tm *d=localtime(&t);
    char date[11];
    strftime (date,11,"%d/%m/%Y",d);
    if (strlen(date)!=10               ||
       (date[2]!='/' && date[5]!='/')  ||
       (date[4]<'1'  && date[3]<'1')   ||
       (date[3]=='1' && date[4]>'2')   ||
        date[3]>'1')
        return WRONG_DATE;
    for (size_t i=0;i<10;i++)
    {
        if (!((date[i]>='0' && date[i]<='9') || (date[i]=='/')))
            return WRONG_DATE;
    }
    for (size_t i=0;i<10;i++)
    {
        termData->transactionDate[i]=date[i];
    }
    termData->transactionDate[10]='\0';
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
    fflush(stdin);
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
    uint8_t len=strlen((char*)cardData->primaryAccountNumber);

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
    if ((EvenSum+OddSum)%10!=0 || (EvenSum+OddSum)<=0)
        return INVALID_CARD;
    return TERMINAL_OK;
}


/*void getTransactionDateTest(void)
{
    ST_terminalData_t TermData;
    EN_terminalError_t Test;
    printf("Tester Name : Ahmed Hussein \n");
    printf("Function Name : getTransactionDate \n");
    printf("----------------------------------------------\n");
    printf("Test Case 1:NULL\n");
    printf("Input Data: \n");
    Test = getTransactionDate(&TermData);
    printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result: %s\n", Test == WRONG_DATE ? "WRONG_DATE" : "TERMINAL_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 2: 20-10-2025\n");
    printf("Input Data:");
    Test=getTransactionDate(&TermData);
    printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result:%s\n",Test==WRONG_DATE? "WRONG_DATE":"TERMINAL_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 3: 10/8/2022 \n");
    printf("Input Data:\n");
    Test=getTransactionDate(&TermData);
    printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result:%s\n",Test==WRONG_DATE? "WRONG_DATE":"TERMINAL_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 4: 22/08/20252\n");
    printf("Input Data:\n");
    Test=getTransactionDate(&TermData);
    printf("Expected Result: WRONG_DATE\n");
    printf("Actual Result:%s\n",Test==TERMINAL_OK? "TERMINAL_OK":"WRONG_DATE");
    printf("----------------------------------------------\n");
    printf("Test Case 5: 23/08/2025 \n");
    printf("Input Data:\n");
    Test=getTransactionDate(&TermData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result:%s\n",Test==TERMINAL_OK? "TERMINAL_OK":"WRONG_DATE");
    printf("----------------------------------------------\n");
}*/

void isCardExpriedTest(void)
{
    ST_cardData_t CardData;
    ST_terminalData_t TermData;
    EN_terminalError_t Test;
    printf("Tester Name : Ahmed Hussein\n");
    printf("Function Name : isCardExpired \n");
    printf("----------------------------------------------\n");
    printf("Test Case 1:NULL\n");
    printf("Input Data: ");
    Test=getCardExpiryDate(NULL);
    Test=getTransactionDate(NULL);
    Test = isCardExpired(NULL,NULL);
    printf("Expected Result: EXPIRED_CARD\n");
    printf("Actual Result: %s\n", Test == EXPIRED_CARD ? "EXPIRED_CARD" : "TERMINAL_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 2:put Expired date\n");
    printf("Input Data:");
    getCardExpiryDate(&CardData);
    getTransactionDate(&TermData);
    Test = isCardExpired(&CardData,&TermData);
    printf("Expected Result: EXPIRED_CARD\n");
    printf("Actual Result: %s\n", Test == EXPIRED_CARD ? "EXPIRED_CARD" : "TERMINAL_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 3:put valid date\n");
    printf("Input Data:");
    getCardExpiryDate(&CardData);
    getTransactionDate(&TermData);
    Test = isCardExpired(&CardData,&TermData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", Test == EXPIRED_CARD ? "EXPIRED_CARD" : "TERMINAL_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 4:today's date\n");
    printf("Input Data:");
    getCardExpiryDate(&CardData);
    getTransactionDate(&TermData);
    Test = isCardExpired(&CardData,&TermData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", Test == EXPIRED_CARD ? "EXPIRED_CARD" : "TERMINAL_OK");
    printf("----------------------------------------------\n");
}


void getTransactionAmountTest(void)
{
    ST_terminalData_t TermData;
    EN_terminalError_t Test;
    printf("Tester Name : Ahmed Hussein \n");
    printf("Function Name : getTransactionAmount \n");
    printf("----------------------------------------------\n");
    printf("Test Case 1: 0 \n");
    printf("Input Data: ");
    Test = getTransactionAmount(&TermData);
    printf("Expected Result: INVALID_AMOUNT\n");
    printf("Actual Result: %s\n", Test == INVALID_AMOUNT ? "INVALID_AMOUNT" : "TERMINAL_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 2: -1000\n");
    printf("Input Data:");
    Test=getTransactionAmount(&TermData);
    printf("Expected Result: INVALID_AMOUNT\n");
    printf("Actual Result:%s\n",Test==INVALID_AMOUNT? "INVALID_AMOUNT":"TERMINAL_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 3: 1000 \n");
    printf("Input Data: ");
    Test=getTransactionAmount(&TermData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result:%s\n",Test==TERMINAL_OK? "TERMINAL_OK":"INVALID_AMOUNT");
    printf("----------------------------------------------\n");
}



void isBelowMaxAmountTest(void)
{
    ST_terminalData_t TermData;
    EN_terminalError_t Test;
    setMaxAmount(&TermData,1000);
    printf("Tester Name : Ahmed Hussein \n");
    printf("Function Name : isBelowMaxAmount \n");
    printf("----------------------------------------------\n");
    printf("Test Case 1:Amount greater than max (1000)\n");
    printf("Input Data:");
    getTransactionAmount(&TermData);
    Test=isBelowMaxAmount(&TermData);
    printf("Expected Result: EXCEED_MAX_AMOUNT\n");
    printf("Actual Result:%s\n",Test==EXCEED_MAX_AMOUNT ? "EXCEED_MAX_AMOUNT" : "TERMINAL_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 2:Amount equal max (1000)\n");
    printf("Input Data:");
    getTransactionAmount(&TermData);
    Test=isBelowMaxAmount(&TermData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result:%s\n",Test==TERMINAL_OK? "TERMINAL_OK":"EXCEED_MAX_AMOUNT");
    printf("----------------------------------------------\n");
    printf("Test Case 3:Amount less than max (1000)\n");
    printf("Input Data:");
    getTransactionAmount(&TermData);
    Test=isBelowMaxAmount(&TermData);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result:%s\n",Test==TERMINAL_OK? "TERMINAL_OK":"EXCEED_MAX_AMOUNT");
    printf("----------------------------------------------\n");
}

void setMaxAmountTest(void)
{
    ST_terminalData_t TermData;
    EN_terminalError_t Test;
    printf("Tester Name : Ahmed Hussein \n");
    printf("Function Name : setMaxAmount \n");
    printf("----------------------------------------------\n");
    printf("Test Case 1:Negative\n");
    printf("Input Data:");
    Test=setMaxAmount(&TermData,-1000);
    printf("Expected Result: INVALID_MAX_AMOUNT\n");
    printf("Actual Result:%s\n",Test==INVALID_MAX_AMOUNT? "INVALID_MAX_AMOUNT":"TERMINAL_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 2: 0 \n");
    printf("Input Data:");
    Test=setMaxAmount(&TermData,0);
    printf("Expected Result: INVALID_MAX_AMOUNT\n");
    printf("Actual Result:%s\n",Test==TERMINAL_OK? "TERMINAL_OK":"INVALID_MAX_AMOUNT");
    printf("----------------------------------------------\n");
    printf("Test Case 3:positive\n");
    printf("Input Data:");
    Test=setMaxAmount(&TermData,1000);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result:%s\n",Test==TERMINAL_OK? "TERMINAL_OK":"INVALID_MAX_AMOUNT");
    printf("----------------------------------------------\n");
}

void isValidCardPANTest(void)
{
    ST_cardData_t CardData;
    EN_terminalError_t Test;
    printf("Tester Name : Ahmed Hussein \n");
    printf("Function Name : isValidCardPAN \n");
    printf("----------------------------------------------\n");
    printf("Test Case 1:NULL\n");
    printf("Input Data:");
    getCardPAN(&CardData);
    Test=isValidCardPAN(&CardData);
    printf("Expected Result: INVALID_CARD\n");
    printf("Actual Result:%s\n",Test==INVALID_CARD? "INVALID_CARD":"TERMINAL_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 2:valid pan\n");
    printf("Input Data:");
    getCardPAN(&CardData);
    Test=isValidCardPAN(&CardData);
    printf("Expected Result: terminal_ok\n");
    printf("Actual Result:%s\n",Test==INVALID_CARD? "INVALID_CARD":"TERMINAL_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 3:invalid pan\n");
    printf("Input Data:");
    getCardPAN(&CardData);
    Test=isValidCardPAN(&CardData);
    printf("Expected Result: Invalid_Card\n");
    printf("Actual Result:%s\n",Test==INVALID_CARD? "INVALID_CARD":"TERMINAL_OK");
    printf("----------------------------------------------\n");
}
