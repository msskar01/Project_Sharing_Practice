//Michael Skarlatov
//Lab 4: Calculator
//Section 2
//Date 2/5/18

#include<stdio.h>
#include<math.h>
int i;

//Addition function
float add(float number1,float number2)
{
	return (number1 + number2);
}
//Subtraction function
float subtract(float number1,float number2)
{
	return (number1-number2);
}
//Multiplication function
float multiplication(float number1,float number2)
{
	return (number1*number2);
}
//devision function
float devision(float number1,float number2)
{
	return (number1/number2);
}
//Modulus function
int modulus(int number1,int number2)
{
	return (number1%number2);
}
//Actual check prime function
int prime(int number1)
{
	int i;
	if(number1 <= 1 && number1 != 0)
	{
		return 1;
	}
	if((number1 % 2 == 0 && number1 > 2) || number1 == 0)
	{
		return 0;
	}
	for(i=3; i < number1/2; i+=2)
	{
		if(number1%i == 0)
		{
			return 0;	
			break;
		}
	}
	return 1;
}

//This is all just to get information for if the number is not prime
int prime2(int number1)
{
	int i,prime_number;
	if (number1 == 0)
	{
		return 0;
	}
	for(i=2; i < number1; i++)
	{
		if(number1%i == 0)
		{
			int prime_number = i;
			return prime_number;
			break;
		}
	}
}
int prime3(int number1)
{
	int i, prim_number2;
	if (number1 == 0)
	{
		return 0;
	}
	for(i=2; i < number1; i++)
	{
		if(number1%i == 0)
		{
			int prime_number2 = number1/i;
			return prime_number2;
			break;
		}
	}
}
//ends here
//Factorial function
int fact(int number1)
{
	int factorial = 1;
	for(i=1; i<=number1; i++)
	{
		factorial = i*factorial;
	}
	return factorial;
}
//Power function
float power(float number1,float number2)
{
	return pow(number1,number2);
}
//Fibonacci function
int fibonacci(int number1)
{
	int n1 = 0;
	int n2 = 1;
	int next;
	for(i=1; i<=number1; i++)
	{
		next = n1 + n2;
		n1 = n2;
		n2 = next;
		if(i==number1)
		{
			return n1;
		}
	}
}

void main()
{
	int end_operation=0;
	int operation;
	do
	{
		
		float first_number, second_number;
		printf("Calculator Menu:\n");
		printf("(1) Addition\n");
		printf("(2) Subtraction\n");
		printf("(3) Multiplication\n");
		printf("(4) Division\n");
		printf("(5) Modulus (integers only)\n");
		printf("(6) Test if prime (integers only)\n");
		printf("(7) Factorial (integers only)\n");
		printf("(8) Power\n");
		printf("(9) Fibonacci function(choose how long you want the sequince starting from zero)\n");
		printf("(0) Exit\n");
		
		printf("Please choose an operation:");
		scanf("%d", &operation);
		
		switch(operation)
		{
			case 1:
				printf("Enter the first number:");
				scanf("%f", &first_number);
				printf("Enter the second number:");
				scanf("%f", &second_number);
				if(first_number-(int)first_number==0 && second_number-(int)second_number==0)
				{
					printf("%d + %d = %d\n\n", (int)first_number, (int)second_number, (int)add(first_number,second_number));
				}
				else
				{
					printf("%f + %f = %f\n\n", first_number, second_number, add(first_number,second_number));
				}

				break;
			case 2:
				printf("Enter the first number:");
				scanf("%f", &first_number);
				printf("Enter the second number:");
				scanf("%f", &second_number);
				if(first_number-(int)first_number==0 && second_number-(int)second_number==0)
				{
					printf("%d - %d = %d\n\n", (int)first_number, (int)second_number, (int)subtract(first_number,second_number));
				}
				else
				{
					printf("%f - %f = %f\n\n", first_number, second_number, subtract(first_number,second_number));
				}
				break;
			case 3:
				printf("Enter the first number:");
				scanf("%f", &first_number);
				printf("Enter the second number:");
				scanf("%f", &second_number);
				if(first_number-(int)first_number==0 && second_number-(int)second_number==0)
				{
					printf("%d * %d = %d\n\n", (int)first_number, (int)second_number, (int)multiplication(first_number,second_number));
				}
				else
				{
					printf("%f * %f = %f\n\n", first_number, second_number, multiplication(first_number,second_number));
				}
				break;
			case 4:
				printf("Enter the first number:");
				scanf("%f", &first_number);
				printf("Enter the second number:");
				scanf("%f", &second_number);
				if(first_number-(int)first_number==0 && second_number-(int)second_number==0 && devision(first_number,second_number)-(int)devision(first_number,second_number)==0)
				{
					printf("%d / %d = %d\n\n", (int)first_number, (int)second_number, (int)devision(first_number,second_number));
				}
				else
				{
					printf("%f / %f = %f\n\n", first_number, second_number, devision(first_number,second_number));
				}
				break;
			case 5:
				printf("Enter the first number(integers only):");
				scanf("%f", &first_number);
				printf("Enter the second number(integers only):");
				scanf("%f", &second_number);
				printf("%d %% %d = %d\n\n", (int)first_number, (int)second_number, modulus((int)first_number,(int)second_number));
				break;
			case 6:
				printf("Enter in a number to be tested(integers only):");
				scanf("%f", &first_number);
				switch(prime((int)first_number))
				{
					case 0:
						printf("The number is not prime. %d * %d = %d\n\n", prime2((int)first_number), prime3((int)first_number), (int)first_number);
						break;
					default:
						printf("The number is prime\n\n");
						break;
				}
				break;
			case 7:
				printf("Enter in a number(integers only):");
				scanf("%f", &first_number);
				for(i=1; i<=(int)first_number; i++)
				{
					printf("%dX", i);
				}
				printf("=\n%d\n\n", fact((int)first_number));
				break;
			case 8:
				printf("Enter the first number:");
				scanf("%f", &first_number);
				printf("Enter the second number:");
				scanf("%f", &second_number);
				if(first_number-(int)first_number==0 && second_number-(int)second_number==0)
				{
					printf("%d ^ %d = %d\n\n", (int)first_number, (int)second_number, (int)power(first_number,second_number));
				}
				else
				{
					printf("%f^%f = %f\n\n", first_number, second_number, power(first_number,second_number));
				}
				break;
			case 9:
				printf("Enter in the number of terms:");
				scanf("%f", &first_number);
				printf("0  ");
				for(i=1; i<=(int)first_number-1; i++)
				{
					printf("%d  ", fibonacci(i));
				}
				printf("\n\n");
				break;
			case 0:
				printf("Good Bye!");
				break;
			default:
				printf("Invalid input\n\n");
				break;
		}
	}
	while(operation != end_operation);

}
