// Michael Skarlatov, Corey MacGeorge
// Lab Fianl: 3D Tic Tac Toe played 10 times against eachothers move classes
// Section 2
// Date 04/24/18

#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>

using namespace std;

class corey
{
	protected:
		char letter2;
	public:
		int player2Score;
		void setValue(char o)
		{
			letter2 = o;
		}
};

class michael: public corey
{	
	protected:
		char letter1;
	public:
		int player1Score;
		void setValue(char x)
		{
			letter1 = x;
		}
};

//DDDgame inherits from both michael and corey class. The big thing it inherits is the player1Score and player2Score
class DDDgame:public michael
{
	public:
		int win;
		void michaelMove(char board[3][3][3], char letter1, char letter2);
		void viewBoard(char board[3][3][3]);
		void checkwin(char letter1, char letter2, char board[3][3][3]);
		void coreyMove(char letter2, char board[3][3][3]);
};
//Class for 3D


//Start of Main
int main(void)
{
	system("pause");
	char board[3][3][3];
	int coinFlip = 0, rounds = 0, michaelScore = 0, coreyScore = 0, tie = 0;
	DDDgame myGame;
	char x = 'X';
	char o = 'O';
	
	srand(time(NULL));
	
	//Start of the game
	while(rounds < 10)
	{
		system("CLS");
		int count = 0;
		
		//Sets board with blank values
		for(int i = 0; i < 3; i++)
		{
			for(int z = 0; z < 3; z++)
			{
				for(int c = 0; c < 3; c++)
				{
					board[i][z][c] = ' ';
				}
			}
		}
		
		coinFlip = rand()%2;
		
		if(coinFlip == 1)
		{
			x = 'X';
			o = 'O';
		}
		else
		{
			x = 'O';
			o = 'X';
		}
		
		//Start of moves
		do
		{
			myGame.viewBoard(board);
			
			if(count == 27)
			{
				break;
			}
			
			//If player1 (Michael) turn
			while(coinFlip == 1)
			{
				myGame.michaelMove(board, x, o);
				coinFlip = 0;
				count++;
			}
			//End of player1 turn
			
			//player2 (Corey) turn
			while (coinFlip == 0)
			{
				if(count == 27)
				{
					break;
				}
				myGame.coreyMove(o, board);
				coinFlip = 1;
				count++;
			}
			//End of player2 turn
			
			myGame.checkwin(x, o, board);
			cout << endl << "Michael " << x << " " << myGame.player1Score << "\t" << "Corey " << o << " " << myGame.player2Score << endl << endl;
		}while(true); //Try just setting it to true
		
		myGame.checkwin(x, o, board);
		
		if(myGame.win == 1)
		{
			michaelScore++;
			cout << "Michael won! Good job!" << endl;
		}
		else if(myGame.win == 2)
		{
			coreyScore++;
			cout << "Coery won! Good job!." << endl;
		}
		else
		{
			tie++;
			cout << "It's a tie. Better play again." << endl;
		}
		
		myGame.viewBoard(board);		
		rounds++;
	}
	cout << "Michael: " << michaelScore << " " << "Corey: " << coreyScore << " Tie: " << tie << endl;
	if(michaelScore > coreyScore)
	{
		cout << "Michael wins!" << endl;
	}
	else if(coreyScore > michaelScore)
	{
		cout << "Corey wins!" << endl;
	}
	else
	{
		cout << "You both tied." << endl;
	}
	return 0;
}
//End of main

//Michael's move, this checks to see if a three in a row is possible	
void DDDgame::michaelMove(char board[3][3][3], char letter1, char letter2)
{
	int tempScore = player1Score;
	for(int i = 0; i < 3; i++)
	{
		for(int c = 0; c < 3; c++)
		{
			for(int v = 0; v < 3; v++)
			{
				if(board[i][c][v] == ' ')
				{
					board[i][c][v] = letter1;
					checkwin(letter1, letter2, board);
					if(tempScore < player1Score)
					{
						return;
					}
					board[i][c][v] = ' ';
				}			
			}
		}
	}
	srand(time(NULL));
	
	bool check = false;
	
	do
	{
		int i = (rand()%3), c = (rand()%3), v = (rand()%3);
		if(board[i][c][v] == ' ')
		{
			board[i][c][v] = letter1;
			check = true;
		}			
	}while(check == false);
}

