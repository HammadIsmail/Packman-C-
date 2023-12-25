#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<string>
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
void setcursor(bool visible, DWORD size) {
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}
void play(int lives , int score);
void printmaze();
void erase(int x, int y);
void printPackman(int x, int y);
char getCharAtxy(short int x, short int y);
void gotoxy(int x, int y);
void ghost(int ghostX, int ghostY);
void eraseghost(int ghost1X, int ghost1Y);
void scorexy();
int displayMenu();
void displayInstructions();
void displayGameover(int score);
int main() {
        setcursor(0, 0);

    int choice = 0;
    int lives=3;
    int score=0;
    system("color 0A");

    while (choice != 3) {
        system("CLS");
      int choice=displayMenu();
        if (choice == 1) {
          
			play( lives ,score);
        } else if (choice == 2) {
            displayInstructions();
        }
		else if(choice == 3)
		{
			exit(0);
		}
		 else if (choice > 3) {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

void gotoxy(int x, int y) {
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void scorexy() {
    COORD coordinates;
    coordinates.X = 90;
    coordinates.Y = 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

char getCharAtxy(short int x, short int y) {
    CHAR_INFO ci;
    COORD xy = {0, 0};
    COORD coordBufSize;
    SMALL_RECT rect = {x, y, x, y};
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}

void erase(int x, int y) {
    gotoxy(x, y);
    cout << " ";
}

void eraseghost(int x, int y) {
    gotoxy(x, y);
    cout << " ";
}

void ghost(int ghostX, int ghostY) {
    gotoxy(ghostX, ghostY);
    cout << "G";
}



void printPackman(int x, int y) {
    gotoxy(x, y);
    cout << "P";
}

int displayMenu() {
    int choice=0;
    cout << "Welcome to the Pac-Man Game!" << endl;
    cout << "1. Start Game" << endl;
    cout << "2. Instructions" << endl;
    cout << "3. Quit" << endl;
    cout << "Enter your choice: ";
    cin >> choice; 
    return choice;
}

void displayInstructions() {
    system("CLS");
    cout << "Instructions:" << endl;
    cout << "1. Use arrow keys to move Pac-Man (P) on the maze." << endl;
    cout << "2. Avoid ghosts (G) moving on the screen." << endl;
    cout << "3. Collect dots (.) for points." << endl;
    cout << "4. The game ends if Pac-Man collides with a ghost." << endl;
    cout << "5. Press ESC to quit the game." << endl;
    cout << "Press any key to go back to the menu." << endl;
    _getch();  // Use _getch to wait for a key press
}

void printmaze() {
 fstream fs;
    string line;

    fs.open("maze.txt", ios::in);
    if (!fs.is_open()) {
        cout << "Error opening maze.txt file." << endl;
        return;
    }

    while (!fs.eof()) {
        getline(fs, line);
        cout << line << endl;
    }

    fs.close();
}

void displayGameover(int score)
{
	char again='y';
    int highScore=0;
    system("cls");
    cout << " |-----------Game Over-------------|" << endl;
   
    
    fstream fs;
    // Read the score
    fs.open("score.txt", ios::in);
     fs>>highScore;
    fs.close();
    cout << "Your Score is = " << score << endl;
    cout << "Your HighScore is = " << highScore << endl;
    if (score > highScore)
    {
        fstream fs;
        // update the score
    fs.open("score.txt", ios::out);
     fs<<score;
    fs.close();
    // write read again
     fs.open("score.txt", ios::in);
     fs>>highScore;
    fs.close();
    cout << "Your New HighScore is = " << highScore << endl;

    }
    cout << "Want to play again [Y/N] =";
    cin>>again;
    if(again=='N' || again=='n')
    {
    	exit(0);
	}
	else
	{
		main();
	}
}

void play(int lives , int score)
{		const int max=6;
	        int packmanX = 4, packmanY = 4;
            int ghostX[max]={5,40,20,3,35,25};
            int ghostY[max]={5,1,7,7,3,11};
            int i=0,j=3;
              system("CLS");
            printmaze();
            bool gamingTrue = true;
            scorexy();
            cout << "Score = " << score << "    Lives = " << lives << endl;

            while (gamingTrue) {
   
                // To move Right
                if (GetAsyncKeyState(VK_RIGHT)) {
                    char nextLocation = getCharAtxy(packmanX + 1, packmanY);
                    if (nextLocation == ' ' || nextLocation == '.') {
                        erase(packmanX, packmanY);
                        packmanX++;
                        printPackman(packmanX, packmanY);

                        if (nextLocation == '.') {
                            score++;
                            scorexy();
                            cout << "Score = " << score << "    Lives = " << lives << endl;
                        }
                    }
                }
               // To move LEft 
              if(GetAsyncKeyState(VK_LEFT))
	{
			char nextLocation = getCharAtxy(packmanX-1,packmanY);
		if(nextLocation == ' ' || nextLocation =='.')
		{
			erase(packmanX,packmanY);
			packmanX--;
			printPackman(packmanX,packmanY);
				if(nextLocation == '.')
			{
				score++;
					scorexy();
			cout<<"Score = "<<score;	
			}
		
		}
	}
    // To move up
		 if(GetAsyncKeyState(VK_UP))
	{
		char nextLocation = getCharAtxy(packmanX,packmanY-1);
		if(nextLocation == ' ' || nextLocation =='.')
		{
			erase(packmanX,packmanY);
			packmanY--;
			printPackman(packmanX,packmanY);
				if(nextLocation == '.')
			{
				score++;
					scorexy();
			cout<<"Score = "<<score;	
			}
		}
	}
    // To move Down
		 if(GetAsyncKeyState(VK_DOWN))
	{
	char nextLocation = getCharAtxy(packmanX,packmanY+1);
		if(nextLocation == ' ' || nextLocation =='.')
		{
			erase(packmanX,packmanY);
			packmanY++;
			printPackman(packmanX,packmanY);
				if(nextLocation == '.')
			{
				score++;
					scorexy();
			cout<<"Score = "<<score;	
			}
		
		}
	}



	// Code for the movement of ghosts..........

// For Y-Axis ghosts
char nextLocation = getCharAtxy(ghostX[i],ghostY[i]+1);
 			if(nextLocation == 'P')
				{
					while(lives!=1)
					{
						lives=lives-1;
						play( lives ,score);
 
					}
							displayGameover(score);
                          
					gamingTrue=false;	
			
			}
	else if(nextLocation == '#')
	{
		eraseghost(ghostX[i],ghostY[i]);
		ghostY[i]=2;
	} 
    ////////////////
		eraseghost(ghostX[i],ghostY[i]);
		ghostY[i]++;
		ghost(ghostX[i],ghostY[i]); 
        i=(i+1)%3;
        

// for X-axis ghosts 
nextLocation = getCharAtxy(ghostX[j]+1,ghostY[j]);
 			if(nextLocation == 'P')
				{
					while(lives!=1)
					{
						lives=lives-1;
						play( lives ,score);

					}
							displayGameover(score);
                          
					gamingTrue=false;	
			
			} 
			
    	if(nextLocation == '#')
	{
		eraseghost(ghostX[j],ghostY[j]);
		ghostX[j]=2;
	} 
		eraseghost(ghostX[j],ghostY[j]);
		ghostX[j]++;
		ghost(ghostX[j],ghostY[j]); 
        j+=1;
		if (j==6)
		{
			j=3;
		}  	
         if (score == 70)
    {
        system("cls");
        char r='y';
        cout<<"You Won!!!!"<<endl;
        cout<<"Want to Play again (Y/N) :";
        cin>>r;
        if (r=='y' || r=='Y')
        {
            score=0;
            lives=0;
            play(lives,score);
        }   
        gamingTrue=false;
    }
// to exit the game 
     if (GetAsyncKeyState(VK_ESCAPE)) {
                    gamingTrue = false;
                }
                        Sleep(100);
            }
}
