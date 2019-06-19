#include "Login.h"
#include "EatHotdongGame.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
Scene* Login::createScene()
{
	auto scene = Scene::create();
	auto layer = Login::create();
	scene->addChild(layer);
	return scene;
}

bool Login::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size size = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create(pic_fbg);
	bg->setPosition(size.width / 2, size.height / 2);
	bg->setScale(size.width / bg->getContentSize().width, size.height / bg->getContentSize().height);
	this->addChild(bg);
	//username
	p_User_EditBox = EditBox::create(CCSizeMake(750, 50), Scale9Sprite::create(pic_edit));
	p_User_EditBox->setPosition(Vec2(size.width / 2, size.height * 3 / 4));
	p_User_EditBox->setFontColor(Color3B(0, 255, 0));
	p_User_EditBox->setPlaceHolder("Username");
	p_User_EditBox->setMaxLength(12);
	p_User_EditBox->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
	p_User_EditBox->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
	addChild(p_User_EditBox);

	//password
	p_Psw_EditBox = EditBox::create(CCSizeMake(750, 50), Scale9Sprite::create(pic_edit));//create
	p_Psw_EditBox->setPosition(Vec2(size.width / 2, size.height / 2 + 100));
	p_Psw_EditBox->setFontColor(Color3B(0, 255, 0));
	p_Psw_EditBox->setPlaceHolder("Password");
	p_Psw_EditBox->setMaxLength(12);
	p_Psw_EditBox->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
	p_Psw_EditBox->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);
	p_Psw_EditBox->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
	addChild(p_Psw_EditBox);


	Scale9Sprite* confirmnormal = Scale9Sprite::create(pic_br1);//create
	Scale9Sprite* confirmpressd = Scale9Sprite::create(pic_br2);//create
	MenuItemSprite* menuitem = MenuItemSprite::create(confirmnormal, confirmpressd, CC_CALLBACK_1(Login::btncallback, this));
	Menu* menu = CCMenu::create(menuitem, NULL);
	menu->setPosition(size.width / 2, size.height / 2);
	this->addChild(menu);

	//
	m_labelStatusCode = LabelTTF::create("HTTP Status Code", "Marker Felt", 20);
	m_labelStatusCode->setAnchorPoint(Vec2(0, 0.5));
	m_labelStatusCode->setPosition(Vec2(size.width / 2, size.height / 4));
	m_labelStatusCode->setColor(Color3B(255, 0, 0));

	addChild(m_labelStatusCode);
	m_labelStatusCode->setString("waiting...");
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic(sound_bgmusic, true);
	return true;
}

void Login::btncallback(Ref* pSender)
{
	bool requestType_is_get = true;//get or post
	if (requestType_is_get)
	{
		HttpRequest* request = new HttpRequest();// create requestObject
		std::string str1 = "http://acm.zju.edu.cn/onlinejudge/login.do?";
		std::string str2 = p_User_EditBox->getText();
		std::string str3 = p_Psw_EditBox->getText();
		std::string struser = "userName=";
		std::string strpsw = "&password=";
		str1 = str1 + struser + str2 + strpsw + str3;

		request->setUrl(str1.c_str());//set url 
		request->setRequestType(HttpRequest::Type::GET);//设置为Get模式
		request->setResponseCallback(CC_CALLBACK_2(Login::onHttpRequestCompleted, this));//设置响应的回调 
		request->setTag("GET test");
		HttpClient::getInstance()->send(request);//send request
		request->release();
	}
	else
	{
		HttpRequest* request = new HttpRequest();// create requestObject
		std::string str1 = "http://acm.zju.edu.cn/onlinejudge/login.do?";
		std::string str2 = p_User_EditBox->getText();
		std::string str3 = p_Psw_EditBox->getText();
		std::string struser = "userName=";
		std::string strpsw = "&password=";
		str1 = str1 + struser + str2 + strpsw + str3;


		request->setUrl(str1.c_str());//url
		request->setRequestType(HttpRequest::Type::POST);//设置为Post模式
		request->setResponseCallback(CC_CALLBACK_2(Login::onHttpRequestCompleted, this));// 设置响应的回调

		const char* postData = str2.c_str();

		request->setRequestData(postData, strlen(postData));//set userdata:usernamed and password

		request->setTag("POST test");
		HttpClient::getInstance()->send(request);//
		request->release();//
	}


}


void Login::onHttpRequestCompleted(HttpClient* client, HttpResponse* response)
{
	if (!response->isSucceed())
	{
		CCString strError;
		strError.initWithFormat("Receive Error! \n%s\n", response->getErrorBuffer());
		m_labelStatusCode->setString(strError.getCString());
		return;
	}
	//还需要分析返回来的字符串是否为登录成功
	std::vector<char> *buffer = response->getResponseData();//  
	std::string recieveData;

	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		recieveData += (*buffer)[i];
	}
	std::string result = recieveData.c_str();
	std::string::size_type idx = result.find("Handle or password is invalid.");

	if (idx == std::string::npos)
		Director::getInstance()->replaceScene(Eathotdog::createScene());
	else
		m_labelStatusCode->setString("Login Failed");
}