// Snake.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"//for arrow key input
#include "vector" //for snake tail
#include "iostream" 
#include "thread"  //required to make threads
#include "windows.h"//for sleep function
#include "Snake.h"
#include "utility" //required for std::pair
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define MAX_LENGTH 40
#define MAX_HEIGHT 18
char map[19][39];
Snake s;
int refresh_rate = 200; //200
int food_r; //row location of food
int food_c; //col location of food
int score = 0;
void getInput()
{
	int c = 0;
	while (true)
	{
		c = 0;

		switch ((c = _getch()))
		{
		case KEY_UP:
			s.y = -1;
			s.x = 0;
			break;
		case KEY_DOWN:
			s.y = 1;
			s.x = 0;
			break;
		case KEY_LEFT:
			s.x = -1;
			s.y = 0;
			break;
		case KEY_RIGHT:
			s.x = 1;
			s.y = 0;
			break;
		default:
			// not arrow
			break;
		}

	}
}
void createMap()
{
	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_LENGTH; j++)
		{
			map[i][j] = '*';
		}
	}
}
void displayMap()
{
	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_LENGTH; j++)
		{
			std::cout << map[i][j];
		}
		std::cout << '\n';
	}
}
void generateFood()
{
	food_r = rand() % 18;
	food_c = rand() % 40;
}
void moveHead()
{
	s.head_x += s.x;
	s.head_y += s.y;
	s.tail[s.tail.size() - 1] = std::make_pair(s.head_y, s.head_x);
}
void editMap()
{
	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_LENGTH; j++)
		{

			for (int k = 0; k < s.tail.size(); k++)
			{
				if ((i == s.tail[k].first) && (j == s.tail[k].second)) //hey this means we're on a snake position
				{
					map[i][j] = 'O';
				}
				else if ((i == food_r) && (j == food_c))
				{
					map[i][j] = 'X';
				}
				else
				{
					map[i][j] = '*';
				}
			}
		}
	}
}
void restartGame()
{
	refresh_rate = 200;
	s.head_x = 0;
	s.head_y = 0;
	s.tail.clear();
	system("cls");
	createMap();
	s.x = 1;
	s.y = 0;
	score = 0;
}
bool isGameOver()
{
	//check to see if current direction would exceed possible locations
	int temp_x = s.head_x + s.x;
	int temp_y = s.head_y + s.y;
	bool isOverlap = false;
	bool isOutOfBounds = false;
	/*for (int i = s.tail.size() - 2; i > 0; i--)
	{
		if (s.tail[s.tail.size() - 1].first == s.tail[i].first && s.tail[s.tail.size()-1].second == s.tail[i].second)
		{
			isOverlap = true;
			break;
		}
	}*/
	if ((temp_x > 39) || (temp_y > 19) || (temp_x < 0) || (temp_y < 0))
	{
		isOutOfBounds = true;
	}
	return (isOutOfBounds || isOverlap );
}
bool isfoodConsumed()
{
	if ((s.head_x == food_c) && (s.head_y == food_r))
	{
		s.eatFood(s.head_y+s.y, s.head_x+s.x); //add location of head to tail;
		score += 1;
		//std::cout << "You ate food";
		return true;
	}
	return false;
}
void updateFood()
{
	generateFood();
	map[food_r][food_c] = 'X';
}
void playGame()
{
start:
	s.tail.push_back(std::make_pair(s.head_y, s.head_x));
	bool game_over = false;
	updateFood();
	while (true)
	{
		game_over = isGameOver();
		if (game_over)
		{
			break;
		}
		moveHead();
		bool eaten = isfoodConsumed();
		s.editTail(); //broken :(
		editMap();
		if (eaten)
		{
			updateFood();
			if (refresh_rate > 0)
			{
				refresh_rate -= 25;
			}
		}
		displayMap();
		Sleep(refresh_rate);//amount is in miliseconds
		system("cls");		//clear screen
	}
	char temp;
	std::cout << "You lost!" << '\n';
	std::cout << "You score was: " << score << '\n';
	std::cout << "Would you like to play again " << "(Y/N)?" << '\n';
input:
	std::cin >> temp;
	if (temp == 'Y')
	{
		restartGame();
		goto start;
	}
	else if (temp == 'N')
	{
		exit;
	}
	else
	{
		std::cout << "Invalid input, enter again" << '\n';
		goto input;
	}
}

int main()
{
	srand(time(0));
	createMap();
	//displayMap();
	std::thread arrow_input(getInput); //create thread to get get input and play game at the same time
	arrow_input.detach();			   // that way we don't have to wait for thread to finish(cause it wont lmao)	   
	playGame();
	return 0;
}

Snake::Snake()
{
}
Snake::~Snake()
{
}