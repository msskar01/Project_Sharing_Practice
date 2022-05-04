// Michael Skarlatov
// Lab 9: Tic Tac Toe
// Section 2
// Date 03/30/18

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class game
{
	public:
		int win;
		void viewboard(char board[]);
		bool askToPlay();
		bool checkwin(char letter1, char letter2, char board[]);
		int cpuMove(char letter2, char board[]);
		
};			

int main(void)
 {
	bool play = false;
	int i = 0;
	int player1 = 1, cpu = 0, coinFlip = 0, move, number = 0, place;
	char letter1 = 'X';
	char letter2 = 'O';
	string name;
	char answer;
	game myBoard;
	
	cout<<"What is your name?"<<endl;
	cin>>name;
	cout<<"Hello "<<name<<endl;
	
	play = myBoard.askToPlay();
	
	srand(time(NULL));
	
	while(play == true)
	{
		int count = 0;
		char board[9] = {'1','2','3','4','5','6','7','8','9'};
		coinFlip = rand()%2;
		cout << coinFlip;	
	
		if(coinFlip == 1)
		{
			move = player1;
			cout << endl << "You go first!" << endl;
		}
		else if(coinFlip == 0)
		{
			move = cpu;
			cout << endl << "I go first!" << endl;
		}
		else
		{
			cout << "Error!";
			return 0;
		}
		
		if(move == player1)
		{
			cout << endl << "Do you want to be X's or O's? " << endl;
			cin >> letter1;
			letter1 = toupper(letter1);
			if(letter1 == 'X')
			{
				cout << "Great! Then I'll be " << letter2 << endl;
			}
			else if(letter1 == 'O')
			{
				letter2 = 'X';
				cout << "Great! Then I'll be " << letter2 << endl;
			}
			else
			{
				cout << "Invalid response, you will just be " << letter1 << endl;
			}
		}
	
		do
		{	
	
			myBoard.viewboard(board);
			
			if(count == 9)
			{
				break;
			}
			
		
			while(coinFlip == 1)
			{		
				i=0;
				do
				{
					cout << "Where would you like to place your " << letter1 <<"?" << endl;			
					cin >> place;
					if(board[place-1] == (place+48))
					{
						i=1;
					}
					else 
					{
						cout <<"That spot is already taken!" << endl;
					}
				}while(i == 0);
				//Checks if the spot is taken	
	
				if(place == 1)
				{
					board[0] = letter1;
				}
				else if(place == 2)
				{
					board[1] = letter1;
				}
				else if(place == 3)
				{
					board[2] = letter1;
				}
				else if(place == 4)
				{
					board[3] = letter1;
				}
				else if(place == 5)
				{
					board[4] = letter1;
				}
				else if(place == 6)
				{
					board[5] = letter1;
				}
				else if(place == 7)
				{
					board[6] = letter1;
				}
				else if(place == 8)
				{
					board[7] = letter1;
				}															
				else if(place == 9)
				{
					board[8] = letter1;
				}
				else
				{
					cout << "Error";
					return 0;
				}
				count++;
				coinFlip = 0;
			}
		
			while (coinFlip == 0)
			{
		
				if(count == 9)
				{
					cout << "It's a draw!";
					break;
				}
		
				myBoard.cpuMove(letter2, board);
				coinFlip = 1;
				count++;
			}
		}while(!myBoard.checkwin(letter1, letter2, board));
		
		myBoard.viewboard(board);
		
		if(myBoard.win == 1)
		{
			cout << "You won! Good Job!" << endl;
		}
		else if(myBoard.win == 2)
		{
			cout << "You lost. Sorry." << endl;
		}
		
		play = myBoard.askToPlay();
		
	}
	
	return 0;
}

void game::viewboard(char board[])
{
	cout << endl << endl << " " << board[0] << " |" << " " << board[1] << " |" << " " << board[2] << endl;
	cout << "___|___|___"<<endl;
	cout << "   |   |   "<<endl;
	cout << " " << board[3] << " |" << " " << board[4] << " |" << " " << board[5] << endl;
	cout << "___|___|___"<<endl;
	cout << "   |   |   "<<endl;
	cout << " " << board[6] << " |" << " " << board[7] << " |" << " " << board[8] << endl;
	cout << "   |   |   "<<endl;	
}


bool game::checkwin(char letter1, char letter2, char board[])
{			
	if(board[0] == letter1 && board[3] == letter1 && board[6] == letter1)
	{
		win = 1;
		return true;
	}
	else if(board[1] == letter1 && board[4] == letter1 && board[7] == letter1)
	{
		win = 1;
		return true;
	}
	else if(board[2] == letter1 && board[5] == letter1 && board[8] == letter1)
	{
		win = 1;
		return true;
	}
	else if(board[0] == letter1 && board[1] == letter1 && board[2] == letter1)
	{
		win = 1;
		return true;
	}
	else if(board[3] == letter1 && board[4] == letter1 && board[5] == letter1) 
	{
		win = 1;
		return true;
	}
	else if(board[6] == letter1 && board[7] == letter1 && board[8] == letter1)
	{
		win = 1;
		return true;
	}
	else if(board[0] == letter1 && board[4] == letter1 && board[8] == letter1)
	{
		win = 1;
		return true;
	}
	else if(board[2] == letter1 && board[4] == letter1 && board[6] == letter1)
	{
		win = 1;
		return true;
	}
	else if(board[0]==letter2 && board[3]==letter2 && board[6]==letter2)
	{
		win = 2;
		return true;
	}
	else if(board[1]==letter2 && board[4]==letter2 && board[7]==letter2)
	{
		win = 2;
		return true;
	}
	else if(board[2]==letter2 && board[5]==letter2 && board[8]==letter2)
	{
		win = 2;
		return true;
	}
	else if(board[0]==letter2 && board[1]==letter2 && board[2]==letter2)
	{
		win = 2;
		return true;
	}
	else if(board[3]==letter2 && board[4]==letter2 && board[5]==letter2)
	{
		win = 2;
		return true;
	}
	else if(board[6]==letter2 && board[7]==letter2 && board[8]==letter2)
	{
		win = 2;
		return true;
	}
	else if(board[0]==letter2 && board[4]==letter2 && board[8]==letter2)
	{
		win = 2;
		return true;
	}
	else if(board[2]==letter2 && board[4]==letter2 && board[6]==letter2)	
	{
		win = 2;
		return true;
	}
	return false;
}

int game::cpuMove(char letter2, char board[])
{
	
	srand(time(NULL));
	
	bool check = false;
	int z = 0;
	char b;
	
	do{
		z = (rand()%9);
		b = (z+49);
		if(board[z] == b){
			board[z] = letter2;
			check = true;
		}			
	}
	while(check == false);
}

bool game::askToPlay()
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
