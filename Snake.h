#pragma once
struct Snake
{

public:
	Snake();			   	
	int x = 0;			   //x component of snake
	int y = 1;			   //y component of snake	 
	int head_x = 0;		   //x location of snake head				
	int head_y = 0;		   //y location of snake head
	std::vector<std::pair<int, int>> tail; //will keep previous locations of head to make the tail
	~Snake();			   
};

