#include "BaseLayer.h"

USING_NS_CC;


bool BaseLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Í¨¹ýÍßÆ¬µØÍ¼ÉèÖÃ±³¾°Í¼Æ¬
	auto bg = TMXTiledMap::create("map/red_bg.tmx");
	addChild(bg);

	//ÑÛ¾¦¾«Áé
	auto glassesSprite = Sprite::createWithSpriteFrameName("setting.glasses.png");
	glassesSprite->setPosition(Vec2(visibleSize.width - glassesSprite->getContentSize().width / 2, 200));
	addChild(glassesSprite);

	//ÊÖÌ×¾«Áé
	auto handSprit = Sprite::createWithSpriteFrameName("setting.hand.png");
	handSprit->setPosition(Vec2(handSprit->getContentSize().width / 2, 60));
	addChild(handSprit);

	//OK ²Ëµ¥
	auto okNormal = Sprite::createWithSpriteFrameName("setting.button.ok.png");
	auto okSelected = Sprite::createWithSpriteFrameName("setting.button.ok-on.png");

	auto okMenuItem = MenuItemSprite::create(okNormal, okSelected, CC_CALLBACK_1(BaseLayer::menuBackCallback, this));
	auto mu = Menu::create(okMenuItem, NULL);
	mu->setPosition(Vec2(visibleSize.width - mu->getContentSize().width / 2 + 60, 60));
	addChild(mu);


	return true;
}

void BaseLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("BassLayer onEnterTransitionDidFinish");
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_1, true);
	}
}

void BaseLayer::menuBackCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->popScene();
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}
