// Michael Skarlatov
// Lab 10: 3D Tic Tac Toe
// Section 2
// Date 04/06/18

#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>

using namespace std;

class game
{
	protected:
		string letter1, letter2;
	public:
		int win;
		void setValues(string x, string o)
		{
			x = letter1;
			o = letter2;
		}
		char board[3][3][3];
		bool askToPlay();
};


class DDDgame:public game
{
	friend class game;
	public:
		void viewBoard(char board[3][3][3]);
		void playerMove(char board[3][3][3], string letter1);
		bool askToPlay();
		bool checkwin(string name, string letter1, string letter2, char board[3][3][3]);
		int cpuMove(string letter2, char board[3][3][3]);
};
//Class for 3D


//Start of Main
int main(void)
{
	cout << "The meaning of life is %s" << 42;
	bool play = false;
	int coinFlip = 0, move, number = 0, place;
	string name;
	DDDgame myGame;
	string x = "X", o = "O";
	myGame.setValues(x, o);
	
	cout<<"What is your name?"<<endl;
	cin>>name;
	cout<<"Hello "<<name<<endl;
	
	play = myGame.askToPlay();
	
	srand(time(NULL));
	
	//Start of the game
	while(play == true)
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
					myGame.board[i][z][c] = ' ';
				}
			}
		}
		
		coinFlip = rand()%2;
		cout << "Let's flip a coin to see who goes first. Your heads." << endl;
		
		//Checks to see who is first
		if(coinFlip == 1)
		{
			cout << "Heads, you go first" << endl;	
		}
		else
		{
			cout << "Tails, I go first" << endl;
		}
		
		
		//If player is first they get to choose their letter
		if(coinFlip == 1)
		{
			cout << endl << "Do you want to be X's or O's? " << endl;
			cin >> x;
			myGame.setValues(x, o);
			x = toupper(x[0]);
			if(x[0] == 'X')
			{
				cout << "Great! Then I'll be " << o << endl;
			}
			else if(x[0] == 'O')
			{
				o = 'X';
				cout << "Great! Then I'll be " << o << endl;
			}
			else
			{
				x = "X";
				cout << "Invalid response, you will just be " << x << endl;
			}
		}
		
		
		//Start of moves
		do
		{
			myGame.viewBoard(myGame.board);
			
			//Checks for when game is done 
			if(count == 27)
			{
				break;
			}
			
			//If player turn
			while(coinFlip == 1)
			{
				myGame.playerMove(myGame.board, x);
				count++;
				coinFlip = 0;
			}
			//End of player turn
			
			//CPU turn
			while (coinFlip == 0)
			{
				//Need this because if player takes last move then it will be an infinite loop
				if(count == 27)
				{
					break;
				}
				
				myGame.cpuMove(o, myGame.board);
				coinFlip = 1;
				count++;
			}
			
			myGame.checkwin(name ,x, o, myGame.board);
			
		}while(true); //Try just setting it to true
		
		myGame.checkwin(name, x, o, myGame.board);
		
		if(myGame.win == 1)
		{
			cout << "You won! Good Job!" << endl;
		}
		else if(myGame.win == 2)
		{
			cout << "You lost, sorry." << endl;
		}
		else
		{
			cout << "It's a tie. Better play again." << endl;
		}
		
		myGame.viewBoard(myGame.board);
		
		play = myGame.askToPlay();
	}
	return 0;
}
//End of main

//Player move funciton
void DDDgame::playerMove(char board[3][3][3], string letter1)
{
	do
	{
		int numberBoard = 0, row = 0, column = 0;
		cout << "Put the board number you want to place your " << letter1 << endl;
		cin >> numberBoard;
		cout << "Put the row number you want to place your " << letter1 << endl;
		cin >> row;
		cout << "Put the column number you want to place your " << letter1 << endl;
		cin >> column;
				
		//Checks to see that they used good number
		if(numberBoard < 4 && numberBoard > 0 && row < 4 && row > 0 && column < 4 && column > 0)
		{
			//Checks to see if spot is open
			if(board[numberBoard-1][row-1][column-1] == ' ')
			{
				board[numberBoard-1][row-1][column-1] = letter1[0];
				break;
			}
			else 
			{
				cout <<"That spot is already taken!" << endl;
			}
		}
			else
			{
				cout << "Invalid response" << endl;
		}
	}while(true);
}
	

//CPU's move
int DDDgame::cpuMove(string letter2, char board[3][3][3])
{
	srand(time(NULL));
	
	bool check = false;
	
	do
	{
		int z = (rand()%3), b = (rand()%3), o = (rand()%3);
		if(board[z][b][o] == ' ')
		{
			board[z][b][o] = letter2[0];
			check = true;
		}			
	}
	while(check == false);
}

//Ask to see if the player wants to play
bool DDDgame::askToPlay()
{
	bool invalidResponse = true;
	bool play = false;
	string response;
	
	while(invalidResponse == true)
	{	
		cout<< endl <<"Would you like to start a new game? (y/n)"<<endl;
		cin>>response;
		
		if(response == "y" || response == "Y")
		{
			return true;
		}
		else if(response == "n" || response == "N")
		{
			cout<<"Ok bye!!"<<endl;
			return false;
		}
		else
		{
			cout<<"Invalid response :("<<endl;
		}
	}
}

