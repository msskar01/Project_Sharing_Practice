//Michael Skarlatov
//Lab 2: Currency exchange chart
//Section 2
//Date 1/18/18

//This program converts USD, GPB, CAD, EUR, and AUD currency

#include<stdio.h>

int main()
{
	//Defining currencey as a float
	float currencey = 0;
	
	//Asking and setting the amount of currencey
	printf("Enter in the amount of currencey you have: ");
	scanf("%f", &currencey);
	
	//Converting the currencey to every other currencey
	float USD_GBP = currencey*0.72;
	float USD_CAD = currencey*1.24;
	float USD_EUR = currencey*0.82;
	float USD_AUD = currencey*1.25;
	float GBP_USD = currencey*1.39;
	float GBP_CAD = currencey*1.73;
	float GBP_EUR = currencey*1.13;
	float GBP_AUD = currencey*1.74;
	float CAD_USD = currencey*0.80;
	float CAD_GBP = currencey*0.58;
	float CAD_EUR = currencey*0.66;
	float CAD_AUD = currencey*1.01;
	float EUR_USD = currencey*1.22;
	float EUR_GBP = currencey*0.88;
	float EUR_CAD = currencey*1.52;
	float EUR_AUD = currencey*1.53;
	float AUD_USD = currencey*0.80;
	float AUD_GBP = currencey*0.58;
	float AUD_CAD = currencey*0.99;
	float AUD_EUR = currencey*0.65;
	
	//Printing the currencey amount
	printf("Currencey                                      USD             GBP             CAD             EUR             AUD \n");
	printf("___________________________________________________________________________________________________________________\n");
	printf("Your%#10.2f in USD is equal to:| %#8.2f USD| %#8.2f GBP| %#8.2f CAD| %#8.2f EUR| %#8.2f AUD| \n", currencey, currencey, USD_GBP, USD_CAD, USD_EUR, USD_AUD);
	printf("Your%#10.2f in GBP is equal to:| %#8.2f USD| %#8.2f GBP| %#8.2f CAD| %#8.2f EUR| %#8.2f AUD| \n", currencey, GBP_USD, currencey, GBP_CAD, GBP_EUR, GBP_AUD);
	printf("Your%#10.2f in CAD is equal to:| %#8.2f USD| %#8.2f GBP| %#8.2f CAD| %#8.2f EUR| %#8.2f AUD| \n", currencey, CAD_USD, CAD_GBP, currencey, CAD_EUR, CAD_AUD);
	printf("Your%#10.2f in EUR is equal to:| %#8.2f USD| %#8.2f GBP| %#8.2f CAD| %#8.2f EUR| %#8.2f AUD| \n", currencey, EUR_USD, EUR_GBP, EUR_CAD, currencey, EUR_AUD);
	printf("Your%#10.2f in AUD is equal to:| %#8.2f USD| %#8.2f GBP| %#8.2f CAD| %#8.2f EUR| %#8.2f AUD| \n", currencey, AUD_USD, AUD_GBP, AUD_CAD, AUD_EUR, currencey);
	printf("------------------------------------------------------------------------------------------------------------------|");
	return 0;
}
