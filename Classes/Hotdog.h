#include "cocos2d.h"
#include "path.h"

#include<vector>
USING_NS_CC;
#pragma once
class Hotdog :public Node
{
public:
	Vector<Sprite*> hotdogList;
	void update(LabelBMFont* level,int GAME_STATUS);

	void addone(int setone);
	int v = 2;
	int dis = 60;
	int addCount = 0;
	int addbomb = 0;
	int addbig = 0;
	int addsum = 0;
	int x = 5;
	Hotdog();
};