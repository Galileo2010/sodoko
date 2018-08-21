#pragma once
#include <vector>
class Maze
{
public:
	Maze() {};
	~Maze() {};

	Maze(int M, int N) {
		Grids.resize(M);
		for (auto& iter : Grids)
			iter.resize(N);
	}

	bool IsWall(int i, int j)
	{
		return Grids[i][j] == '#';
	}
	std::vector<std::vector<char>> Grids;
};

