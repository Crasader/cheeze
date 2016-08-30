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
#include "PartyUnit.h"
#include "EnemyUnit.h"
#include "BattleCommand.h"
#include "UnitData.h"

#include "ImageManager.h"
#include "BGMPlayer.h"

using Party = std::vector<std::shared_ptr<PartyUnit>>;
using Enemys = std::vector<std::shared_ptr<EnemyUnit>>;

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
    
    _untouchable = getChildByName("Untouchable");
    setTouchable();

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
    auto tmpl = CSLoader::createNode("Csbs/Battle/PartyUnit.csb")->getChildByName<Widget*>("Template");
    tmpl->retain();
    auto window = getChildByName("Window");
    for (auto i = 1; i <= 4; i++) {
        auto key = "Character_" + std::to_string(i);
        auto csb = tmpl->clone();
        auto partyUnit = std::make_shared<PartyUnit>(i, i, csb);
        partyUnit->appendTo(getPartyList(), i, window->getChildByName<ImageView*>(key));
        _party.push_back(partyUnit);
    }
    tmpl->release();
}

void BattleScene::setEnemys()
{
    auto window = getChildByName("Window");
    for (auto i = 1; i <= 3; i++) {
        auto key = "Enemy_" + std::to_string(i);
        auto csb = CSLoader::createNode("Csbs/Battle/EnemyUnit.csb");
        auto enemy = std::make_shared<EnemyUnit>(i, csb);
        enemy->appendTo(window->getChildByName(key), i);
        _enemys.push_back(enemy);
    }
}

void BattleScene::playerAttack()
{
    setUntouchable();
    Vector<FiniteTimeAction*> actions;
    for (auto& attacker : getAliveParty()) {
        actions.pushBack(CallFunc::create([&, attacker](){ attacker->attack(); }));
        actions.pushBack(DelayTime::create(0.2f));
        auto& command = attacker->getBattleCommand();
        auto& effects = command->getEffects();
        for (auto& effect : effects) {
            switch (effect.type) {
                case EffectType::DAMAGE :
                    for (auto& enemy : selectTargetEnemys(effect.target)) {
                        auto damage = attacker->getAtk() * random(effect.power[0], effect.power[1]) / 100.0f;
                        auto element = effect.element;
                        if (element == ElementType::WEAPON) {
                            element = attacker->getElementType();
                        }
                        auto weak = isWeakElement(element, enemy->getElementType());
                        if (weak) {
                            damage *= 1.5f;
                        }
                        actions.pushBack(CallFunc::create([&, enemy, damage, weak, attacker](){
                            enemy->damaged(damage, weak, attacker->getWeaponType());
                        }));
                        actions.pushBack(DelayTime::create(0.2f));
                    }
                    break;
                case EffectType::HEAL :
                    for (auto& member : selectTargetParty(effect.target, attacker)) {
                        auto heal = attacker->getAtk() * random(effect.power[0], effect.power[1]) / 100.0f;
                        actions.pushBack(CallFunc::create([&, member, heal](){
                            member->healed(heal);
                        }));
                        actions.pushBack(DelayTime::create(0.2f));
                    }
                    break;
                default:
                    break;
            }
        }
        actions.pushBack(CallFunc::create([&, attacker, command](){
            auto ap = command->getAp();
            if (ap == 100) {
                attacker->updateTP(-ap);
                attacker->updateAP(-1);
            } else {
                attacker->updateTP();
                attacker->updateAP(-ap);
            }
        }));
        actions.pushBack(DelayTime::create(0.6f));
    }
    actions.pushBack(DelayTime::create(0.4f));
    actions.pushBack(CallFunc::create([&](){
        enemyAttack();
    }));
    this->runAction(Sequence::create(actions));
}

void BattleScene::enemyAttack()
{
    Vector<FiniteTimeAction*> actions;
    for (auto& attacker : getAliveEnemys()) {
        actions.pushBack(CallFunc::create([&, attacker](){ attacker->attack(); }));
        actions.pushBack(DelayTime::create(0.2f));
        auto& command = attacker->getBattleCommand();
        auto& effects = command->getEffects();
        for (auto& effect : effects) {
            switch (effect.type) {
                case EffectType::DAMAGE :
                    for (auto& target : selectTargetParty(effect.target, nullptr)) {
                        auto damage = attacker->getAtk() * random(effect.power[0], effect.power[1]) / 100.0f;
                        auto element = effect.element;
                        if (element == ElementType::WEAPON) {
                            element = attacker->getElementType();
                        }
                        auto weak = isWeakElement(element, attacker->getElementType());
                        if (weak) {
                            damage *= 1.5f;
                        }
                        actions.pushBack(CallFunc::create([&, target, damage, weak, attacker](){
                            target->damaged(damage, weak, attacker->getWeaponType());
                        }));
                        actions.pushBack(DelayTime::create(0.2f));
                    }
                    break;
                default:
                    break;
            }
        }
        actions.pushBack(CallFunc::create([&, attacker, command](){
            auto ap = command->getAp();
            attacker->updateAP(-ap);
        }));
        actions.pushBack(DelayTime::create(0.6f));
    }
    actions.pushBack(DelayTime::create(0.4f));
    actions.pushBack(CallFunc::create([&](){
        nextTurn();
    }));
    this->runAction(Sequence::create(actions));
}

