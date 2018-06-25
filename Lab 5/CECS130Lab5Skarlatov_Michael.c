//Michael Skarlatov
//Lab 5: Story generator
//Section 2
//Date 2/15/18



#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	//set up the random generator
	srand(time(0));
	
	//set up variables
	char *story_setting[] = {"through a forest", "through a castle", "through a haunted city", "through a graveyard"};
	char *story_object[] = {"book", "ring", "bag"};
	char *story_monster[] = {"skeloton", "dragon", "big cat"};
	char *story_direction[] = {"left", "right"};
	char *story_weapon[] = {"sword", "bow", "mace"};
	char name[20];
	char age[20];
	char color[20];
	char monster[20];
	char object[20];
	int coins = rand()%20;
	int exp = rand()%2000;
	
	//gather personal info
	printf("What is your name?\n");
	scanf("%s", name);
	printf("What is your age?\n");
	scanf("%s", age);
	printf("What is your favorite color?\n");
	scanf("%s", color);
	
	//print out the story
	printf("Hello %s and welcome to your adventure.\n", name);
	printf("You are wlaking %s when you are attacked by a %s.\n", story_setting[rand()%4], story_monster[rand()%3]);
	printf("You dive to the %s to avoid being attacked and drop your %s %s\n", story_direction[rand()%2], color, story_object[rand()%3]);
	printf("In all of your %s years of living you have never seen such a fierce monster, and so, you pull out your %s and perpare for battle.\n", age, story_weapon[rand()%3]);
	printf("After many close calls, and many near death moments, you finally slay the monster and retreive your dropped item.\n");
	printf("You gain %d droped gold coins and %d exp from the monster.\n", coins, exp);
	printf("And so you live on to adventure another day.");

	return 0;
}
