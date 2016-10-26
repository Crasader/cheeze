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

    auto homeButton = getChildByName<Widget*>("Touch");
    BaseScene::onTouch(homeButton, [&](Ref* ref){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
        auto label = getChildByName<TextBMFont*>("LabelStart");
        label->removeFromParent();
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
    BGMPlayer::play("Sounds/no_1_Clowns_Party.mp3");

    auto title = getChildByName<ImageView*>("Title");
    title->setOpacity(0);
}

void TitleScene::onEnterTransitionDidFinish()
{
    auto title = getChildByName<ImageView*>("Title");
    title->runAction(FadeIn::create(3.0f));

    auto label = getChildByName<TextBMFont*>("LabelStart");
    auto fadeIn = FadeIn::create(0.4f);
    auto wait = DelayTime::create(0.4f);
    auto fadeOut = FadeOut::create(0.4f);
    auto seq = Sequence::create(fadeIn, wait, fadeOut, nullptr);
    auto action = RepeatForever::create(seq);
    label->setVisible(true);
    label->setOpacity(0);
    label->runAction(action);
}

