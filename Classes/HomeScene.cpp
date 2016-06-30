//
//  HomeScene.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/06/09.
//
//

#include "HomeScene.h"

#include "cocos/ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace cocos2d::experimental;

HomeScene::HomeScene() = default;
HomeScene::~HomeScene() = default;

bool HomeScene::init()
{
    BaseScene::init();
    
    AudioEngine::stopAll();
    AudioEngine::play2d("Sounds/bgm_home.mp3", true, 1.0f);
    
    return true;
}

