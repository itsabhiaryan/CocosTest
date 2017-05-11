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