//Corey's move, this is just random placement
void DDDgame::coreyMove(char letter2, char board[3][3][3])
{
	srand(time(NULL));
	
	bool check = false;
	
	do
	{
		int z = (rand()%3), b = (rand()%3), o = (rand()%3);
		if(board[z][b][o] == ' ')
		{
			board[z][b][o] = letter2;
			check = true;
		}			
	}
	while(check == false);
}


//Checks/prints out score for win
void DDDgame::checkwin(char letter1, char letter2, char board[3][3][3])
{
	player1Score = 0;
	player2Score = 0;
	
	for(int i = 0; i < 3; i++)
	{
		for(int c = 0; c < 3; c++)
		{
			for(int v = 0; v < 3; v++)
			{
				//Checks x axis along the whole thing
				if(v == 0)
				{
					if(board[i][c][v] == board[i][c][v+1] && board[i][c][v] == board[i][c][v+2])
					{
						if(board[i][c][v] == letter1)
						{
							player1Score++;
						}
						else if(board[i][c][v] == letter2)
						{
							player2Score++;
						}
					}
				}
				//Checks y axis along the whole thing
				if(c == 0)
				{
					if(board[i][c][v] == board[i][c+1][v] && board[i][c][v] == board[i][c+2][v])
					{
						if(board[i][c][v] == letter1)
						{
							player1Score++;
						}
						else if(board[i][c][v] == letter2)
						{
							player2Score++;
						}
					}
				}
				//Checks the z axis along the whole thing
				if(i == 0)
				{
					if(board[i][c][v] == board[i+1][c][v] && board[i][c][v] == board[i+2][c][v])
					{
						if(board[i][c][v] == letter1)
						{
							player1Score++;
						}
						else if(board[i][c][v] == letter2)
						{
							player2Score++;
						}
					}
				}
				//Checks top left diagnals on the faces as if the front where facing you
				if(v == 0 && c == 0)
				{
					if(board[i][c][v] == board[i][c+1][v+1] && board[i][c][v] == board[i][c+2][v+2])
					{
						if(board[i][c][v] == letter1)
						{
							player1Score++;
						}
						else if(board[i][c][v] == letter2)
						{
							player2Score++;
						}
					}
				}
				//Checks top right diagnals on the faces as if the front where facing you
				if(v == 2 && c == 2)
				{
					if(board[i][c-2][v] == board[i][c-1][v-1] && board[i][c][v-2] == board[i][c-2][v])
					{
						if(board[i][c-2][v] == letter1)
						{
							player1Score++;
						}
						else if(board[i][c-2][v] == letter2)
						{
							player2Score++;
						}
					}
				}
				//Checks top diagnols going to the other side of the cube (so line from [0][0][0] to [2][2][0])
				if(i == 0 && c == 0)
				{
					if(board[i][c][v] == board[i+1][c+1][v] && board[i][c][v] == board[i+2][c+2][v])
					{
						if(board[i][c][v] == letter1)
						{
							player1Score++;
						}
						else if(board[i][c][v] == letter2)
						{
							player2Score++;
						}
					}
				}
				//Checks bottom diagnols going to the other side of the cube (so line from [0][2][0] to [2][0][0])
				if(i == 2 && c == 0)
				{
					if(board[i][c][v] == board[i-1][c+1][v] && board[i][c][v] == board[i-2][c+2][v])
					{
						if(board[i][c][v] == letter1)
						{
							player1Score++;
						}
						else if(board[i][c][v] == letter2)
						{
							player2Score++;
						}
					}
				}
				//Checks diganols from top left front too top right back and all like it
				if(v == 0 && i == 0)
				{
					if(board[i][c][v] == board[i+1][c][v+1] && board[i][c][v] == board[i+2][c][v+2])
					{
						if(board[i][c][v] == letter1)
						{
							player1Score++;
						}
						else if(board[i][c][v] == letter2)
						{
							player2Score++;
						}
					}
				}
				//Checks diagnols from top right front too top left back and all like it
				if(v == 2 && i == 0)
				{
					if(board[i][c][v] == board[i+1][c][v-1] && board[i][c][v] == board[i+2][c][v-2])
					{
						if(board[i][c][v] == letter1)
						{
							player1Score++;
						}
						else if(board[i][c][v] == letter2)
						{
							player2Score++;
						}
					}
				}
				//Checks all 4 crossing diagnols through the center and corners of the cube
				if(i == 1 && c == 1 && v ==1)
				{
					if(board[i][c][v] == board[i-1][c-1][v-1] && board[i][c][v] == board[i+1][c+1][v+1])
					{
						if(board[i][c][v] == letter1)
						{
							player1Score++;
						}
						else if(board[i][c][v] == letter2)
						{
							player2Score++;
						}
					}
					if(board[i][c][v] == board[i-1][c-1][v+1] && board[i][c][v] == board[i+1][c+1][v-1])
					{
						if(board[i][c][v] == letter1)
						{
							player1Score++;
						}
						else if(board[i][c][v] == letter2)
						{
							player2Score++;
						}
					}
					if(board[i][c][v] == board[i-1][c+1][v-1] && board[i][c][v] == board[i+1][c-1][v+1])
					{
						if(board[i][c][v] == letter1)
						{
							player1Score++;
						}
						else if(board[i][c][v] == letter2)
						{
							player2Score++;
						}
					}
					if(board[i][c][v] == board[i-1][c+1][v+1] && board[i][c][v] == board[i+1][c-1][v-1])
					{
						if(board[i][c][v] == letter1)
						{
							player1Score++;
						}
						else if(board[i][c][v] == letter2)
						{
							player2Score++;
						}
					}
				}
			}
		}
	}
	
	if(player1Score > player2Score)
	{
		win = 1;
	}
	else if(player2Score > player1Score)
	{
		win = 2;
	}
	else
	{
		win = 3;
	}
}



