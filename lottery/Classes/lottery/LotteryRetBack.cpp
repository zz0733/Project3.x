﻿#include "LotteryRetBack.h"
#include "ConfigMgr.h"
#include "MovingLabelLayer.h"
#include "EntityMgr.h"
#include "LotterySceneControl.h"
#include "LotteryActiveCenter.h"
#include "VersionControl.h"

using namespace CocosDenshion;

Scene* LotteryRetBack::scene()
{
	Scene *scene = Scene::create();
	LotteryRetBack *layer = LotteryRetBack::create();
	scene->addChild(layer);
	return scene;
}

LotteryRetBack::LotteryRetBack()
{
	
}
LotteryRetBack::~LotteryRetBack()
{
	
}

bool LotteryRetBack::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->initData();
	this->initView();
	this->setKeypadEnabled(true);
	return true;
}

void LotteryRetBack::initData()
{
	winSize = Director::getInstance()->getWinSize();
}

void LotteryRetBack::initView()
{
	LayerColor* layer = LayerColor::create(ccc4(255, 255, 255, 255), SCREEN_WIDTH, SCREEN_HEIGHT);
	layer->ignoreAnchorPointForPosition(false);
	layer->setPosition(Vec2(winSize.width*0.5,winSize.height*0.5));
	this->addChild(layer);

	//
	Sprite *bk1 = Sprite::createWithSpriteFrame(spriteFrame(HEAD_IMG));
	bk1->setAnchorPoint(Vec2(0,1));
	bk1->setPosition(Vec2(0, SCREEN_HEIGHT));
	bk1->setScaleX(SCREEN_WIDTH / bk1->getContentSize().width);
	bk1->setScaleY(162 / bk1->getContentSize().height);
	this->addChild(bk1,1);

	Sprite *pCloseNormalButton = Sprite::createWithSpriteFrame(spriteFrame("regist_04.png"));
	Sprite *pCloseSelectButton = Sprite::createWithSpriteFrame(spriteFrame("regist_04.png"));
	MenuItemSprite *pCloseItemSprite = MenuItemSprite::create
		(pCloseNormalButton,pCloseSelectButton,CC_CALLBACK_1(LotteryRetBack::back,this));
	Menu *pCloseButton = Menu::create(pCloseItemSprite,NULL);
	pCloseButton->setPosition(Vec2(34, SCREEN_HEIGHT - 105));
	this->addChild(pCloseButton,1);

	float fontSize = 38;
	ccColor3B blackColor = ccc3(76,76,76);

	LabelTTF *title = LabelTTF::create(ConfigMgr::instance()->text("display_DuangDong.xml", "t52"), "", fontSize);
	title->setPosition(Vec2(SCREEN_WIDTH/2, pCloseButton->getPositionY()));
	title->setColor(ccc3(255,255,255));
	this->addChild(title, 1);

	//背景图
	Sprite* sptBody = Sprite::createWithSpriteFrame(spriteFrame("hd_03.png"));
	sptBody->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	sptBody->setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 162));
	this->addChild(sptBody);
}

void LotteryRetBack::onEnter()
{
	Layer::onEnter();
}

void LotteryRetBack::onExit()
{
	Layer::onExit();
}

void LotteryRetBack::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_BACK)  //返回
	{
		back(NULL);
		event->stopPropagation();
	}
}

void LotteryRetBack::back(Object *obj)
{
	playButtonSound();
	Scene *scene = Scene::create();
	LotteryActiveCenter *layer = LotteryActiveCenter::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(LotterySceneControl::sharedSceneControl()->getScene(scene));
}