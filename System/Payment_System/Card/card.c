#include "../../Libraries/standard_libraries.h"
#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    if (cardData==NULL)
        return WRONG_NAME;
    uint8_t name[25];
    //printf ("Enter card holder's name (20:24 alphabetic characters) : ");
    gets  ((char*)name);
    uint8_t length=strlen((char*)name);
    if (length>24 || length<20)
        return WRONG_NAME;
    for (size_t i=0;i<length;i++)
    {
        if (!(isalpha (name[i])) && name[i]!=' ')
            return WRONG_NAME;
    }
    for (size_t i=0;i<length;i++)
    {
        cardData->cardHolderName[i]=name[i];
    }
    cardData->cardHolderName[length]='\0';
    return CARD_OK;
}


EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    if (cardData==NULL)
        return WRONG_EXP_DATE;
    uint8_t date[6];
    //printf ("Enter card's expiry date (MM/YY) : ");
    gets  ((char*)date);
    uint8_t length=strlen((char*)date);
    if  (length!=5                   ||
        date[2]!='/'                 ||
        date[0]>'1'                  ||
        (date[1]<'1' && date[0]<'1') ||
        (date[0]=='1' && date[1]>'2'))
        return WRONG_EXP_DATE;
    for (size_t i=0;i<length;i++)
    {
        if (!((date[i]>='0' && date[i]<='9') || (date[i]=='/')))
            return WRONG_EXP_DATE;
    }
    for (size_t i=0;i<length;i++)
    {
        cardData->cardExpirationDate[i]=date[i];
    }
    cardData->cardExpirationDate[length]='\0';
    return CARD_OK;
}


EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    if (cardData==NULL)
        return WRONG_PAN;
    uint8_t pan[20];
    //printf ("Enter card's PAN : ");
    gets ((char*)pan);
    uint8_t length=strlen((char*)pan);
    if (length>19 || length<16)
        return WRONG_PAN;
    for (size_t i=0;i<length;i++)
    {
        if (!(pan[i]>='0' && pan[i]<='9'))
            return WRONG_PAN;
    }
    for (size_t i=0;i<length;i++)
    {
        cardData->primaryAccountNumber[i]=pan[i];
    }
    cardData->primaryAccountNumber[length]='\0';
    return CARD_OK;
}




void getCardHolderNameTest(void)
{
    ST_cardData_t CardData;
    EN_cardError_t Test;
    printf("Tester Name : Ahmed Hussein \n");
    printf("Function Name : getCardHolderName \n");
    printf("----------------------------------------------\n");
    printf("Test Case 1:NULL\n");
    printf("Input Data:");
    Test = getCardHolderName(&CardData);
    printf("Expected Result: WRONG_NAME\n");
    printf("Actual Result: %s\n", Test == WRONG_NAME ? "WRONG_NAME" : "CARD_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 2: Ahmed Hussein\n");
    printf("Input Data:");
    Test=getCardHolderName(&CardData);
    printf("Expected Result: WRONG_NAME\n");
    printf("Actual Result:%s\n",Test==WRONG_NAME ? "WRONG_NAME" : "CARD_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 3: Ahmed Hussein Ahmed 12A\n");
    printf("Input Data:");
    Test=getCardHolderName(&CardData);
    printf("Expected Result: WRONG_NAME\n");
    printf("Actual Result:%s\n",Test==WRONG_NAME ? "WRONG_NAME" : "CARD_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 4:Hussein Ahmed Hussein\n");
    printf("Input Data:");
    Test=getCardHolderName(&CardData);
    printf("Expected Result: CARD_OK\n");
    printf("Actual Result:%s\n",Test==CARD_OK ? "CARD_OK" : "WRONG_NAME");
    printf("----------------------------------------------\n");
}



void getCardExpiryDateTest (void)
{
    ST_cardData_t CardData;
    EN_cardError_t Test;
    printf("Tester Name : Ahmed Hussein \n");
    printf("Function Name : getCardExpiryDate \n");
    printf("----------------------------------------------\n");
    printf("Test Case 1:NULL\n");
    printf("Input Data:");
    Test=getCardExpiryDate(&CardData);
    printf("Expected Result: WRONG_EXP_DATE\n");
    printf("Actual Result:%s\n",Test==WRONG_EXP_DATE ? "WRONG_EXP_DATE" : "CARD_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 2:08*25\n");
    printf("Input Data:");
    Test=getCardExpiryDate(&CardData);
    printf("Expected Result: WRONG_EXP_DATE\n");
    printf("Actual Result:%s\n",Test==WRONG_EXP_DATE ? "WRONG_EXP_DATE" : "CARD_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 3:15/25\n");
    printf("Input Data:");
    Test=getCardExpiryDate(&CardData);
    printf("Expected Result: WRONG_EXP_DATE\n");
    printf("Actual Result:%s\n",Test==WRONG_EXP_DATE? "WRONG_EXP_DATE":"CARD_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 4:10/a5\n");
    printf("Input Data:");
    Test=getCardExpiryDate(&CardData);
    printf("Expected Result: WRONG_EXP_DATE\n");
    printf("Actual Result:%s\n",Test==WRONG_EXP_DATE ? "WRONG_EXP_DATE":"CARD_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 5:08/25\n");
    printf("Input Data:");
    Test=getCardExpiryDate(&CardData);
    printf("Expected Result: CARD_OK\n");
    printf("Actual Result:%s\n",Test==WRONG_EXP_DATE ? "WRONG_EXP_DATE":"CARD_OK");
    printf("----------------------------------------------\n");
}



void getCardPANTest(void)
{
    ST_cardData_t CardData;
    EN_cardError_t Test;
    printf("Tester Name : Ahmed Hussein \n");
    printf("Function Name : getCardPAN \n");
    printf("----------------------------------------------\n");
    printf("Test Case 1:NULL\n");
    printf("Input Data:");
    Test=getCardPAN(&CardData);
    printf("Expected Result: WRONG_PAN\n");
    printf("Actual Result:%s\n",Test==WRONG_PAN ? "WRONG_PAN":"CARD_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 2: 123456789\n");
    printf("Input Data:");
    Test=getCardPAN(&CardData);
    printf("Expected Result: WRONG_PAN\n");
    printf("Actual Result:%s\n",Test==WRONG_PAN ? "WRONG_PAN":"CARD_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 3: 123456789123456789123456789\n");
    printf("Input Data:");
    Test=getCardPAN(&CardData);
    printf("Expected Result: WRONG_PAN\n");
    printf("Actual Result:%s\n",Test==WRONG_PAN ? "WRONG_PAN":"CARD_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 4: 123456789a123456\n");
    printf("Input Data:");
    Test=getCardPAN(&CardData);
    printf("Expected Result: WRONG_PAN\n");
    printf("Actual Result:%s\n",Test==WRONG_PAN ? "WRONG_PAN":"CARD_OK");
    printf("----------------------------------------------\n");
    printf("Test Case 5: 1234567891234567\n");
    printf("Input Data:");
    Test=getCardPAN(&CardData);
    printf("Expected Result: CARD_OK\n");
    printf("Actual Result:%s\n",Test==WRONG_PAN ? "WRONG_PAN":"CARD_OK");
    printf("----------------------------------------------\n");
}
