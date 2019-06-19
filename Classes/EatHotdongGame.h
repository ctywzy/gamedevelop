#include "cocos2d.h"
#include "Hotdog.h"

#pragma once
USING_NS_CC;
class Eathotdog : public cocos2d::Layer{
public:
	

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Eathotdog);
	Hotdog* hotdogs;

	Sprite* player;

	LabelBMFont* level;
	int aaa=0;
	void update(float time);

	void mover(cocos2d::Ref* pSender);

	void movel(cocos2d::Ref* pSender);

	void pause_game(cocos2d::Ref* pSender);

	void start_game(cocos2d::Ref* pSender);

	void restart_game(cocos2d::Ref* pSender);
	int GAME_STATUS = GAME_PAUSE;

};