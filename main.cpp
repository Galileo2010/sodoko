#include <iostream>
#include "Sokoban.h"
using namespace std;
int main()
{
	Game* g = new Game();
	g->create(5, 5, "######+* ## @ ## *+######");
	char ch;
	while (cin >> ch)
	{
		switch (ch)
		{
			case 'W':{g->m_pPlayer->Move(UP);	break;}
			case 'S':{g->m_pPlayer->Move(DOWN);	break;}
			case 'A':{g->m_pPlayer->Move(LEFT);	break;}
			case 'D':{g->m_pPlayer->Move(RIGHT);break;}
		}
		g->PrintGame();
	}
	return 0;
}