//Function to show the board
void DDDgame::viewBoard(char board[3][3][3])
{
	cout << endl;
	cout << "\tBoard\t     1     \t     2     \t     3     " << endl;
	cout << "\tColumns\t 1   2   3 \t 1   2   3 \t 1   2   3 " << endl;
	cout << endl;
	cout << "\t\t   |   |   \t   |   |   \t   |   |   "<<endl;
	cout << "\t1\t " << board[0][0][0] << " |" << " " << board[0][0][1] << " |" << " " << board[0][0][2] << "\t " << board[1][0][0] << " |" << " " << board[1][0][1] << " |" << " " << board[1][0][2] << "\t " << board[2][0][0] << " |" << " " << board[2][0][1] << " |" << " " << board[2][0][2] << endl;
	cout << "\t\t___|___|___\t___|___|___\t___|___|___"<<endl;
	cout << "\t\t   |   |   \t   |   |   \t   |   |   "<<endl;
	cout << "Rows\t2\t " << board[0][1][0] << " |" << " " << board[0][1][1] << " |" << " " << board[0][1][2] << "\t " << board[1][1][0] << " |" << " " << board[1][1][1] << " |" << " " << board[1][1][2] << "\t " << board[2][1][0] << " |" << " " << board[2][1][1] << " |" << " " << board[2][1][2] << endl;
	cout << "\t\t___|___|___\t___|___|___\t___|___|___"<<endl;
	cout << "\t\t   |   |   \t   |   |   \t   |   |   "<<endl;
	cout << "\t3\t " << board[0][2][0] << " |" << " " << board[0][2][1] << " |" << " " << board[0][2][2] << "\t " << board[1][2][0] << " |" << " " << board[1][2][1] << " |" << " " << board[1][2][2] << "\t " << board[2][2][0] << " |" << " " << board[2][2][1] << " |" << " " << board[2][2][2] << endl;
	cout << "\t\t   |   |   \t   |   |   \t   |   |   "<<endl;	
}
