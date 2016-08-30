//
//  BattleUnit.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/08/25.
//
//

#include "BattleUnit.h"
#include "UnitData.h"
#include "BattleCommand.h"

#include "ImageManager.h"
#include "BGMPlayer.h"

using BattleCommands = std::vector<std::shared_ptr<BattleCommand>>;

void BattleUnit::init()
{
    setName();
    _hp = getHPMax();
    auto& data = getUnitData();
    _apMax = data.ap;
    setHP();
    setElementColor();
}

void BattleUnit::setAvatar(Node* node)
{
    auto filePath = "Images/" + getUnitData().code + ".png";
    _avatar = ImageManager::create(filePath);
    getAvatar()->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    node->removeAllChildren();
    node->addChild(getAvatar());
}

void BattleUnit::setElementColor()
{
    auto bgImage = getCsb()->getChildByName<ImageView*>("BgImage");
    bgImage->setColor(elementCodes.at(getUnitData().element).color);
}

void BattleUnit::setName()
{
    auto& data = getUnitData();
    auto name = getCsb()->getChildByName<Text*>("Name");
    name->setString(data.name);
}

void BattleUnit::setHP()
{
    auto hpNode = getCsb()->getChildByName("HP");
    auto hpBar = hpNode->getChildByName<LoadingBar*>("Bar");
    hpBar->setPercent(getHpPercent());
    std::stringstream hpSS;
    hpSS << " HP: ";
    hpSS << getHP();
    hpSS << " / ";
    hpSS << getHPMax();
    auto hpLabel = hpNode->getChildByName<Text*>("Label");
    hpLabel->setString(hpSS.str());
}

void BattleUnit::setAP()
{
    auto& data = getUnitData();
    _apMax = data.ap;
    auto apLabel = getCsb()->getChildByName<Text*>("APLabel");
    apLabel->setString("[AP:" + std::to_string(getAP()) + "/" + std::to_string(getAPMax()) + "]");
    for (auto i = 0; i < 5; i++) {
        auto ap = getCsb()->getChildByName<Button*>("AP_" + std::to_string(i + 1));
        if (i < getAPMax()) {
            ap->setBright(i < getAP());
        } else {
            ap->setVisible(false);
        }
    }
}

void BattleUnit::attack()
{
    auto point = -60;
    if (isEnemy()) { point *= -1; }
    auto jump = JumpBy::create(0.2f, Vec2(point, 0), 30, 1);
    auto wait = DelayTime::create(0.4f);
    auto finish = CallFunc::create([&]{
    });
    auto action = Sequence::create(jump, wait, jump->reverse(), finish, nullptr);
    getAvatar()->runAction(action);
}

const int BattleUnit::getHPMax()
{
    return getUnitData().hp + getWeaponData().hp;
}

const int BattleUnit::getAtk()
{
    return getUnitData().attack + getWeaponData().attack;
}

void BattleUnit::damaged(const int damage, const bool weak, const WeaponType weaponType)
{
    auto particleAnimation = CallFuncN::create([&, weaponType](Node* node){
        auto fileName = "Particles/attack_" + weaponCodes.at(weaponType).code + ".plist";
        if (FileUtils::getInstance()->isFileExist(fileName)) {
            auto particle = ParticleSystemQuad::create(fileName);
            particle->setPosition(getRandomPosition(node));
            particle->setRotationSkewY(-180.0f);
            particle->setScale(1.0f);
            node->addChild(particle);
            particle->setAutoRemoveOnFinish(true);
        };
    });
    auto labelAnimation = CallFuncN::create([&, damage, weak](Node* node){
        auto damageLabel = TextBMFont::create(std::to_string(damage), "Fonts/DamageLabel.fnt");
        damageLabel->setPosition(getRandomPosition(node));
        damageLabel->setScale(0.5f);
        node->addChild(damageLabel);
        animationLabel(damageLabel);
        if (weak) {
            auto weakLabel = TextBMFont::create("Weak Point!!", "Fonts/BasicLabel.fnt");
            weakLabel->setScale(0.5f);
            auto size = node->getContentSize();
            auto pos = Vec2(size.width / 2, size.height / 2);
            weakLabel->setPosition(pos);
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

void BattleUnit::healed(const int heal)
{
    auto particleAnimation = CallFuncN::create([&](Node* node){
        auto fileName = "Particles/heal_0.plist";
        if (FileUtils::getInstance()->isFileExist(fileName)) {
            auto particle = ParticleSystemQuad::create(fileName);
            particle->setPosition(getRandomPosition(node));
            particle->setRotationSkewY(-180.0f);
            particle->setScale(1.0f);
            node->addChild(particle);
            particle->setAutoRemoveOnFinish(true);
        };
    });
    auto labelAnimation = CallFuncN::create([&, heal](Node* node){
        auto healLabel = TextBMFont::create(std::to_string(heal), "Fonts/HealLabel.fnt");
        healLabel->setPosition(getRandomPosition(node));
        healLabel->setScale(0.5f);
        node->addChild(healLabel);
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

const ElementType BattleUnit::getElementType()
{
    return getUnitData().element;
}

const WeaponType BattleUnit::getWeaponType()
{
    return getWeaponData().type;
}

const Vec2 BattleUnit::getRandomPosition(const Node* node)
{
    auto size = node->getContentSize();
    auto x = random(size.width / 3, size.width / 3 * 2);
    auto y = random(size.height / 3, size.height / 3 * 2);
    auto pos = Vec2(x, y);
    return pos;
}

void BattleUnit::animationLabel(TextBMFont* label)
{
    auto jump   = JumpBy::create(0.3f, Point(0, 0), 30, 2);
    auto wait   = DelayTime::create(0.4f);
    auto finish = CallFuncN::create([&](Node* node){
        node->removeFromParent();
    });
    auto action = Sequence::create(jump, wait, finish, nullptr);
    label->runAction(action);
}

const UnitData& BattleUnit::getUnitData() const
{
    if (isEnemy()) {
        return enemyUnitDatas.at(getUnitId());
    } else {
        return partyUnitDatas.at(getUnitId());
    }
}

const WeaponData& BattleUnit::getWeaponData() const
{
    return weaponDatas.at(getWeaponId());
}
