#include "Hotdog.h"
Hotdog::Hotdog(){

}

void Hotdog::update(){
	addCount++;
	if (addCount == 60){
		addone(0);
		addCount = 0;
		addbomb++;
		addbig++;
	}if (addbomb == 5){
		addone(1);
		addbomb = 0;
	}if (addbig == 10){
		addone(2);
		addbig = 0;
	}
	for (auto it = hotdogList.begin(); it != hotdogList.end();){
		Sprite* hotdog = *it;
		hotdog->setPositionY(hotdog->getPositionY() - 3);
		if (hotdog->getPositionY()<0){//�Ƴ��ȹ�
			it = hotdogList.erase(it);
			this->removeChild(hotdog);
		}
		else{
			it++;
		}

	}
}


void Hotdog::addone(int setone){
	
	Size size = Director::getInstance()->getWinSize();
	double ratio = size.height / 2400;
	auto sprite = Sprite::create();
	if (setone == 0){
		
		sprite = Sprite::create("pic/hotdog.png");//������ȹ�
	}
	else if(setone==1){
		sprite = Sprite::create("pic/bomb.png");//ը��
	}
	else if (setone == 2){
		sprite = Sprite::create("pic/bigone.png");//�߷�ֵ���ȹ�
	}

	int x = CCRANDOM_0_1()*size.width;
	if (x <= 15)
		x += 15;
	sprite->setPosition(Vec2(x, size.height ));
	
	hotdogList.pushBack(sprite);
	if (setone == 0){
		
		sprite->setScale(ratio);
		
		this->addChild(sprite, 1, "hotdog");
	}
		
	else if (setone == 1){

		ParticleSystem *particle = CCParticleMeteor::create();
		sprite->addChild(particle);
		sprite->setScale(ratio);
		particle->setPositionX(particle->getPositionX() - 300);
		particle->setStartSize(100);
		this->addChild(sprite, 2, "bomb");
	}
	else if (setone == 2){
		this->addChild(sprite, 3, "bigger");
	}
}