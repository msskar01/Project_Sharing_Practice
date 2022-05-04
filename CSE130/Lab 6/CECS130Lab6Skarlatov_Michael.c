/*Michael Skarlatov
  Lab 7: Phoen book (with more options)
  Section 2
  Date 2/28/18*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Set up stuct
typedef struct book
{
	char fName[20];
	char lName[20];
	char number[20];
}book;

int addContact( book *, int);
int deleteContact(book *, int);
void showBook(book *, int);
int contactNumber = 0;
int main()
{
	book *pBook;
	pBook = (book*)malloc(sizeof(book));
	int choice, t=1;
	
	do
	{
		printf("\nPhone Book Aplication\n\n");
		printf("1) Add friend\n");
		printf("2) Delete friend\n");
		printf("3) Show phone book\n");
		printf("4) Sort the list alphabetically\n");
		printf("5) Search freind's phone number\n");
		printf("6) Random freind selection\n");
		printf("7) Delete list of freinds\n");
		printf("8) Close\n\n");
					
		printf("What do you want to do? ");
		scanf("%d", &choice);
	
		switch(choice)
		{
			case 1:
				if(pBook == NULL)
				{
					printf("Not enough memory");
				}
				
				pBook = (book*)realloc(pBook, (contactNumber+1)*sizeof(book));
				

				contactNumber++;
				addContact(pBook, contactNumber);

				break;
			case 2:
				deleteContact(pBook, contactNumber);
				contactNumber--;
				break;
			case 3:
				showBook(pBook, contactNumber);
				break;
			case 4:
				
			case 8:
				t = 4;
				printf("\nGood Bye!");
				break;
			default:
				printf("Invalid input");
				break;
		}
	
	}while(t != 4);
}

int addContact(book *pBook, int contactNumber)
{
	printf("\nFirst name: ");
	scanf("%s", pBook[contactNumber-1].fName);
	printf("Last name: ");
	scanf("%s", pBook[contactNumber-1].lName);
	printf("Phone number: ");
	scanf("%s", pBook[contactNumber-1].number);
	printf("\nContact added!!\n\n");
}

int deleteContact(book *pBook, int contactNumber)
{
	char temp_fName[20];
	char temp_lName[20];
	printf("\nFirst name: ");
	scanf("%s", temp_fName);
	printf("Last name: ");
	scanf("%s", temp_lName);
	int i, u, w;
	for(i = 0; i < contactNumber; i++)
	{
		if((strcmp(temp_fName, pBook[i].fName)==0)&&(strcmp(temp_lName, pBook[i].lName)==0))
		{
			for(w=i; w < contactNumber; w++)
			{
				pBook[w]=pBook[w+1];
			}
		break;
		pBook = realloc(pBook, (contactNumber-1)*sizeof(book));
		}
	}
	printf("Record delted from phone book");
	
}

void showBook(book *pBook, int contactNumber)
{
	int i;
	for(i = 0; i < contactNumber; i++)
	{
		printf("\n%d) ", i+1);
		printf("Phone Book Entries:\n\t%s %s\n\tNumber: %s\n", pBook[i].fName, pBook[i].lName, pBook[i].number);
	}
}
