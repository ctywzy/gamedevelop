#include "cocos2d.h"

#include<vector>
USING_NS_CC;
#pragma once
class Hotdog :public Node
{
public:
	Vector<Sprite*> hotdogList;
	void update();

	void addone(int setone);//Ìí¼ÓµôÂäµÄÈÈ¹·
	


	int addbomb = 0;
	int addbig = 0;
	int addCount = 0;
	Hotdog();
};