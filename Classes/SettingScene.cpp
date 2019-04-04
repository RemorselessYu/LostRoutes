#include "SettingScene.h"

USING_NS_CC;

cocos2d::Scene * SettingLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = SettingLayer::create();
	scene->addChild(layer);
	return scene;
}

bool SettingLayer::init()
{
	if (!Layer::create())
		return false;


	return true;
}