void BattleScene::nextTurn()
{
    Vector<FiniteTimeAction*> actions;
    actions.pushBack(CallFunc::create([&](){
        for (auto& member : getParty()) {
            member->turnChange();
        }
        for (auto& enemy : getEnemys()) {
            enemy->turnChange();
        }
        setTouchable();
    }));
    actions.pushBack(DelayTime::create(0.4f));
    this->runAction(Sequence::create(actions));
}

const Party BattleScene::getAliveParty()
{
    Party aliveMembers;
    for (auto& member : getParty()) {
        if (!member->isDead()) {
            aliveMembers.push_back(member);
        }
    }
    return aliveMembers;
}

const Enemys BattleScene::getAliveEnemys()
{
    Enemys targetEnemys;
    for (auto& enemy : getEnemys()) {
        if (!enemy->isDead()) {
            targetEnemys.push_back(enemy);
        }
    }
    return targetEnemys;
}

const Party BattleScene::selectTargetParty(const TargetType targetType, const std::shared_ptr<PartyUnit> member)
{
    Party targetMembers;
    auto& aliveMembers = getAliveParty();
    auto max = static_cast<int>(aliveMembers.size() - 1);
    auto position = 0;
    auto n = 0;
    auto damagedHP = 9999;
    switch (targetType) {
        case TargetType::ENEMY_ALL :
            for (auto& member : aliveMembers) {
                targetMembers.push_back(member);
            }
            break;
        case TargetType::ENEMY_ONE :
            targetMembers.push_back(aliveMembers.at(random(0, max)));
            break;
        case TargetType::ENEMY_RANDOM_4 :
            for (auto i = 0; i < 4; i++) {
                targetMembers.push_back(aliveMembers.at(random(0, max)));
            }
            break;
        case TargetType::PARTY_ALL :
            for (auto& member : aliveMembers) {
                targetMembers.push_back(member);
            }
            break;
        case TargetType::PARTY_ONE :
            for (auto& member : aliveMembers) {
                auto damaged = member->getHP() - member->getHPMax();
                if (damagedHP > damaged) {
                    damagedHP = damaged;
                    position = n;
                }
                n++;
            }
            targetMembers.push_back(aliveMembers.at(position));
            break;
        case TargetType::OWN :
            targetMembers.push_back(member);
            break;
        default:
            break;
    }
    return targetMembers;
}

const Enemys BattleScene::selectTargetEnemys(const TargetType targetType)
{
    Enemys targetEnemys;
    auto& aliveEnemys = getAliveEnemys();
    auto max = static_cast<int>(aliveEnemys.size() - 1);
    if (max < 0) {
        return targetEnemys;
    }
    switch (targetType) {
        case TargetType::ENEMY_ALL :
            for (auto& Enemy : aliveEnemys) {
                targetEnemys.push_back(Enemy);
            }
            break;
        case TargetType::ENEMY_ONE :
            targetEnemys.push_back(aliveEnemys.at(random(0, max)));
            break;
        case TargetType::ENEMY_RANDOM_4 :
            for (auto i = 0; i < 4; i++) {
                targetEnemys.push_back(aliveEnemys.at(random(0, max)));
            }
            break;
        default:
            break;
    }
    return targetEnemys;
}

const bool BattleScene::isWeakElement(const ElementType atkType, const ElementType defType)
{
    auto check = false;
    switch (atkType) {
        case ElementType::FIRE :
            if (defType == ElementType::WIND) {
                check = true;
            }
            break;
        case ElementType::WATER :
            if (defType == ElementType::FIRE) {
                check = true;
            }
            break;
        case ElementType::EARTH :
            if (defType == ElementType::WATER) {
                check = true;
            }
            break;
        case ElementType::WIND :
            if (defType == ElementType::EARTH) {
                check = true;
            }
            break;
        default:
            break;
    }
    return check;
}
