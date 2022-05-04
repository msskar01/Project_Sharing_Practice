//Michael Skarlatov
//Lab 3: Calculator
//Section 2
//Date 1/25/18

#include<stdio.h>

void main()
{
	int end_operation=7;
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
		printf("(7) Exit\n");
		
		printf("Please choose an operation:");
		scanf("%d", &operation);
		
		switch(operation)
		{
			case 1:
				printf("Enter the first number:");
				scanf("%f", &first_number);
				printf("Enter the second number:");
				scanf("%f", &second_number);
				float addition = first_number+second_number;
				printf("%f + %f = %f\n\n", first_number, second_number, addition);
				break;
			case 2:
				printf("Enter the first number:");
				scanf("%f", &first_number);
				printf("Enter the second number:");
				scanf("%f", &second_number);
				float subtraction = first_number-second_number;
				printf("%f - %f = %f\n\n", first_number, second_number, subtraction);
				break;
			case 3:
				printf("Enter the first number:");
				scanf("%f", &first_number);
				printf("Enter the second number:");
				scanf("%f", &second_number);
				float multiplication = first_number*second_number;
				printf("%f * %f = %f\n\n", first_number, second_number, multiplication);
				break;
			case 4:
				printf("Enter the first number:");
				scanf("%f", &first_number);
				printf("Enter the second number:");
				scanf("%f", &second_number);
				float devision = first_number/second_number;
				printf("%f / %f = %f\n\n", first_number, second_number, devision);
				break;
			case 5:
				printf("Enter the first number:");
				scanf("%f", &first_number);
				printf("Enter the second number:");
				scanf("%f", &second_number);
				int modulus = (int)first_number % (int)second_number;
				printf("%d %% %d = %d\n\n", (int)first_number, (int)second_number, modulus);
				break;
			case 6:
				printf("Enter in a number to be tested(integers only):");
				scanf("%f", &first_number);
				int i;
				int prime_test, prime_number, prime_number2;
				for(i=2; i < (int)first_number; i++)
				{
					if((int)first_number%i == 0)
					{
						prime_test = 0;
						prime_number = i;
						prime_number2 = first_number/i;
						break;
					}
				}
				switch(prime_test)
				{
					case 0:
						printf("The number is not prime. %d * %d = %d\n\n", prime_number, prime_number2, (int)first_number);
						break;
					default:
						printf("The number is prime\n\n");
						break;
				}
				break;
			case 7:
				printf("Good Bye!");
				break;
			default:
				printf("Invalid input\n\n");
				break;
		}
	}
	while(operation != end_operation);

}
