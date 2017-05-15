//
//  Constant.cpp
//  Test
//
//  Created by Abhishek Aryan on 07/05/17.
//
//

#include "Constant.hpp"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"

#endif

void its::openApp(std::string packageName){
    
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    
    JniMethodInfo methodInfo;
    
    const char* class_name="org/cocos2dx/cpp/AppActivity";
    const char* method_name="openOtherApp";
    const char* parameter= "(Ljava/lang/String;)V";
    
    
    
    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo, class_name, method_name ,parameter )) {
        return;
    }
    
    jstring jStringParam = methodInfo.env->NewStringUTF(packageName.c_str());
    
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,jStringParam);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    
#endif
    
    
}

void its::createPause(Node* node,Vec2& origin,Size& visibleSize){
    
    auto pauseLayer=LayerColor::create(Color4B::BLACK, visibleSize.width,visibleSize.height);
    
    auto pauseLabel=Label::createWithTTF("Paused", "fonts/Marker Felt.ttf", 24);
    pauseLabel->setPosition(origin.x+visibleSize.width/2,origin.y+visibleSize.height-50);
    pauseLayer->addChild(pauseLabel);
    pauseLayer->setVisible(false);
    pauseLayer->setOpacity(220);  // so that gameplay is slightly visible
    node->addChild(pauseLayer);
    
    auto button =cocos2d::ui::Button::create("CloseNormal.png");
    button->setPosition(Vec2(100,100));
    button->addClickEventListener([](Ref*){
        std::string url = "https://play.google.com/store/xxx";
        cocos2d::Application::getInstance()->openURL(url);
    });

    pauseLayer->addChild(button);

//    auto pause = Sprite::create("CloseNormal.png");
//    pause->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    node->addChild(pause);
//    
//    auto touchListener=EventListenerTouchOneByOne::create();
//    touchListener->setSwallowTouches(false);
//    
//    touchListener->onTouchBegan=[pauseLayer](Touch *pTouch, Event* pEvent){
//        CCLOG("%s","Touched");
//        
//        if(!Director::getInstance()->isPaused()){
//            Director::getInstance()->pause();
//            pauseLayer->setVisible(true);
//            auto sp=dynamic_cast<Sprite*>(pEvent->getCurrentTarget());
//            sp->setTexture("CloseNormal.png");
//        }
//        else {
//            Director::getInstance()->resume();
//            pauseLayer->setVisible(false);
//            auto sp=dynamic_cast<Sprite*>(pEvent->getCurrentTarget());
//            sp->setTexture("CloseSelected.png");
//        }
//        
//        return false;
//    };
//    
//    
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, pause);
//
//    
    MenuItem* pauseButton = MenuItemImage::create("CloseNormal.png","CloseSelected.png",[pauseLayer](Ref*sender){
        
        if(!Director::getInstance()->isPaused()){
            Director::getInstance()->pause();
            pauseLayer->setVisible(true);
        }
        else {
            Director::getInstance()->resume();
            pauseLayer->setVisible(false);
        }
    });
    
    auto buttons = Menu::create(pauseButton,NULL);
    node->addChild(buttons);
    buttons->setPosition(visibleSize.width / 2.0, visibleSize.height / 2.0);
    
    
}

