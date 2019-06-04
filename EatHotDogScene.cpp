#include "EatHotdongGame.h"

Scene* Eathotdog::createScene()
{
	auto scene = Scene::create();
	auto layer = Eathotdog::create();
	scene->addChild(layer);
	return scene;
}
bool Eathotdog::init(){
	Size size = Director::getInstance()->getWinSize();
	//�������
	player = Sprite::create("pic/bomb.png");
	player->setPosition(Vec2(size.width/2, 50));

	this->addChild(player);

	//�����ȹ�
	hotdog = new Hotdog();
	this->addChild(hotdog);

	

	scheduleUpdate();
	return true;
}

void Eathotdog::update(float time){//���º���
	hotdog->update();
}
