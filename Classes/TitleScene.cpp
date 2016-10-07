//
//  TitleScene.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/08/21.
//
//

#include "TitleScene.h"
#include "HomeScene.h"
#include "LoadingLayer.h"

#include "BGMPlayer.h"

TitleScene::TitleScene() = default;
TitleScene::~TitleScene() = default;

bool TitleScene::init()
{
    BaseScene::init();

    auto homeButton = getChildByName<Button*>("Home");
    BaseScene::onTouch(homeButton, [&](Ref* ref){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
        this->scheduleOnce([&](float dt){
            auto scene = HomeScene::createScene();
            auto fade = TransitionFade::create(2.0f, scene);
            Director::getInstance()->replaceScene(fade);
        }, 1.0f, "loading");
        auto loading = LoadingLayer::create();
        addChild(loading);
    });
    
    return true;
}

void TitleScene::onEnter()
{
    BaseScene::onEnter();
    
    BGMPlayer::stopAll();
    BGMPlayer::play("Sounds/04_leprechaun.mp3");
}

