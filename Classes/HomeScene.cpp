//
//  HomeScene.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/06/09.
//
//

#include "HomeScene.h"
#include "BattleScene.h"
#include "LoadingLayer.h"
#include "MemberStatusBox.h"

#include "BGMPlayer.h"

HomeScene::HomeScene() = default;
HomeScene::~HomeScene() = default;

bool HomeScene::init()
{
    BaseScene::init();
    
    _partyList = getChildByName<PageView*>("PageView");
    getPartyList()->setBounceEnabled(true);
    getPartyList()->removeAllItems();
    
    setPartyMembers();
    
    auto menu = getChildByName("Menu");
    auto battleButton = menu->getChildByName<Button*>("Battle");
    BaseScene::onTouch(battleButton, [&](Ref* ref){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
        this->scheduleOnce([&](float dt){
            auto scene = BattleScene::createScene();
            auto fade = TransitionFade::create(2.0f, scene);
            Director::getInstance()->replaceScene(fade);
        }, 2.0f, "loading");
        auto loading = LoadingLayer::create();
        addChild(loading);
    });
    
    return true;
}

void HomeScene::onEnter()
{
    BaseScene::onEnter();
    
//    BGMPlayer::stopAll();
//    BGMPlayer::play("Sounds/pumpkin_dance.mp3");
}

void HomeScene::setPartyMembers()
{
    for (auto i = 1; i <= 3; i++) {
        auto member = std::make_shared<MemberStatusBox>();
        member->appendTo(getPartyList(), i);
        _party.push_back(member);
    }
}


