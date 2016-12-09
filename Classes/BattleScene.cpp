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

#include "Player.h"
#include "BGMPlayer.h"
#include "ImageManager.h"

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
    auto menuButton = menu->getChildByName<Button*>("Menu");
    BaseScene::onTouch(menuButton, [&](Ref* ref){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
        showMenuLayer();
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
    _skillBoard = getChildByName("SkillBoard");
    hideSkillBoard();
    _menuLayer = getChildByName("MenuLayer");
    hideMenuLayer();

    return true;
}

void BattleScene::onEnter()
{
    BaseScene::onEnter();
    
    BGMPlayer::stopAll();
    BGMPlayer::play("Sounds/no_3_Trick_or_Treat.mp3");

    setPartyMembers();
    setEnemys();
    nextTurn();
}

void BattleScene::onEnterTransitionDidFinish()
{
    BaseScene::onEnterTransitionDidFinish();

    animationNextRound();
    animationAppearEnemys();
}

void BattleScene::setPartyMembers()
{
    auto player = Player::getInstance();
    auto tmpl = CSLoader::createNode("Csbs/Battle/PartyUnit.csb")->getChildByName<Widget*>("Template");
    tmpl->retain();
    auto window = getChildByName("Window");
    for (auto i = 1; i <= 3; i++) {
        auto key = "Character_" + std::to_string(i);
        auto csb = tmpl->clone();
        auto weaponId = static_cast<WeaponId>(player->getCharacterWeaponId(i));
        auto partyUnit = std::make_shared<PartyUnit>(i, weaponId, csb);
        partyUnit->appendTo(getPartyList(), i, window->getChildByName<ImageView*>(key));
        _party.push_back(partyUnit);
    }
    tmpl->release();
}

void BattleScene::setEnemys()
{
    _enemys.clear();
    _round++;
    auto battleStatus = getChildByName("BattleStatus");
    auto roundLabel = battleStatus->getChildByName<TextBMFont*>("Round");
    roundLabel->setString("Trick " + std::to_string(_round) + "/" + std::to_string(3));

    auto window = getChildByName("Window");
    BGMPlayer::play("Sounds/no_3_Trick_or_Treat.mp3");
    for (auto i = 1; i <= 3; i++) {
        auto key = "Enemy_" + std::to_string(i);
        auto csb = CSLoader::createNode("Csbs/Battle/EnemyUnit.csb");
        auto no = 10 + random(1, 9);
        auto scale = 0.45f;
        if (_round % 3 == 0 && i == 3) {
            BGMPlayer::play("Sounds/no_2_Pumpkin_King_Appears.mp3");
            no = 20;
            scale = 0.75f;
        }
        auto enemy = std::make_shared<EnemyUnit>(no, csb);
        enemy->appendTo(window->getChildByName(key), i, scale);
        _enemys.push_back(enemy);
    }
}

void BattleScene::playerAttack(const int position)
{
    setUntouchable();
    Vector<FiniteTimeAction*> actions;
    auto attacker = getParty().at(position);
    if (!attacker->isDead()) {
        actions.pushBack(CallFunc::create([&, attacker](){ attacker->attack(); }));
        actions.pushBack(DelayTime::create(0.2f));
        auto& command = attacker->getBattleCommand();
        if (!command->isAttack()) {
            actions.pushBack(CallFunc::create([&, command](){ showSkillBoard(command->getName()); }));
        }
        auto& effects = command->getEffects();
        for (auto& effect : effects) {
            switch (effect.type) {
                case EffectType::DAMAGE :
                    for (auto& enemy : selectTargetEnemys(effect.target)) {
                        auto damage = attacker->getAtk() * random(effect.power[0], effect.power[1]) / 100.0f;
                        auto element = effect.element;
                        if (element == ElementType::SELF) {
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
                        auto heal = attacker->getAtk() * random(effect.power[0], effect.power[1]) / 200.0f;
                        actions.pushBack(CallFunc::create([&, member, heal](){
                            member->healed(heal);
                        }));
                        actions.pushBack(DelayTime::create(0.2f));
                    }
                    break;
                case EffectType::RESURRECTION :
                    for (auto& member : getParty()) {
                        auto heal = attacker->getAtk() * random(effect.power[0], effect.power[1]) / 200.0f;
                        actions.pushBack(CallFunc::create([&, member, heal](){
                            member->healed(heal);
                            member->getAvatar()->setVisible(true);
                            member->getAvatar()->runAction(FadeIn::create(0.5f));
                        }));
                        actions.pushBack(DelayTime::create(0.2f));
                    }
                    break;
                case EffectType::AP_UP :
                    for (auto& member : selectTargetParty(effect.target, attacker)) {
                        actions.pushBack(CallFunc::create([&, member, effect](){
                            member->updateAP(random(effect.power[0], effect.power[1]), true);
                            BGMPlayer::play2d("Sounds/se_ap_up.mp3");
                        }));
                        actions.pushBack(DelayTime::create(0.2f));
                    }
                    break;
                case EffectType::AP_DOWN :
                    for (auto& member : selectTargetEnemys(effect.target)) {
                        actions.pushBack(CallFunc::create([&, member, effect](){
                            member->updateAP(random(effect.power[0], effect.power[1]) * -1, true);
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
            } else {
                attacker->updateTP();
                attacker->updateAP(-ap);
            }
        }));
        actions.pushBack(DelayTime::create(0.6f));
        if (!command->isAttack()) {
            actions.pushBack(CallFunc::create([&](){ hideSkillBoard(); }));
        }
    }
    auto next = position + 1;
    if (getParty().size() == next) {
        actions.pushBack(DelayTime::create(0.4f));
        actions.pushBack(CallFunc::create([&](){
            enemyAttack();
        }));
    } else {
        actions.pushBack(CallFunc::create([&, next](){
            playerAttack(next);
        }));
    }
    this->runAction(Sequence::create(actions));
}

void BattleScene::enemyAttack(const int position)
{
    Vector<FiniteTimeAction*> actions;
    auto attacker = getEnemys().at(position);
    if (!attacker->isDead()) {
        actions.pushBack(CallFunc::create([&, attacker](){ attacker->attack(); }));
        actions.pushBack(DelayTime::create(0.2f));
        auto& command = attacker->getBattleCommand();
        if (!command->isAttack()) {
            actions.pushBack(CallFunc::create([&, command](){ showSkillBoard(command->getName()); }));
        } else {
            actions.pushBack(CallFunc::create([&](){ hideSkillBoard(); }));
        }
        auto& effects = command->getEffects();
        for (auto& effect : effects) {
            switch (effect.type) {
                case EffectType::DAMAGE :
                    for (auto& target : selectTargetParty(effect.target, nullptr)) {
                        auto damage = attacker->getAtk() * random(effect.power[0], effect.power[1]) / 100.0f;
                        auto element = effect.element;
                        if (element == ElementType::SELF) {
                            element = attacker->getElementType();
                        }
                        auto weak = isWeakElement(element, target->getElementType());
                        if (weak) {
                            damage *= 1.5f;
                        }
                        actions.pushBack(CallFunc::create([&, target, damage, weak, attacker](){
                            target->damaged(damage, weak, attacker->getWeaponType());
                        }));
                        actions.pushBack(DelayTime::create(0.2f));
                    }
                    break;
                case EffectType::AP_DOWN :
                    for (auto& member : selectTargetParty(effect.target, nullptr)) {
                        actions.pushBack(CallFunc::create([&, member, effect](){
                            member->updateAP(random(effect.power[0], effect.power[1]) * -1, true);
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
        if (!command->isAttack()) {
            actions.pushBack(CallFunc::create([&](){ hideSkillBoard(); }));
        }
    }
    auto next = position + 1;
    if (getEnemys().size() == next) {
        if (getAliveEnemys().size() <= 0) {
            actions.pushBack(DelayTime::create(0.2f));
            actions.pushBack(CallFunc::create([&](){ animationNextRound(); }));
            actions.pushBack(DelayTime::create(1.0f));
            actions.pushBack(CallFunc::create([&](){ setEnemys(); }));
            actions.pushBack(CallFunc::create([&](){ animationAppearEnemys(); }));
            actions.pushBack(DelayTime::create(0.4f));
        }
        actions.pushBack(DelayTime::create(0.4f));
        actions.pushBack(CallFunc::create([&](){
            BGMPlayer::play2d("Sounds/se_ap_up.mp3");
            nextTurn();
        }));
    } else {
        actions.pushBack(CallFunc::create([&, next](){
            enemyAttack(next);
        }));
    }
    this->runAction(Sequence::create(actions));
}

void BattleScene::animationNextRound()
{
    auto rankUpLabel = getChildByName<TextBMFont*>("LabelRound")->clone();
    rankUpLabel->setVisible(true);
    rankUpLabel->setScale(5.0f);
    this->addChild(rankUpLabel);
    auto rotate = RotateBy::create(0.9f, 1800);
    auto scale1 = ScaleTo::create(0.6f, 0.0f);
    auto scale2 = ScaleTo::create(0.3f, 1.0f);
    auto scale  = Sequence::create(scale1, scale2, nullptr);
    auto spawn  = Spawn::create(rotate, scale, nullptr);
    auto wait   = DelayTime::create(1.0f);
    auto fade   = FadeOut::create(0.4f);
    auto finish = CallFuncN::create([&](Node* node){
        node->removeFromParent();
    });
    auto action = Sequence::create(spawn, wait, fade, finish, nullptr);
    rankUpLabel->runAction(action);

    auto window = getChildByName("Window");
    auto bgImage = window->getChildByName<ImageView*>("Background");
    auto move = MoveBy::create(1.0f, Vec2(300, 0));
    bgImage->runAction(move);
    
    for (auto& unit : getParty()) {
        unit->animationAppear();
    }
}

void BattleScene::animationAppearEnemys()
{
    for (auto& enemy : getEnemys()) {
        enemy->animationAppear();
    }
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
        if (getAliveParty().size() <= 0) {
            this->scheduleOnce([&](float dt){
                auto scene = HomeScene::createScene();
                auto fade = TransitionFade::create(2.0f, scene);
                Director::getInstance()->replaceScene(fade);
            }, 3.0f, "loading");
            auto loading = LoadingLayer::create();
            loading->gameOver();
            addChild(loading);
            return;
        } else {
            setTouchable();
        }
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
    if (max < 0) {
        return targetMembers;
    }
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
            _targetPosition = random(0, max);
            targetMembers.push_back(aliveMembers.at(_targetPosition));
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
        case TargetType::SAME :
            targetMembers.push_back(aliveMembers.at(_targetPosition));
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
            _targetPosition = random(0, max);
            targetEnemys.push_back(aliveEnemys.at(_targetPosition));
            break;
        case TargetType::SAME :
            targetEnemys.push_back(aliveEnemys.at(_targetPosition));
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
        case ElementType::WIND :
            if (defType == ElementType::WATER) {
                check = true;
            }
            break;
        default:
            break;
    }
    return check;
}
