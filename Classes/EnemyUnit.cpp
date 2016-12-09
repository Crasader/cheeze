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

void EnemyUnit::appendTo(Node* node, const int position, const float scale)
{
    if (getUnitId() < 1) {
        getCsb()->setVisible(false);
        return;
    }
    for (auto& child : getCsb()->getChildren()) {
        child->setVisible(false);
    }
    setAvatar(node);
    getAvatar()->setScale(scale);
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
        if (isSkill()) {
            BGMPlayer::play2d("Sounds/se_skill_ghost_default.mp3");
            auto particle = ParticleSystemQuad::create("Particles/skill_boot.plist");
            getCsb()->addChild(particle);
            auto callback = CallFuncN::create([&](Node* node){
                node->setPosition(Vec2::ZERO);
                node->setScale(0.75f);
                static_cast<ParticleSystemQuad*>(node)->setAutoRemoveOnFinish(true);
            });
            particle->runAction(callback);
        }
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
            weakLabel->setScale(1.0f);
            auto size = node->getContentSize();
            auto pos = Vec2(size.width / 2, size.height * 3 / 4);
            weakLabel->setPosition(pos);
            weakLabel->setFlippedX(true);
            switch (getElementType()) {
                case ElementType::FIRE :
                    weakLabel->setColor(elementCodes.at(ElementType::WATER).text_color);
                    break;
                case ElementType::WIND :
                    weakLabel->setColor(elementCodes.at(ElementType::FIRE).text_color);
                    break;
                case ElementType::WATER :
                    weakLabel->setColor(elementCodes.at(ElementType::WIND).text_color);
                    break;
                default:
                    break;
            }
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
        if (isDead()) {
            getAvatar()->runAction(FadeOut::create(0.4f));
            getCsb()->setVisible(false);
        }
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

void EnemyUnit::animationAppear()
{
    Vector<FiniteTimeAction*> actions;
    switch (getAnimationType()) {
        case UnitAnimationType::WALK :
            actions.pushBack( CallFuncN::create([&](Node* node){ node->setPosition(Vec2(-450, 0)); }) );
            actions.pushBack( CallFuncN::create([&](Node* node){ node->setVisible(true); }) );
            actions.pushBack( DelayTime::create(random(0.0f, 0.5f)) );
            actions.pushBack( JumpBy::create(1.0f, Vec2(450, 0), 30, 5) );
            break;
        case UnitAnimationType::FLY :
            actions.pushBack( CallFuncN::create([&](Node* node){ node->setPosition(Vec2(-600, 960)); }) );
            actions.pushBack( CallFuncN::create([&](Node* node){ node->setVisible(true); }) );
            actions.pushBack( DelayTime::create(random(0.4f, 0.9f)) );
            actions.pushBack( JumpTo::create(0.6f, Vec2::ZERO, -120, 1) );
            break;
        case UnitAnimationType::FALL :
            actions.pushBack( CallFuncN::create([&](Node* node){ node->setPosition(Vec2(-80, 960)); }) );
            actions.pushBack( CallFuncN::create([&](Node* node){ node->setVisible(true); }) );
            actions.pushBack( DelayTime::create(0.8f) );
            actions.pushBack( JumpBy::create(0.5f, Vec2(60, -960), 30, 1) );
            actions.pushBack( JumpBy::create(0.2f, Vec2(20, 0), 60, 1) );
            break;
        default:
            break;
    }
    actions.pushBack( CallFunc::create([&](){
        for (auto& child : getCsb()->getChildren()) {
            child->setVisible(true);
        }
    }) );
    getAvatar()->runAction(Sequence::create(actions));
}
