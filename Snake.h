#pragma once
class Snake
{
public:
	Snake();			   	
	int x = 1;			   //x component of snake
	int y = 0;			   //y component of snake	 
	int head_x = 0;		   //x location of snake head				
	int head_y = 0;		   //y location of snake head
	std::vector<std::pair<int, int>> tail; //will keep previous locations of head to make the tail
	~Snake();

	void editTail()
	{
		int length = this->tail.size() - 1;
		for (int i = 0; i < length; i++)
		{
			this->tail[i] = this->tail[i + 1];
		}
	}
	void eatFood(int r, int c)
	{
		this->tail.push_back(std::make_pair(r,c));
	}
};