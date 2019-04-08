#include "HelpScene.h"

USING_NS_CC;

cocos2d::Scene * HelpLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = HelpLayer::create();
	scene->addChild(layer);
	return scene;
}

bool HelpLayer::init()
{
	if (!BaseLayer::create())
		return false;


	return true;
}
