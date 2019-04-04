#include "GamePlayScene.h"

USING_NS_CC;

cocos2d::Scene * GamePlayLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = GamePlayLayer::create();
	scene->addChild(layer);
	return scene;
}

bool GamePlayLayer::init()
{
	if (!Layer::create())
		return false;


	return true;
}
