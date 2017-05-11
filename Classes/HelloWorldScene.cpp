#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Constant.hpp"
#include "sqlite3.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    
    // return the scene
    return scene;
}

//cocos2d::UserDefault *userDefaults = cocos2d::UserDefault::getInstance();



// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label);
    
    
    

    auto pauseLayer=LayerColor::create(Color4B::BLACK, visibleSize.width,visibleSize.height);
    
    auto pauseLabel=Label::createWithTTF("Paused", "fonts/Marker Felt.ttf", 24);
    pauseLabel->setPosition(origin.x+visibleSize.width/2,origin.y+visibleSize.height-50);
    pauseLayer->addChild(pauseLabel);
    pauseLayer->setVisible(false);
    pauseLayer->setOpacity(220);  // so that gameplay is slightly visible
    addChild(pauseLayer);
    
    
    auto pause = Sprite::create("CloseNormal.png");
    pause->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    addChild(pause);
    
    auto touchListener=EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan=[pauseLayer](Touch *pTouch, Event* pEvent){
        
        if(!Director::getInstance()->isPaused()){
           Director::getInstance()->pause();
           pauseLayer->setVisible(true);
            auto sp=dynamic_cast<Sprite*>(pEvent->getCurrentTarget());
            sp->setTexture("CloseNormal.png");
        }
        else {
            Director::getInstance()->resume();
            pauseLayer->setVisible(false);
            auto sp=dynamic_cast<Sprite*>(pEvent->getCurrentTarget());
            sp->setTexture("CloseSelected.png");
        }
        
        return true;
    };
    

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, pause);
    

    // position the sprite on the center of the screen
    

    // add the sprite as a child to this layer
    
    
   // auto action= Sequence::create(MoveTo::create(1, Vec2(100,100)),MoveTo::create(1, Vec2(1,100)),nullptr);
   // pause->runAction(RepeatForever::create(action));
    
  
    
    
    MenuItem* pauseButton = MenuItemImage::create("pauseNormal.png","pauseSelected.png",[pauseButton](Ref*sender){
        
        
        if(!Director::getInstance()->isPaused()){
            Director::getInstance()->pause();
        }
        else
            Director::getInstance()->resume();
    });
    
    auto buttons = Menu::create(pauseButton,NULL);
    this->addChild(buttons);
    buttons->setPosition(visibleSize.width / 2.0, visibleSize.height / 2.0);
    
     //pause();
    
    
    
    //scheduleUpdate();
    return true;
}






void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
