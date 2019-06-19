#include "Hotdog.h"

#include "EatHotdongGame.h"
USING_NS_CC;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
Hotdog::Hotdog(){

}

void Hotdog::update(LabelBMFont* level,int GAME_STATUS){
	if (GAME_STATUS == GAME_PLAYING){
		addCount++;
		addsum++;
		if (addsum == 1800){
			x = 4;
			v = 3;
			dis = 45;
			level->setString("level 2");
		}
		if (addsum == 5400){
			x = 4;
			v = 4;
			dis = 40;
			level->setString("level 3");
		}
		if (addsum == 9000){
			x = 3;
			v = 5;
			dis = 30;
			level->setString("level 4");
		}if (addsum == 12600){
			x = 3;
			v = 6;
			dis = 20;
			level->setString("level 5");
		}if (addsum == 15200){
			x = 2;
			v = 9;
			dis = 15;
			level->setString("level 6");
		}

		if (addCount >= dis){
			addCount = 0;
			addbomb++;
			if (addbomb != x){
				addone(0);
			}
		}
		if (addbomb >= x){
			addone(1);
			addbomb = 0;
		}
		for (auto it = hotdogList.begin(); it != hotdogList.end();){
			Sprite* hotdog = *it;
			if (hotdog->getName() == "bomb")
				hotdog->setPositionY(hotdog->getPositionY() - (v + 1));
			else
				hotdog->setPositionY(hotdog->getPositionY() - (v));
			if (hotdog->getPositionY() <0){//ÒÆ³ýÈÈ¹·
				it = hotdogList.erase(it);
				this->removeChild(hotdog);
			}
			else{
				it++;
			}

		}
	}
	else if (GAME_STATUS == GAME_END){
		addsum = 0;
		x = 5;
		v = 2;
	}
	else{

	}
}


void Hotdog::addone(int setone){
	Size size = Director::getInstance()->getWinSize();
	double ratio = size.height / 2000;
	auto sprite = Sprite::create();
	
	int x = CCRANDOM_0_1()*size.width;
	if (x <= size.width/24){
		x += size.width / 24;
	}
	
	if (x >= size.width / 24 * 23){
		x -= size.width / 24;
	}
	if (setone == 0){//ÏÂÂäÈÈ¹·
		sprite = Sprite::create(pic_hotdog);
		sprite->setScale(ratio);
		sprite->setPosition(Vec2(x, size.height));
		hotdogList.pushBack(sprite);
		this->addChild(sprite, 1, "hotdog");
	}
	else if (setone == 1){//ÏÂÂäÕ¨µ¯
		sprite = Sprite::create(pic_bomb);
		sprite->setScale(ratio/1.5);
		sprite->setPosition(Vec2(x, size.height));
		hotdogList.pushBack(sprite);
		this->addChild(sprite, 2, "bomb");
	}
}