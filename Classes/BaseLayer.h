#pragma once

#include "cocos2d.h"
#include "SystemHeader.h"

class BaseLayer : public cocos2d::Layer
{
public:
	//static cocos2d::Scene * createScene();
	virtual bool init();

	virtual void onEnterTransitionDidFinish();

	void menuBackCallback(cocos2d::Ref *pSender);

	CREATE_FUNC(BaseLayer);
};
