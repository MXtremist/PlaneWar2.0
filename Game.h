#pragma once
#pragma warning (disable:4996)
#include<iostream>
#include<conio.h>
#include<time.h>  
#include<string>  
#include<vector>
#include<algorithm>
#include<fstream>
#include<cmath>
#include<ctime>
#include<graphics.h>
using namespace std;

class Plane
{
public:
	pair<int, int> POS;
	IMAGE img;
	IMAGE img_b;
	Plane();
	void InitMe();
	void planeMove(char x);
	void randMove();
	bool JudgePlane();
	void drawPlane();
};
class Game
{
protected:
	string MODE;
	int TIME;
	int ENEMY_NUM;
	int ASCORE;
	const int MOVETIME = 25;
	int MAXBULLET;
	int score;
	vector<Plane> enemy;
	Plane me;
	vector< pair<int ,int> > bullet;
	IMAGE imgbul;
	IMAGE imgbul_b;
	IMAGE back; 
	IMAGE runningback;
	IMAGE runningback2;
	LOGFONT f;
public:
	Game()
	{
		loadimage(&back, _T("Image\\background.jpg"),800);
		loadimage(&runningback, _T("Image\\running.png"), 600); 
		loadimage(&imgbul, _T("Image\\bullet.PNG"), 8,25); 
		loadimage(&imgbul_b, _T("Image\\bullet_b.PNG"), 8, 25);
		loadimage(&runningback2, _T("Image\\runningback2.png"),150,415);
		me.InitMe();
		score = 0;
	}
	void run();
	void Scorelist();
	void drawBullet();
	void newEnemy();
	void bulletMove();
	void BulletInEnemy();
	bool EnemyInMe();
	void GameOver();
	void Difficulty();
};
