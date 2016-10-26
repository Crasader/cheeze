//
//  EnemyUnit.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/08/24.
//
//

#include "EnemyUnit.h"
#include "UnitData.h"
#include "BattleCommand.h"

#include "ImageManager.h"
#include "BGMPlayer.h"

#include "editor-support/cocostudio/CocoStudio.h"
using namespace cocostudio;

void EnemyUnit::appendTo(Node* node, const int position)
{
    if (getUnitId() < 1) {
        getCsb()->setVisible(false);
        return;
    }
    getCsb()->setVisible(true);
    setAvatar(node);
    getAvatar()->setScale(0.5f);
    getAvatar()->setFlippedX(true);
    setPosition(position);
    node->addChild(getCsb());
    init();
}

void EnemyUnit::init()
{
    BattleUnit::init();
    auto attackCommand = std::make_shared<BattleCommand>(commandDatas.at(0));
    addCommand(attackCommand);
    auto battleCommand = std::make_shared<BattleCommand>(getUnitData().command_data);
    addCommand(battleCommand);
    updateAP(0);
}

void EnemyUnit::attack()
{
    auto start = CallFunc::create([&]{
    });
    auto jump = JumpBy::create(0.15f, Vec2(60, 0), 30, 1);
    auto wait = DelayTime::create(0.4f);
    auto finish = CallFunc::create([&]{
    });
    auto action = Sequence::create(start, jump, wait, jump->reverse(), finish, nullptr);
    getAvatar()->runAction(action);
}

void EnemyUnit::damaged(const int damage, const bool weak, const WeaponType weaponType)
{
    auto particleAnimation = CallFuncN::create([&, weaponType](Node* node){
        auto fileName = "Particles/attack_" + weaponCodes.at(weaponType).code + ".plist";
        if (FileUtils::getInstance()->isFileExist(fileName)) {
            auto particle = ParticleSystemQuad::create(fileName);
            particle->setPosition(getRandomPosition(node));
            particle->setRotationSkewY(-180.0f);
            particle->setScale(1.0f);
            node->getParent()->addChild(particle);
            particle->setAutoRemoveOnFinish(true);
        };
    });
    auto labelAnimation = CallFuncN::create([&, damage, weak](Node* node){
        auto damageLabel = TextBMFont::create(std::to_string(damage), "Fonts/DamageLabel.fnt");
        damageLabel->setPosition(getRandomPosition(node));
        damageLabel->setScale(0.5f);
        node->getParent()->addChild(damageLabel);
        animationLabel(damageLabel);
        if (weak) {
            auto weakLabel = TextBMFont::create("Weak Point!!", "Fonts/BasicLabel.fnt");
            weakLabel->setScale(0.5f);
            auto size = node->getContentSize();
            auto pos = Vec2(size.width / 4, size.height / 4);
            weakLabel->setPosition(pos);
            weakLabel->setFlippedX(true);
            node->addChild(weakLabel);
            auto move   = MoveBy::create(0.5f, Point(0, 80));
            auto wait   = DelayTime::create(0.4f);
            auto finish = CallFuncN::create([&](Node* node){
                node->removeFromParent();
            });
            auto action = Sequence::create(move, wait, finish, nullptr);
            weakLabel->runAction(action);
        }
    });
    auto damageColor = CallFuncN::create([&](Node* node){
        node->setColor(Color3B(255, 68, 68));
    });
    auto hpBarDown = CallFunc::create([&, damage](){
        updateHP(-damage);
    });
    auto se = CallFunc::create([&]{
        BGMPlayer::play2d("Sounds/se_damage_human.mp3");
    });
    auto keepColor = DelayTime::create(0.1f);
    auto finish = CallFuncN::create([&](Node* node){
        node->setColor(Color3B(255, 255, 255));
    });
    auto action = Sequence::create(particleAnimation, labelAnimation, se, hpBarDown, damageColor, keepColor, finish, nullptr);
    getAvatar()->runAction(action);
}

void EnemyUnit::healed(const int heal)
{
    auto particleAnimation = CallFuncN::create([&](Node* node){
        auto fileName = "Particles/heal_0.plist";
        if (FileUtils::getInstance()->isFileExist(fileName)) {
            auto particle = ParticleSystemQuad::create(fileName);
            particle->setPosition(getRandomPosition(node));
            particle->setRotationSkewY(-180.0f);
            particle->setScale(1.0f);
            node->getParent()->addChild(particle);
            particle->setAutoRemoveOnFinish(true);
        };
    });
    auto labelAnimation = CallFuncN::create([&, heal](Node* node){
        auto healLabel = TextBMFont::create(std::to_string(heal), "Fonts/HealLabel.fnt");
        healLabel->setPosition(getRandomPosition(node));
        healLabel->setScale(0.5f);
        node->getParent()->addChild(healLabel);
        animationLabel(healLabel);
    });
    auto healColor = CallFuncN::create([&](Node* node){
        node->setColor(Color3B(68, 255, 68));
    });
    auto hpBarUp = CallFunc::create([&, heal](){
        updateHP(heal);
    });
    auto se = CallFunc::create([&]{
        BGMPlayer::play2d("Sounds/se_heal.mp3");
    });
    auto keepColor = DelayTime::create(0.1f);
    auto finish = CallFuncN::create([&](Node* node){
        node->setColor(Color3B(255, 255, 255));
    });
    auto action = Sequence::create(particleAnimation, labelAnimation, se, hpBarUp, healColor, keepColor, finish, nullptr);
    getAvatar()->runAction(action);
}

void EnemyUnit::turnChange()
{
    if (isDead()) {
        getAvatar()->setVisible(false);
        getCsb()->setVisible(false);
        return;
    }
    if (getCommandNumber() == 0) {
        updateAP();
    }
    if (isSkill()) {
        setCommandNumber(1);
    } else {
        setCommandNumber(0);
    }
}