//Checks/prints out score for win
bool DDDgame::checkwin(string name, string letter1, string letter2, char board[3][3][3])
{
	int playerScore = 0, cpuScore = 0;
	
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
						if(board[i][c][v] == letter1[0])
						{
							playerScore++;
						}
						else if(board[i][c][v] == letter2[0])
						{
							cpuScore++;
						}
					}
				}
				//Checks y axis along the whole thing
				if(c == 0)
				{
					if(board[i][c][v] == board[i][c+1][v] && board[i][c][v] == board[i][c+2][v])
					{
						if(board[i][c][v] == letter1[0])
						{
							playerScore++;
						}
						else if(board[i][c][v] == letter2[0])
						{
							cpuScore++;
						}
					}
				}
				//Checks the z axis along the whole thing
				if(i == 0)
				{
					if(board[i][c][v] == board[i+1][c][v] && board[i][c][v] == board[i+2][c][v])
					{
						if(board[i][c][v] == letter1[0])
						{
							playerScore++;
						}
						else if(board[i][c][v] == letter2[0])
						{
							cpuScore++;
						}
					}
				}
				//Checks top left diagnals on the faces as if the front where facing you
				if(v == 0 && c == 0)
				{
					if(board[i][c][v] == board[i][c+1][v+1] && board[i][c][v] == board[i][c+2][v+2])
					{
						if(board[i][c][v] == letter1[0])
						{
							playerScore++;
						}
						else if(board[i][c][v] == letter2[0])
						{
							cpuScore++;
						}
					}
				}
				//Checks top right diagnals on the faces as if the front where facing you
				if(v == 2 && c == 2)
				{
					if(board[i][c-2][v] == board[i][c-1][v-1] && board[i][c][v-2] == board[i][c-2][v])
					{
						if(board[i][c-2][v] == letter1[0])
						{
							playerScore++;
						}
						else if(board[i][c-2][v] == letter2[0])
						{
							cpuScore++;
						}
					}
				}
				//Checks top diagnols going to the other side of the cube (so line from [0][0][0] to [2][2][0])
				if(i == 0 && c == 0)
				{
					if(board[i][c][v] == board[i+1][c+1][v] && board[i][c][v] == board[i+2][c+2][v])
					{
						if(board[i][c][v] == letter1[0])
						{
							playerScore++;
						}
						else if(board[i][c][v] == letter2[0])
						{
							cpuScore++;
						}
					}
				}
				//Checks bottom diagnols going to the other side of the cube (so line from [0][2][0] to [2][0][0])
				if(i == 2 && c == 0)
				{
					if(board[i][c][v] == board[i-1][c+1][v] && board[i][c][v] == board[i-2][c+2][v])
					{
						if(board[i][c][v] == letter1[0])
						{
							playerScore++;
						}
						else if(board[i][c][v] == letter2[0])
						{
							cpuScore++;
						}
					}
				}
				//Checks diganols from top left front too top right back and all like it
				if(v == 0 && i == 0)
				{
					if(board[i][c][v] == board[i+1][c][v+1] && board[i][c][v] == board[i+2][c][v+2])
					{
						if(board[i][c][v] == letter1[0])
						{
							playerScore++;
						}
						else if(board[i][c][v] == letter2[0])
						{
							cpuScore++;
						}
					}
				}
				//Checks diagnols from top right front too top left back and all like it
				if(v == 2 && i == 0)
				{
					if(board[i][c][v] == board[i+1][c][v-1] && board[i][c][v] == board[i+2][c][v-2])
					{
						if(board[i][c][v] == letter1[0])
						{
							playerScore++;
						}
						else if(board[i][c][v] == letter2[0])
						{
							cpuScore++;
						}
					}
				}
				//Checks all 4 crossing diagnols through the center and corners of the cube
				if(i == 1 && c == 1 && v ==1)
				{
					if(board[i][c][v] == board[i-1][c-1][v-1] && board[i][c][v] == board[i+1][c+1][v+1])
					{
						if(board[i][c][v] == letter1[0])
						{
							playerScore++;
						}
						else if(board[i][c][v] == letter2[0])
						{
							cout << "8" << endl;
							cpuScore++;
						}
					}
					if(board[i][c][v] == board[i-1][c-1][v+1] && board[i][c][v] == board[i+1][c+1][v-1])
					{
						if(board[i][c][v] == letter1[0])
						{
							playerScore++;
						}
						else if(board[i][c][v] == letter2[0])
						{
							cpuScore++;
						}
					}
					if(board[i][c][v] == board[i-1][c+1][v-1] && board[i][c][v] == board[i+1][c-1][v+1])
					{
						if(board[i][c][v] == letter1[0])
						{
							playerScore++;
						}
						else if(board[i][c][v] == letter2[0])
						{
							cpuScore++;
						}
					}
					if(board[i][c][v] == board[i-1][c+1][v+1] && board[i][c][v] == board[i+1][c-1][v-1])
					{
						if(board[i][c][v] == letter1[0])
						{
							playerScore++;
						}
						else if(board[i][c][v] == letter2[0])
						{
							cpuScore++;
						}
					}
				}
			}
		}
	}
	
	if(playerScore > cpuScore)
	{
		cout << endl << name << " " << playerScore << "\t" << "CPU " << cpuScore << endl << endl;
		win = 1;
	}
	else if(cpuScore > playerScore)
	{
		cout << endl << name << " " << playerScore << "\t" << "CPU " << cpuScore << endl << endl;
		win = 2;
	}
	else
	{
		cout << endl << name << " " << playerScore << "\t" << "CPU " << cpuScore << endl << endl;
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
