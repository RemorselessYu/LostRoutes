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
	if (!BaseLayer::create()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto top = Sprite::createWithSpriteFrameName("setting-top.png");
	top->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - top->getContentSize().height / 2));
	this->addChild(top);

	//音效
	auto soundOnSprite = Sprite::createWithSpriteFrameName("setting.check-on.png");
	auto soundOffSprite = Sprite::createWithSpriteFrameName("setting.check-off.png");
	auto soundOnMenuItem = MenuItem::create(soundOnSprite, NULL);
	auto soundOffMenuItem = MenuItem::create(soundOffSprite, NULL);
	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingLayer::menuSoundToggleCallback, this),
		soundOnMenuItem,
		soundOffMenuItem,
		NULL);

	//音乐
	auto musicOnSprite = Sprite::createWithSpriteFrameName("setting.check-on.png");
	auto musicOffSprite = Sprite::createWithSpriteFrameName("setting.check-off.png");
	auto musicOnMenuItem = MenuItem::create(musicOnSprite, NULL);
	auto musicOffMenuItem = MenuItem::create(musicOffSprite, NULL);
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingLayer::menuMusicToggleCallback, this),
		musicOnMenuItem,
		musicOffMenuItem,
		NULL);

	auto mu = Menu::create(soundToggleMenuItem, musicToggleMenuItem, NULL);
	mu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2) + Vec2(70, 50));
	mu->alignItemsVerticallyWithPadding(25.0f);
	this->addChild(mu);

	auto lblSound = Label::createWithTTF(MyUtility::getUTF8Char("lblSound"), "fonts/hanyi.ttf", 36);
	lblSound->setColor(Color3B(14, 83, 204));
	lblSound->setPosition(mu->getPosition() - Vec2(100, -34));
	this->addChild(lblSound);

	auto lblMusic = Label::createWithTTF(MyUtility::getUTF8Char("lblMusic"), "fonts/hanyi.ttf", 36);
	lblMusic->setColor(Color3B(14, 83, 204));
	lblMusic->setPosition(lblSound->getPosition() - Vec2(0, 60));
	this->addChild(lblMusic);

	//设置音乐和音效选中状态
	UserDefault *default = UserDefault::getInstance();
	if (default->getBoolForKey(MUSIC_KEY)) {
		musicToggleMenuItem->setSelectedIndex(0);
	}
	else {
		musicToggleMenuItem->setSelectedIndex(1);
	}

	if (default->getBoolForKey(SOUND_KEY)) {
		soundToggleMenuItem->setSelectedIndex(0);
	}
	else {
		soundToggleMenuItem->setSelectedIndex(1);
	}

	return true;
}

void SettingLayer::menuSoundToggleCallback(cocos2d::Ref * pSender)
{
	UserDefault *default = UserDefault::getInstance();
	if (default->getBoolForKey(SOUND_KEY)) {
		default->setBoolForKey(SOUND_KEY, false);
	}
	else {
		default->setBoolForKey(SOUND_KEY, true);
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}

void SettingLayer::menuMusicToggleCallback(cocos2d::Ref * pSender)
{
	UserDefault *default = UserDefault::getInstance();
	if (default->getBoolForKey(MUSIC_KEY)) {
		default->setBoolForKey(MUSIC_KEY, false);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else {
		default->setBoolForKey(MUSIC_KEY, true);
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_2, true);
	}
}
