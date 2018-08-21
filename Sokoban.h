#pragma once
#include <vector>
#include <iostream>
#include "Maze.h"
#include "Gold.h"
#include "Box.h"

	enum Direction
	{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT,
	};

	// �����Ҫ֪��Ŀ��λ����û��ǽ�ڣ���Ҫ֪��Ŀ��λ����û������
	class Player
	{
	public:
		int i;
		int j;

		std::vector<Box*> * boxs;
		Maze* pMaze;

		Player(int i_, int j_, Maze* pMaze_):i(i_),j(j_), pMaze(pMaze_)
		{
			boxs = &Box::Boxs;
		}

		// �ɵ�ǰλ�ú��˶���������µ�λ��
		void GetNewPos(const int iOld, const int jOld, const Direction Dir_, int & iNew, int & jNew)
		{
			iNew = iOld, jNew = jOld;
			switch (Dir_)
			{
			case UP: { iNew = iOld - 1; break; }
			case DOWN: { iNew = iOld + 1; break; }
			case LEFT: { jNew = jOld - 1; break; }
			case RIGHT: { jNew = jOld + 1; break; }
			default:	break;
			}
		}

		void SetPos(int & iOld, int & jOld, const int iNew, const int jNew)
		{
			iOld = iNew;
			jOld = jNew;
		}

		// ������(i,j)λ�õ����ӵ���ţ�λ�ҵ�����-1
		int HasBox(int i_, int j_)
		{
			int index = 0;
			for (const auto box : *boxs)
			{
				if (box->i == i_ && box->j == j_)
					return index;
				index++;
			}
			return -1;
		}
		
		// ���ƶ�
		void Move(Direction Dir_)
		{
			int iNew, jNew;
			GetNewPos(i, j, Dir_, iNew, jNew);
			if (!pMaze->IsWall(iNew, jNew))
			{
				int index = HasBox(iNew, jNew);
				// û��box���߳ɹ��ƶ����������λ����Ϣ
				if (index == -1 || PushBox(index, Dir_))
					SetPos(i, j, iNew, jNew);
			}
		}

		// �����Ϊindex�����ӳ�����Dir_�ƶ����ɹ�����true��ʧ�ܷ���false��
		bool PushBox(int index, Direction Dir_)
		{
			int &i = (*boxs)[index]->i;
			int &j = (*boxs)[index]->j;
			int iNew, jNew;

			GetNewPos(i, j, Dir_, iNew, jNew);
			bool a = !pMaze->IsWall(iNew, jNew);
			bool b = HasBox(iNew, jNew) == -1;
			if (!pMaze->IsWall(iNew, jNew) && HasBox(iNew, jNew) == -1)
			{
				SetPos(i, j, iNew, jNew);
				return true;
			}
			else
				return false;
		}
	};

	class Game
	{
	public:
		void create(int M, int N, const char* Cmd) 
		{
			pMaze = new Maze(M, N);

			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
				{
					switch (Cmd[i*N + j])
					{
					case '#': { pMaze->Grids[i][j] = '#'; break; };
					case ' ': { pMaze->Grids[i][j] = ' '; break; };
					case '@': 
					{ 
						m_pPlayer = new Player(i,j,pMaze);
						break; 
					};
					case '*': 
					{ 
						pMaze->Grids[i][j] = ' '; 
						new Box(i, j);
						break; 
					};
					case '+': 
					{ 
						pMaze->Grids[i][j] = ' '; 
						new Gold(i, j);
						break; 
					};
					default:
						break;
					}
				}
			}
		};

		bool GameOver()
		{
			for (const auto gold : Gold::Golds)
			{
				bool result = false;
				for (const auto box : Box::Boxs)
				{
					if (box->i == gold->i && box->j == gold->j)
					{
						result = true;
						break;
					}
				}
				if (!result)	return false;
			}
			return true;
		}

		void PrintGame()
		{
			auto show = pMaze->Grids;
			
			// ����Ŀ��
			for (auto gold : Gold::Golds)
			{
				int i = gold->i;
				int j = gold->j;
				show[i][j] = '+';
			}

			// ��������
			for (auto box : Box::Boxs)
			{
				int i = box->i;
				int j = box->j;
				show[i][j] = '*';
			}

			// �������
			show[m_pPlayer->i][m_pPlayer->j] = '@';

			// ��ʾ��Ϸ
			for (const auto line : show)
			{
				for (const auto ch : line)
					std::cout << ch;
				std::cout << std::endl;
			}

			if (GameOver())
			{
				std::cout << "Game Over!" << std::endl;
			}
		}

		Maze* pMaze;
		Player * m_pPlayer;
	};

