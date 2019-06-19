#include "EatHotdongGame.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


Scene* Eathotdog::createScene()
{
	auto scene = Scene::create();
	auto layer = Eathotdog::create();
	scene->addChild(layer);
	return scene;
}
bool Eathotdog::init(){

	Size size = Director::getInstance()->getWinSize();
	double ratio = size.height / 2400;
	//添加背景
	auto bg = Sprite::create(pic_bg);
	bg->setPosition(size.width / 2, size.height / 2);
	bg->setScale(size.width / bg->getContentSize().width, size.height / bg->getContentSize().height);
	this->addChild(bg);
	//添加人物
	player = Sprite::create(pic_player1);
	player->setPosition(Vec2(size.width/2, size.height/8));
	player->setTag(TAG_PLAYER);
	player->setScale(ratio);
	this->addChild(player);
	//加动作
	Animation* an = Animation::create();
	an->addSpriteFrameWithFileName(pic_player1);
	an->addSpriteFrameWithFileName(pic_player2);
	an->setDelayPerUnit(0.25f);
	an->setLoops(-1);
	Animate* anim = Animate::create(an);
	player->runAction(anim);
	//加入热狗
	hotdogs = new Hotdog();
	this->addChild(hotdogs);

	//加分数
	auto score = LabelBMFont::create("0", "fonts/futura-48.fnt");
	score->setPosition(Point(size.width / 2, size.height / 4 * 3));
	this->addChild(score);
	score->setTag(TAG_SCORE);
	//加等级
	level = LabelBMFont::create("level 1", "fonts/futura-48.fnt");
	level->setPosition(Point(size.width / 8, size.height / 9 * 8));
	this->addChild(level);
	level->setTag(TAG_LEVEL);
	//左移按钮
	auto BL = MenuItemImage::create(pic_bl1, pic_bl2, CC_CALLBACK_1(Eathotdog::movel, this));
	auto menu = Menu::create(BL, NULL);
	menu->setPosition(Vec2(size.width / 16, size.height / 2));
	menu->setTag(TAG_BL);
	this->addChild(menu);

	//右移按钮
	auto BR = MenuItemImage::create(pic_br1, pic_br2, CC_CALLBACK_1(Eathotdog::mover, this));
	auto menu1 = Menu::create(BR, NULL);
	menu1->setPosition(Vec2(size.width - size.width / 16, size.height / 2));
	menu1->setTag(TAG_BR);
	this->addChild(menu1);

	//开始按钮

	auto startG = MenuItemImage::create(pic_play_bu, pic_play_bu, CC_CALLBACK_1(Eathotdog::start_game, this));
	auto menu2 = Menu::create(startG, NULL);
	menu2->setPosition(Vec2(size.width / 3,size.height/2));
	menu2->setTag(TAG_BSTART);
	menu2->setScale(ratio*2);
	this->addChild(menu2);

	//重新按钮

	auto startR = MenuItemImage::create(pic_restart_bu, pic_restart_bu, CC_CALLBACK_1(Eathotdog::restart_game, this));
	auto menu3 = Menu::create(startR, NULL);
	menu3->setPosition(Vec2(size.width / 3, size.height / 2));
	menu3->setTag(TAG_RSTART);
	this->addChild(menu3);
	menu3->setScale(ratio*2);
	menu3->setVisible(false);

	//暂停按钮

	auto startP = MenuItemImage::create(pic_stop_bu, pic_stop_bu, CC_CALLBACK_1(Eathotdog::pause_game, this));
	auto menu4 = Menu::create(startP, NULL);
	menu4->setPosition(Vec2(size.width /(1.5), size.height /(1.5)));
	menu4->setTag(TAG_PAUSE*2);
	menu4->setScale(ratio*2);
	this->addChild(menu4);



	scheduleUpdate();
	
	return true;
}

void Eathotdog::update(float time){//更新函数

	auto size = Director::getInstance()->getVisibleSize();
	Rect rplayer = ((Sprite*)player)->getBoundingBox();
	hotdogs->update((LabelBMFont*)this->getChildByTag(TAG_LEVEL),GAME_STATUS);
	switch (GAME_STATUS)
	{
	case GAME_PLAYING:
		
		//碰撞检测
		for (auto hotdog : hotdogs->hotdogList)
		{
			bool flag = rplayer.intersectsRect(hotdog->getBoundingBox());
			if (!hotdog->isVisible())
				continue;
			if (flag){
				
				auto emitter = ParticleMeteor::create();
				emitter->setDuration(0.1);
				emitter->setStartSize(200);
				emitter->setEmitterMode(ParticleSystem::Mode::RADIUS);

				emitter->setStartRadius(300);
				emitter->setStartRadiusVar(50);
				emitter->setEndRadius(0);
				emitter->setEndRadiusVar(50);

				emitter->setPosition(Vec2(size.width / 4, size.height / 5 * 4));
				player->addChild(emitter);
				
				if (hotdog->getName() == "bomb"){
					GAME_STATUS = GAME_END;
					SimpleAudioEngine::sharedEngine()->playBackgroundMusic(sound_bgboom, false);
				}
				else{
					aaa++;
					SimpleAudioEngine::sharedEngine()->playBackgroundMusic(sound_bgeff, false);
				}
				//分数
				auto scoreSprite = (LabelBMFont*)this->getChildByTag(TAG_SCORE);
				String* s = String::createWithFormat("%d", aaa);
				scoreSprite->setString(s->getCString());
				hotdog->setVisible(false);
			}
		}
		break;
	case GAME_PAUSE:
		break;
	case GAME_END:
		this->getChildByTag(TAG_RSTART)->setVisible(true);
		

		break;


	}
	
}


void Eathotdog::movel(cocos2d::Ref* pSender)//左移
{
	if (GAME_STATUS == GAME_PLAYING){
		Size size = Director::getInstance()->getWinSize();
		double get = this->getChildByTag(TAG_PLAYER)->getPositionX();
		if (get>size.width / 12) this->getChildByTag(TAG_PLAYER)->setPositionX(get - size.width / 16);
	}

}

void Eathotdog::mover(cocos2d::Ref* pSender)//右移
{
	if (GAME_STATUS == GAME_PLAYING){
		Size size = Director::getInstance()->getWinSize();
		double get = this->getChildByTag(TAG_PLAYER)->getPositionX();
		if (get<(size.width - size.width / 12)) this->getChildByTag(TAG_PLAYER)->setPositionX(get + size.width / 16);
	}
	
}

void Eathotdog::start_game(cocos2d::Ref* pSender)//
{
	this->getChildByTag(TAG_BSTART)->setVisible(false);
	GAME_STATUS = GAME_PLAYING;
}

void Eathotdog::restart_game(cocos2d::Ref* pSender)//右移
{
	aaa = 0;
	auto scoreSprite = (LabelBMFont*)this->getChildByTag(TAG_SCORE);
	String* s = String::createWithFormat("%d", aaa);
	scoreSprite->setString(s->getCString());
	this->getChildByTag(TAG_RSTART)->setVisible(false);
	GAME_STATUS = GAME_PLAYING;
}

void Eathotdog::pause_game(cocos2d::Ref* pSender)//右移
{
	
	if (GAME_STATUS == GAME_PLAYING){
		GAME_STATUS = GAME_PAUSE;
	}
	else if (GAME_STATUS == GAME_PAUSE){
		GAME_STATUS = GAME_PLAYING;
	}
}
