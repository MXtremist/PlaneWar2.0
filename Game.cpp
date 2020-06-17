
#include"Game.h"

int random(int a, int b)
{
	return (rand() % (b - a + 1)) + a;
}

Plane::Plane()
{
	int r = random(1, 3);
	if (r == 1)
	{
		loadimage(&img, _T("Image\\enemy1.PNG"), 50, 50);
		loadimage(&img_b, _T("Image\\enemy1_b.PNG"), 50, 50);
	}
	else if (r == 2)
	{
		loadimage(&img, _T("Image\\enemy2.PNG"), 50, 50);
		loadimage(&img_b, _T("Image\\enemy2_b.PNG"), 50, 50);
	}
	else if (r == 3)
	{
		loadimage(&img, _T("Image\\enemy3.jpg"), 50, 50);
		loadimage(&img_b, _T("Image\\enemy3_b.jpg"), 50, 50);
	}
	POS.second = 30;
	POS.first = random(30, 570);
}

void Plane::InitMe()
{
	IMAGE my1, my2;
	loadimage(&my1, _T("Image\\my.PNG"),50, 50);
	loadimage(&my2, _T("Image\\my_b.PNG"), 50, 50);
	img = my1; img_b = my2;
	POS.second = 650;
	POS.first = 285;
}

void Plane::drawPlane()
{
	putimage(POS.first, POS.second, &img_b, SRCAND);
	putimage(POS.first,POS.second, &img, SRCPAINT);
}

void Plane::planeMove(char x)
{
	if (x == 'a' || x == 'A')
		if (POS.first > 40)
			POS.first -= 10;

	if (x == 's' || x == 'S')
		if (POS.second <640)
			POS.second += 10;

	if (x == 'd' || x == 'D')
		if (POS.first < 540)
			POS.first += 10;

	if (x == 'w' || x == 'W')
		if (POS.second >40)
			POS.second -=10;
}

bool Plane::JudgePlane()
{
	return (POS.first >= 30 && POS.second <= 650 && POS.first <= 550 && POS.second >=30);
}


void Plane::randMove()
{
	POS.second += 5;
	int i = random(1, 3);
	switch (i)
	{
	case 1:planeMove('a'); break;
	case 2:planeMove('d'); break;
	case 3:break;
	default:break;
	}
}

void Game::newEnemy()
{
	if (enemy.size() < ENEMY_NUM)
		enemy.push_back(Plane());
}

void Game::drawBullet()
{
	for (vector<pair<int, int>>::iterator it = bullet.begin(); it != bullet.end(); ++it)
	{
		putimage(it->first, it->second, &imgbul_b, SRCAND);
		putimage(it->first, it->second, &imgbul, SRCPAINT);
	}
}

void Game::bulletMove()
{
	for (vector<pair<int, int>>::iterator it = bullet.begin(); it != bullet.end(); )
	{
		it->second -= 10;
		if (it->second < 15)
		{
			it = bullet.erase(it); 
		}
		else
		{
			it++;
		}
	}
}

void Game::BulletInEnemy()
{
	for (vector<pair<int, int>>::iterator it = bullet.begin(); it != bullet.end();)
	{
		bool t = false;
		for (vector<Plane>::iterator itt = enemy.begin(); itt != enemy.end(); )
		{
			if((abs(itt->POS.first+25 - it->first) <= 25)&& (abs(itt->POS.second - it->second) <= 25))
			{
				t = true;
				itt = enemy.erase(itt);
				score += ASCORE;
			}
			else
				itt++;
		}
		t == true ? it = bullet.erase(it) : it++;

	}
}

bool Game::EnemyInMe()
{
	for (vector<Plane>::iterator it = enemy.begin(); it != enemy.end(); it++)
	{
		if ((abs(it->POS.first - me.POS.first )<= 25) && (abs(it->POS.second - me.POS.second )<= 50))
			return true;
	}
	return false;
}

void Game::GameOver()
{
	Sleep(MOVETIME * 10); settextcolor(RED);
	outtextxy(220, 400, _T("GAME OVER!"));
	TCHAR s[20] = { 0 };
	_stprintf_s(s, _T("%d"), score);        // 高版本 VC 推荐使用 _stprintf_s 函数
	f.lfHeight = 28;                      // 设置字体高度为 48
	settextstyle(&f); settextcolor(BLACK);
	outtextxy(220, 450, _T("您的分数:")); 
	outtextxy(330, 450, s);
	Sleep(MOVETIME * 100); 
	f.lfHeight = 32;                      // 设置字体高度为 48
	settextstyle(&f); settextcolor(WHITE);
	ofstream fout("scorelist.txt", ios::app);
	time_t curtime;
	time(&curtime);
	fout << MODE << "		" << ctime(&curtime) << score << endl;
	fout.close();
}

