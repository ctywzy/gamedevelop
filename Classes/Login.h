#pragma once
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#pragma once
//HTTP
#include "network/HttpClient.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::network;

class Login : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(Login);

	EditBox* p_User_EditBox;
	EditBox* p_Psw_EditBox;
	LabelTTF* m_labelStatusCode;

	void btncallback(Ref* pSender);
	void onHttpRequestCompleted(HttpClient* client, HttpResponse* response);
};
