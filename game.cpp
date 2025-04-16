#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameover = false;
const int vidth = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int xvostX[100], xvostY[100];
int xvostscore;
enum direction { stop = 0, left1, right2, up, dovn };
direction dir;

void setup() {
	dir = stop;
	x = vidth / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % vidth;
	fruitY = rand() % height;
	score = 0;
}

void drav_map() {
	system("cls");
	for (int i = 0; i < vidth + 1; i++)
		cout << "#";
	cout << endl; //верх граничы

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < vidth; j++) {
			if (j == 0 || j == vidth - 1)
			cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "f";
			else {
				bool print = false;
				for (int k = 0; k < xvostscore; k++) {
					if (xvostX[k] == j && xvostY[k] == i) {
						print = true;
						cout << "o";
					}
				}
				if (!print)
				cout << " ";
			}
			
}
		cout << endl;
		
	}

	for (int i = 0; i < vidth + 1; i++)
		cout << "#";
	cout << endl; // вниз граничы
	cout << "score: " << score << endl;
}
void input_user() {
	if (_kbhit()) {
		switch (_getch ())
		{
		case 'j':
			dir = left1;
			break;
		case 'l':
			dir = right2;
			x++;
			break;
		case 'i':
			dir = up;
			y--;
			break;
		case 'k':
			dir = dovn;
			y++;
			break;
		case 'x':
			gameover = true;
			break;
		}
	}
}

void logic_game() {
	int prevX = xvostX[0];
	int prevY = xvostY[0];
	int prev2X, prev2Y;
	xvostX[0] = x;
	xvostY[0] = y;
	for (int i = 1; i < xvostscore; i++) {
		prev2X = xvostX[i];
		prev2Y = xvostY[i];
		xvostX[i] = prevX;
		xvostY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case left1:
		x--;
		break;
	case right2:
		x++;
		break;
	case up:
		y--;
		break;
	case dovn:
		y++;
		break;
	}

	//if (x > vidth || x < 0 || y > height || y < 0)
		//gameover = true;
	if (x >= vidth)
		x = 0;
	else if (x < 0)
		x = vidth - 2;
	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;
	for (int i = 0; i < xvostscore; i++) {
		if (xvostX[i] == x && xvostY[i] == y)
			gameover = true;
	}

	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % height;
		fruitY = rand() % vidth;
		xvostscore++;
	}
}

int main() {
	setup();
	while (!gameover) {
		drav_map();
		input_user();
		logic_game();
		Sleep(300);
	}


	return 0;
}