//
//  BattleScene.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/06/09.
//
//

#include "BattleScene.h"
#include "HomeScene.h"
#include "LoadingLayer.h"
#include "MemberListBox.h"
#include "Enemy.h"

#include "ImageManager.h"
#include "BGMPlayer.h"

BattleScene::BattleScene() = default;
BattleScene::~BattleScene() = default;

bool BattleScene::init()
{
    BaseScene::init();
    
    auto menu = getChildByName("Menu");
    auto startButton = menu->getChildByName<Button*>("Start");
    BaseScene::onTouch(startButton, [&](Ref* ref){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
        playerAttack();
    });
    auto escapeButton = menu->getChildByName<Button*>("Escape");
    BaseScene::onTouch(escapeButton, [&](Ref* ref){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
        this->scheduleOnce([&](float dt){
            auto scene = HomeScene::createScene();
            auto fade = TransitionFade::create(2.0f, scene);
            Director::getInstance()->replaceScene(fade);
        }, 3.0f, "loading");
        auto loading = LoadingLayer::create();
        addChild(loading);
    });
    _partyList = getChildByName<ListView*>("ListView");
    getPartyList()->setBounceEnabled(false);
    getPartyList()->setScrollBarEnabled(false);
    getPartyList()->removeAllItems();

    return true;
}

void BattleScene::onEnter()
{
    BaseScene::onEnter();
    
    BGMPlayer::stopAll();
    BGMPlayer::play("Sounds/PerituneMaterial_Raid2.mp3");
    
    setPartyMembers();
    setEnemys();
}

void BattleScene::setPartyMembers()
{
    auto window = getChildByName("Window");
    for (auto i = 1; i <= 4; i++) {
        auto key = "Character_" + std::to_string(i);
        auto member = std::make_shared<MemberListBox>();
        member->appendTo(getPartyList(), i, window->getChildByName<ImageView*>(key));
        _party.push_back(member);
    }
}

void BattleScene::setEnemys()
{
    auto window = getChildByName("Window");
    for (auto i = 1; i <= 3; i++) {
        auto key = "Enemy_" + std::to_string(i);
        auto enemy = std::make_shared<Enemy>();
        enemy->appendTo(window->getChildByName(key), i, i);
        _enemys.push_back(enemy);
    }
}

void BattleScene::playerAttack()
{
    Vector<FiniteTimeAction*> actions;
    for (auto& member : getParty()) {
        actions.pushBack(CallFunc::create([&, member](){ member->attack(); }));
        actions.pushBack(DelayTime::create(0.2f));
        actions.pushBack(CallFunc::create([&, member](){ _enemys[0]->damaged(member->getAtk()); }));
        actions.pushBack(DelayTime::create(0.6f));
    }
    this->runAction(Sequence::create(actions));
}

