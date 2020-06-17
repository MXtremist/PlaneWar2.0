#include"Game.h"
int main()
{
	initgraph(750, 700);
	setbkmode(TRANSPARENT);
	srand((int)time(0));
	Game g;
	g.run();
}