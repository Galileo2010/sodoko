#pragma once
#include <vector>
class Box
{
public:
	Box() {};
	~Box() {};

	int i;
	int j;

	static std::vector<Box*> Boxs;

	Box(int i_, int j_) :i(i_), j(j_) 
	{
		Boxs.push_back(this);
	};
};

