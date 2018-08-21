#pragma once
#include <vector>
class Gold
{
public:
	Gold() {};
	~Gold() {};

	int i;
	int j;

	static std::vector<Gold*> Golds;

	Gold(int i_, int j_) :i(i_), j(j_)
	{
		Golds.push_back(this);
	}
};

