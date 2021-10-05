#include <iostream>
#include<ctime>
#include<string>
#include <conio.h>
#include <Windows.h>
using namespace std;
//----------------properties------------------------//
enum direction{Top=1,Down,Right,Left };
struct map { int hight, width, fruitx, fruity; };
struct snake { int headx, heady, tail_n, tail_x[50], tail_y[50]; direction dir; };
struct player { int score; string name; bool lose; };
//-------------------------------------------------//
map map1; player player1; snake snake1;
void name(string x)
{
	cout << "****************************************" << endl;
	cout << "     Welcome To Snake Game" << endl;
	cout << "****************************************" << endl;
	cout << "Enter Your Name : ";
	cin >> player1.name;
}
void shift_r(int arr[], int size)
{
	for (int i = size - 2; i >= 0; i--)
	{
		arr[i + 1] = arr[i];
	}
}
void generate_fruit()
{
	srand(time(NULL));
	map1.fruitx = rand() % (map1.width - 2) + 1;
	map1.fruity = rand() % (map1.hight - 2) + 1;
}
void setup()
{
	map1.width = 40;
	map1.hight = 20;
	generate_fruit();
	//------------------------//
	snake1.heady = map1.hight / 2;
	snake1.headx = map1.width / 2;
	snake1.tail_n = 0;
	//-----------------------//
	player1.score = 0;
	player1.lose = false;
}
void draw()
{
	system("cls");
	for (int i = 0; i < map1.hight; i++)
	{
		for (int j = 0; j < map1.width; j++)
		{
			if (i == 0 || i == map1.hight - 1) cout << "*";
			else if (j == 0 || j == map1.width - 1)cout << "*";
			else if (i == snake1.heady && j == snake1.headx)cout << "0";
			else if (i == map1.fruity && j == map1.fruitx)cout << "$";
			else{
				bool printed = false;
				for (int z = 0; z < snake1.tail_n; z++)
				{
					if (snake1.tail_x[z] == j && snake1.tail_y[z] == i)
					{
						cout << "o";
						printed = true;
						break;
					}
				}
				if(!printed)cout << " ";
			}
		}
		cout << endl;
	}
	cout << player1.name << " Score : " << player1.score << endl;
	cout << "Game Play created By : Fathy Tamer" << endl;
}
void input()
{
	if (_kbhit()) {
		char c = _getch();
		switch (c)
		{
		case 'w':snake1.dir = Top; break;
		case 's':snake1.dir = Down; break;
		case 'a':snake1.dir = Left; break;
		case 'd':snake1.dir = Right; break;
		case 'x': exit(0);
		}
	}
}
void move()
{
	shift_r(snake1.tail_x, 50);
	shift_r(snake1.tail_y, 50);
	snake1.tail_x[0] = snake1.headx;
	snake1.tail_y[0] = snake1.heady;
	switch (snake1.dir)
	{
	case Top:snake1.heady--; break;
	case Down:snake1.heady++; break;
	case Right:snake1.headx++; break;
	case Left:snake1.headx--; break;
	}
	if (snake1.heady >= map1.hight || snake1.heady <= 0 || snake1.headx >= map1.width || snake1.headx <= 0)
	{
		player1.lose = true;
	}
	if (snake1.headx == map1.fruitx && snake1.heady == map1.fruity)
	{
		generate_fruit();
		player1.score += 1;
		snake1.tail_n++;
	}
}
int main()
{
	system("color 02");
	string x;
	name(x);
	setup();
	while (!player1.lose)
	{
		draw();
		input();
		move();
		Sleep(50);
		

	}
	system("Pasue");
	return 0;
}