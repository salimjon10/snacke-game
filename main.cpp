#include <iostream>
#include <conio.h>
#include <cstdlib>

using namespace std;

bool gameOver;
const int width = 25;
const int height = 15;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    system("cls");

    //top
    for(int i=0; i<width + 1; ++i)
    {
        cout << "#";
    }
    cout << endl;


    //left-right
    for(int i=0; i<height; ++i)
    {
        for(int j=0; j<width; ++j)
        {
            if(j==0 || j == width -1)
            {
                cout << "#";
            }
            if(i == y && j == x)
            {
                cout << "@";
            }
            else if(i == fruitY && j == fruitX)
            {
                cout << "$";
            }
            else
            {
                bool print = false;

                for(int k = 0; k < nTail; k++)
                {
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        print = true;
                        cout << "o";
                    }
                }
                if(!print)
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }


    //down
    for(int i=0; i<width + 1; ++i)
    {
        cout << "#";
    }
    cout << endl;

    cout << "\nScore: " << score << "$" << endl;
}

void Input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }

}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for(int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }


    //Столкновение со стеной
    if(x > width - 2 || x < 0 || y > height -1 || y < 0 )
    {
        gameOver = true;
    }



    //Пройти через стену
    /*
    if(x >= width - 1)
    {
        x = 0;
    }
    else if(x < 0)
    {
        x = width - 2;
    }

    if(y >= height)
    {
        y = 0;
    }
    else if(y < 0)
    {
        y = height - 1;
    }
    */

    for(int i = 0; i < nTail; i++)
    {
        if(tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
        }
    }

    if(x== fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }

}


int main()
{

    system("color 02");
    Setup();
    while(!gameOver)
    {
        Draw();
        Input();
        Logic();
    }

    if(gameOver)
    {
        system("cls");
        cout << "Your score: " << score << endl;
        cout << " " << endl;
        system("color 04");
        cout << " -------------" << endl;
        cout << " |" << " GAME OVER " << "|" << endl;
        cout << " -------------" << endl;
        cout << "\n\n\nPress 'Enter' to exit\n" << endl;
        cin.get();
        system("cls");
    }

    return 0;
}