void Game::run()
{
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 32;                      // 设置字体高度为 48
	settextstyle(&f);                     // 设置字体样式
	
	MOUSEMSG m;		// 定义鼠标消息

	cleardevice();
	putimage(0, 0, &back);
	outtextxy(220, 400, _T("1.开始游戏"));
	outtextxy(220, 450, _T("2.排行榜"));
	outtextxy(220, 500, _T("3.退出游戏"));
	while (1)
	{
		FlushMouseMsgBuffer();
		m = GetMouseMsg();
		if (m.mkLButton&&m.x >= 200 && m.x <= 380 && m.y >= 375 && m.y < 440)
		{
			Difficulty();
			 break;
		}
		else if (m.mkLButton&&m.x >= 200 && m.x <= 380 && m.y >= 440 && m.y < 490)
		{
			Scorelist();
		}
		else if (m.mkLButton&&m.x >= 200 && m.x <= 380 && m.y >= 490 && m.y <= 640)
			return;
		
	}
	for(int num=0;num<ENEMY_NUM;num++)
		enemy.push_back(Plane());

	int i = 1;
	cleardevice();
	while (1)
	{
		
		Sleep(MOVETIME);
		putimage(0, 0, &runningback);
		//cleardevice();
		putimage(601,1, &runningback2);
		f.lfHeight = 20; 
		settextstyle(&f);
		TCHAR s[10] = { 0 };
		_stprintf_s(s, _T("%d"), score);        // 高版本 VC 推荐使用 _stprintf_s 函数
		outtextxy(600, 400, s);
		f.lfHeight = 32; settextstyle(&f);
		me.drawPlane(); 
		for (vector<Plane>::iterator it = enemy.begin(); it != enemy.end(); it++)
			it->drawPlane();
		if (_kbhit())
		{
			char x = _getch();
			if ('a' == x || 's' == x || 'd' == x || 'w' == x || 'A' == x || 'S' == x || 'D' == x || 'W' == x)
			{
				if (me.JudgePlane())
				{
					me.planeMove(x);
					me.drawPlane();
				}
			}
			else if (' ' == x && bullet.size() <= MAXBULLET)
			{
				pair<int, int> newb;
				newb.first= me.POS.first + 22;
				newb.second = me.POS.second;
				bullet.push_back(newb);
			}
			else if (27 == x)
			{
				GameOver(); break;
			}
		}
		
		bulletMove();
		drawBullet();
		BulletInEnemy();
		newEnemy();
		if (EnemyInMe())
		{
			GameOver(); break;
		}
		if (i % TIME== 0)
		{
			i = 1;
			for (vector<Plane>::iterator it = enemy.begin(); it != enemy.end(); it++)
				it->randMove();
		}
		i++;
	}
}

void Game::Difficulty()
{
	cleardevice(); 
	putimage(0, 0, &back);
	outtextxy(220, 300, _T("选取难度"));
	outtextxy(220, 400, _T("简单"));
	outtextxy(220, 450, _T("普通"));
	outtextxy(220, 500, _T("困难")); 
	MOUSEMSG m;		// 定义鼠标消息
	while (1)
	{
		Sleep(MOVETIME / 2);
		//FlushMouseMsgBuffer(); 
		m = GetMouseMsg();
		if (m.mkLButton&&m.x >= 200 && m.x <= 380 && m.y >= 375 && m.y < 435)
		{
			MODE = "Easy";
			TIME = 50;
			ENEMY_NUM = 3;
			ASCORE = 5;
			MAXBULLET = 9;
			break;
		}
		else if (m.mkLButton&&m.x >= 200 && m.x <= 380 && m.y >= 435 && m.y < 485)
		{
			MODE = "Normal";
			TIME = 20;
			ENEMY_NUM = 5;
			ASCORE = 10;
			MAXBULLET = 12;
			break;
		}
		else if (m.mkLButton&&m.x >= 200 && m.x <= 380 && m.y >= 485 && m.y <= 635)
		{
			MODE = "Hard";
			TIME = 5;
			ENEMY_NUM = 8;
			ASCORE = 15; 
			MAXBULLET = 15;
			break;
		}
	}
}struct Score
{
	string time;
	int s;
};
bool Greater(Score a,Score b)
{
	return a.s > b.s;
}
void Game::Scorelist()
{
	
	vector<Score> se;
	ifstream fin("scorelist.txt");
	while (!fin.eof())
	{
		string s; int e;
		getline(fin, s);
		fin >> e;
		se.push_back(Score{ s,e });
		fin.get();
		if (fin.peek() == EOF)break;
	}
	fin.close();
	sort(se.begin(), se.end(), Greater);
	cleardevice();
	putimage(0, 0, &back);
	f.lfHeight = 20;
	settextstyle(&f);
	outtextxy(200, 300, _T("排名"));
	outtextxy(300, 300, _T("得分(按ESC退出）")); 
	f.lfHeight = 32;
	settextstyle(&f);
	for (int i=0;i<se.size();i++)
	{
		TCHAR sw[3];
		_stprintf(sw, _T("%d"), i+1);        // 高版本 VC 推荐使用 _stprintf_s 函数
		outtextxy(200, 322+i*23, sw); 
		TCHAR sw2[5];
		_stprintf(sw2, _T("%d"), se[i].s);
		outtextxy(300, 322 + i * 23, sw2);
	}
	while (1)
	{
		if (_kbhit())
		{
			char x = _getch();
			if (x == 27)
			{
				cleardevice();
				putimage(0, 0, &back);
				outtextxy(220, 400, _T("1.开始游戏"));
				outtextxy(220, 450, _T("2.排行榜"));
				outtextxy(220, 500, _T("3.退出游戏"));
				break;
			}
		}
	}

}