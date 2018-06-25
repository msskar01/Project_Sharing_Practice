/*Michael Skarlatov
  Lab 8: Phone book with files
  Section 2
  Date 3/08/18*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//Set up stuct
typedef struct book
{
	char fName[20];
	char lName[20];
	char number[20];
}book;

FILE *pRead;
FILE *pWrite;

//Declare functions
void addContact(book *, int);
int deleteContact(book *, int);
void showBook(book *, int);
void sortBook(book *, int);
void findNumber(book *, int);
void randomFreind(book *, int);
void deleteAll(book *, int);
void saveNames(book *, int);
void openFile(book *, int);

int contactNumber = 0, random;

//Start of main
int main()
{
	book *pBook;
	pBook = (book*)malloc(sizeof(book));
	int t=1, choice;
	
	//Start of while loop
	do
	{
		srand(time(0));
		printf("\nPhone Book Aplication\n\n");
		printf("1) Add friend\n");
		printf("2) Delete friend\n");
		printf("3) Show phone book\n");
		printf("4) Sort the list alphabetically\n");
		printf("5) Search freind's phone number\n");
		printf("6) Random freind selection\n");
		printf("7) Delete list of freinds\n");
		printf("8) Make contact file\n");
		printf("9) Open contact file\n");
		printf("10) Close\n\n");
					
		printf("What do you want to do? ");
		scanf("%d", &choice);
		
		
		//Start of switch
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
				contactNumber = deleteContact(pBook, contactNumber);
				break;
			case 3:
				showBook(pBook, contactNumber);
				break;
			case 4:
				sortBook(pBook, contactNumber);
				showBook(pBook, contactNumber);
				break;
			case 5:
				findNumber(pBook, contactNumber);
				break;
			case 6:
				random = rand()%contactNumber;
				randomFreind(pBook, random);
				break;
			case 7:
				deleteAll(pBook, contactNumber);
				contactNumber = 0;
				break;
			case 8:
				saveNames(pBook, contactNumber);
				printf("\nContacts saved to file\n");
				break;	
			case 9:
				openFile(pBook, contactNumber);
				break;
			case 10:
				t = 4;
				printf("\nGood Bye!");
				break;
			default:
				printf("Invalid input");
				continue;
				break;
		}
		//End of switch
	}while(t != 4);
	//End of while loop
}
//End of Main

//Add Contact Function
void addContact(book *pBook, int contactNumber)
{
	printf("\nFirst name (only lower case letters please): ");
	scanf("%s", pBook[contactNumber-1].fName);
	printf("Last name (only lower case letter please): ");   
	scanf("%s", pBook[contactNumber-1].lName);
	printf("Phone number: ");
	scanf("%s", pBook[contactNumber-1].number);
	printf("\nContact added!!\n");
}

//Delete Contact Function
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
			for(w = i; w < contactNumber; w++)
			{
				pBook[w]=pBook[w+1];
			}
		pBook = realloc(pBook, (contactNumber-1)*sizeof(book));
		printf("Record delted from phone book\n");
		return (contactNumber-1);
		}
	}
	printf("Could not find contact\n");
	return contactNumber;
}

//Show Book Function
void showBook(book *pBook, int contactNumber)
{
	int i;
	for(i = 0; i < contactNumber; i++)
	{
		printf("\n%d) ", i+1);
		printf("Phone Book Entries:\n\t%s %s\n\tNumber: %s\n", pBook[i].fName, pBook[i].lName, pBook[i].number);
	}
}

//Sort Book Funciton
void sortBook(book *pBook, int contactNumber)
{
	int i, w;
	for(i = 0; i < contactNumber; i++)
	{
		for(w = i+1; w < contactNumber; w++)
		{
			if(strcmp(pBook[i].fName, pBook[w].fName) > 0)
			{
				book temp_Name = pBook[i];
				strcpy(pBook[i].fName, pBook[w].fName);
				strcpy(pBook[i].lName, pBook[w].lName);
				strcpy(pBook[i].number, pBook[w].number);
				strcpy(pBook[w].fName, temp_Name.fName);
				strcpy(pBook[w].lName, temp_Name.lName);
				strcpy(pBook[w].number, temp_Name.number);
			}
		}
	}
}

//Find Number Function
void findNumber(book *pBook, int contactNumber)
{
	char temp_fName[20];
	char temp_lName[20];
	printf("\nFirst name: ");
	scanf("%s", temp_fName);
	printf("Last name: ");
	scanf("%s", temp_lName);
	int i, check;
	for(i = 0; i < contactNumber; i++)
	{
		if((strcmp(temp_fName, pBook[i].fName)==0)&&(strcmp(temp_lName, pBook[i].lName)==0))
		{
			check = 1;
			printf("\n%s %s's number is %s\n", pBook[i].fName, pBook[i].lName, pBook[i].number);
			break;
		}
		check = 0;
	}
	if(check == 0)
	{
		printf("Could not find name\n");
	}
}

//Random Freind Function
void randomFreind(book *pBook, int random)
{
	printf("\nYour random friend is %s %s and their number is %s\n", pBook[random].fName, pBook[random].lName, pBook[random].number);
}

//Delete All Function
void deleteAll(book *pBook, int contactNumber)
{
	int i;
	for(i = 0; i < contactNumber; i++)
	{
		pBook = realloc(pBook, (contactNumber-i)*sizeof(book));
	}
	char *temp_fName = {""};
	char *temp_lName = {""};
	char *temp_number = {""};
	strcpy(pBook[0].fName, temp_fName);
	strcpy(pBook[0].lName, temp_lName);
	strcpy(pBook[0].number, temp_number);
	printf("Everything Deleted\n");
}

//Save Names Function
void saveNames(book *pBook, int contactNumber)
{
	char fileName[20];
	printf("What is the file name?");
	scanf("%s", fileName);	
	pWrite = fopen(("%s.txt", fileName), "a");
	if (pWrite != NULL)
	{
		int i;
		for(i = 0; i < contactNumber; i++)
		{
			fprintf(pWrite, "%s\n%s\n%s\n\n", pBook[i].fName, pBook[i].lName, pBook[i].number);
		}
		fclose(pWrite);
	}
	else
	{
		printf("\nFile not opened\n");
	}
}

//Open Saved Names Function
void openFile(book *pBook, int contactNumber)
{
	int p = 4;
	while(p == 4)
	{
		char fileName[20];
		printf("\nWhat is the name of the file?");
		scanf("%s", fileName);
		pRead = fopen(("%s.txt", fileName), "r");
		if(pRead == NULL)
		{
			printf("\nSorry there is no file with that name\n");
		}
		else
		{
			char fName[20], lName[20], number[20];
			while(!feof(pRead))
			{
				fscanf(pRead, "%s %s %s", fName, lName, number);
				if(!feof(pRead))
				{
					printf("First name: %s\nLast name: %s\nNumber: %s\n", fName, lName, number);
				}
			}
			p = 1;
		}
	}

	fclose(pRead);
}

