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
#include "ItemListBoard.h"
#include "WeaponListBoard.h"
#include "PlayerBase.h"
#include "CommonData.h"

#include "BGMPlayer.h"

HomeScene::HomeScene() = default;
HomeScene::~HomeScene() = default;

bool HomeScene::init()
{
    BaseScene::init();
    
    _partyList = getChildByName<PageView*>("PageView");
    _itemListBoard = std::make_unique<ItemListBoard>(this, CSLoader::createNode("Csbs/Home/ItemListBoard.csb"));
    _weaponListBoard = std::make_unique<WeaponListBoard>(this, CSLoader::createNode("Csbs/Home/WeaponListBoard.csb"));

    setUIParts();
    
    return true;
}

void HomeScene::onEnter()
{
    BaseScene::onEnter();
    
    BGMPlayer::play("Sounds/no_1_Clowns_Party.mp3");
}

void HomeScene::onEnterTransitionDidFinish()
{
    BaseScene::onEnterTransitionDidFinish();
    
    auto image = getChildByName<ImageView*>("BgMain");
    auto rotate = RotateBy::create(60.0f, 360);
    auto action = RepeatForever::create(rotate);
    image->setRotation(0);
    image->runAction(action);
    
    auto arrowR = getChildByName<TextBMFont*>("Arrow_R");
    auto moveR = MoveBy::create(0.6f, Vec2(15, 0));
    auto seqR = Sequence::create(moveR, moveR->reverse(), nullptr);
    auto actionR = RepeatForever::create(seqR);
    arrowR->runAction(actionR);
    
    auto arrowL = getChildByName<TextBMFont*>("Arrow_L");
    auto moveL = MoveBy::create(0.6f, Vec2(-15, 0));
    auto seqL = Sequence::create(moveL, moveL->reverse(), nullptr);
    auto actionL = RepeatForever::create(seqL);
    arrowL->runAction(actionL);
}

void HomeScene::setPartyMembers()
{
    _party.clear();
    getPartyList()->removeAllItems();
    for (auto i = 1; i <= 3; i++) {
        auto member = std::make_shared<MemberStatusBox>();
        member->appendTo(getPartyList(), i);
        member->setAction("LevelUp", [&, i](Ref* ref){
            BGMPlayer::play2d("Sounds/se_ok.mp3");
        });
        member->setAction("Equip", [&, i](Ref* ref){
            BGMPlayer::play2d("Sounds/se_ok.mp3");
            getWeaponListBoard()->setWeaponList(i);
        });
        _party.push_back(member);
    }
}

void HomeScene::setUIParts()
{
    getPartyList()->setBounceEnabled(true);
    getPartyList()->addEventListener([&](Ref* ref, PageView::EventType eventType){
        if(eventType == PageView::EventType::TURNING){
            auto page = static_cast<int>(static_cast<PageView*>(ref)->getCurrentPageIndex());
            auto node = getChildByName("Party");
            for (auto i = 0; i < 3; i++) {
                auto key = "Member_" + std::to_string(i + 1);
                auto avatar = node->getChildByName(key)->getChildByName<ImageView*>("Avatar");
                if (i == page) {
                    avatar->setColor(Color3B::WHITE);
                } else {
                    avatar->setColor(Color3B(136, 136, 136));
                }
            }
        }
    });

    auto node = getChildByName("Party");
    for (auto i = 0; i < 3; i++) {
        auto key = "Member_" + std::to_string(i + 1);
        auto avatar = node->getChildByName(key)->getChildByName<ImageView*>("Avatar");
        BaseScene::onTouch(avatar, [&, i](Ref* ref){
            BGMPlayer::play2d("Sounds/se_ok.mp3");
            getPartyList()->scrollToItem(i);
        });
    }

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
    
    auto itemButton = menu->getChildByName<Button*>("Item");
    BaseScene::onTouch(itemButton, [&](Ref* ref){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
        getItemListBoard()->setItemList(ItemType::BATTLE);
    });
}
