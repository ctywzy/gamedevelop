#include "cocos2d.h"
#include "Hotdog.h"
USING_NS_CC;
class Eathotdog : public cocos2d::Layer{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Eathotdog);
	Hotdog* hotdog;

	Sprite* player;

	void update(float time);
};