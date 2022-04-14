#pragma once
#include "stdafx.h"

class Entombed
{
	unsigned int getRandomBit();
	int MAGIC(unsigned int lasttwo, unsigned int threeabove);
	bool isZeroPresent(std::vector<unsigned int> lastrows);
	enum wallType { 
		IS_WALL = 1, 
		NO_WALL = 0, 
		RANDOM_WALL = -1
	};
public:
	Entombed();
	~Entombed();
	std::string render_line(unsigned int row);
	void rowGen(std::vector<unsigned int> &lastrows);	
};

