#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;



Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/loading_texture.plist");

	//设置背景图片
	auto bg = TMXTiledMap::create("map/red_bg.tmx");
	this->addChild(bg);

	//设置图标精灵
	auto logo = Sprite::createWithSpriteFrameName("logo.png");
	logo->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(logo);

	//设置加载精灵
	auto sprite = Sprite::createWithSpriteFrameName("loding4.png");
	sprite->setPosition(logo->getPosition() - Vec2(0, logo->getContentSize().height / 2 + 30));
	this->addChild(sprite);

	//设置加载精灵动画
	//////////////////////动画开始//////////////////////
	Animation *animation = Animation::create();
	for (int i = 1; i <= 4; i++) {
		__String *frameName = __String::createWithFormat("loding%d.png", i);
		log("frameName = %s", frameName->getCString());
		SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		animation->addSpriteFrame(spriteFrame);
	}
	animation->setDelayPerUnit(0.5f);    //这是两个帧之间的间隔
	animation->setRestoreOriginalFrame(true);    //动画执行后还原初始状态

	Animate *action = Animate::create(animation);
	sprite->runAction(RepeatForever::create(action));
	//////////////////////动画结束//////////////////////

	m_nNumberOfLoading = 0;    //初始化加载纹理图片的个数
	//预加载纹理
	Director::getInstance()->getTextureCache()->addImageAsync("texture/home_texture.png",
		CC_CALLBACK_1(HelloWorld::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("texture/setting_texture.png",
		CC_CALLBACK_1(HelloWorld::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("texture/gameplay_texture.png",
		CC_CALLBACK_1(HelloWorld::loadingTextureCallBack, this));

	//预加载声音
	_loadingAudioThread = new std::thread(&HelloWorld::loadingAudio, this);

	return true;
}

void HelloWorld::onExit()
{
	Layer::onExit();
	_loadingAudioThread->join();
	CC_SAFE_DELETE(_loadingAudioThread);
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("texture/loading_textuer.plist");
	Director::getInstance()->getTextureCache()->removeTextureForKey("texture/loading_texture.png");
	this->unschedule(schedule_selector(HelloWorld::delayCall));
}

void HelloWorld::loadingTextureCallBack(cocos2d::Texture2D * texture)
{
	switch (m_nNumberOfLoading++)
	{
	case 0:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/home_texture.plist", texture);
		log("home texture ok.");
		break;
	case 1:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/setting_texture.plist", texture);
		log("setting texture ok.");
		break;
	case 2:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/gameplay_texture.plist", texture);
		log("gameplay texture ok.");
		this->schedule(schedule_selector(HelloWorld::delayCall), 1, 1, 3);
		break;
	default:
		break;
	}
}

void HelloWorld::delayCall(float dt)
{
	auto homeScene = HomeMenuLayer::createScene();
	Director::getInstance()->replaceScene(homeScene);
}

void HelloWorld::loadingAudio()
{
	//初始化音乐
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(bg_music_1);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(bg_music_2);
	//初始化音效
	SimpleAudioEngine::getInstance()->preloadEffect(sound_1);
}
