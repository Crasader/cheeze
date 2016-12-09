//
//  BattleUnit.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/08/25.
//
//

#include "BattleUnit.h"
#include "UnitData.h"
#include "ItemData.h"
#include "CommonData.h"
#include "BattleCommand.h"

#include "ImageManager.h"
#include "BGMPlayer.h"

using BattleCommands = std::vector<std::shared_ptr<BattleCommand>>;

void BattleUnit::init()
{
    setName();
    _hp = getHPMax();
    _apMax = getUnitData().ap;
    setHP();
    setElementColor();
}

void BattleUnit::setAvatar(Node* node)
{
    auto filePath = "Images/Character/" + getUnitData().code + ".png";
    _avatar = ImageManager::create(filePath);
    getAvatar()->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    getAvatar()->setVisible(false);
    node->removeAllChildren();
    node->addChild(getAvatar());
}

void BattleUnit::setElementColor()
{
    auto bgImage = getCsb()->getChildByName<ImageView*>("BgImage");
    bgImage->setColor(elementCodes.at(getUnitData().element).bg_color);
    auto icon = getCsb()->getChildByName<ImageView*>("Element");
    ImageManager::loadTexture(icon, "Images/UIParts/icon_" + elementCodes.at(getUnitData().element).code + ".png");
}

void BattleUnit::setName()
{
    auto& data = getUnitData();
    auto name = getCsb()->getChildByName<TextBMFont*>("Name");
    name->setString(data.name);
}

void BattleUnit::setHP()
{
    auto hpNode = getCsb()->getChildByName("HP");
    auto hpBar = hpNode->getChildByName<LoadingBar*>("Bar");
    hpBar->setPercent(getHpPercent());
}

void BattleUnit::setAP()
{
    auto& data = getUnitData();
    _apMax = data.ap;
    for (auto i = 0; i < 5; i++) {
        auto ap = getCsb()->getChildByName<TextBMFont*>("AP_" + std::to_string(i + 1));
        if (i < getAPMax()) {
            ap->setString("★");
            if (i < getAP()) {
                ap->setColor(Color3B(255, 204, 0));
            } else {
                ap->setColor(Color3B(204, 204, 204));
            }
        } else {
            ap->setString("");
        }
    }
}

const int BattleUnit::getHPMax()
{
    return getUnitData().hp + getWeaponData().hp;
}

const int BattleUnit::getAtk()
{
    return getUnitData().attack + getWeaponData().attack;
}

const ElementType BattleUnit::getElementType()
{
    return getUnitData().element;
}

const WeaponType BattleUnit::getWeaponType()
{
    return getWeaponData().type;
}

const UnitAnimationType BattleUnit::getAnimationType()
{
    return getUnitData().animation;
}

const Vec2 BattleUnit::getRandomPosition(const Node* node)
{
    auto size = node->getContentSize();
    auto x = random(-size.width / 6, size.width / 6);
    auto y = random(size.height / 6, size.height / 6 * 2);
    auto pos = Vec2(x, y);
    return pos;
}

void BattleUnit::animationLabel(TextBMFont* label, const int x)
{
    auto jump   = JumpBy::create(0.3f, Point(x, 0), 30, 2);
    auto wait   = DelayTime::create(0.4f);
    auto finish = CallFuncN::create([&](Node* node){
        node->removeFromParent();
    });
    auto action = Sequence::create(jump, wait, finish, nullptr);
    label->runAction(action);
}

void BattleUnit::updateAP(const int point, const bool animation)
{
    _ap += point;
    if(_ap > getAPMax()) _ap = getAPMax();
    auto labelAnimation = CallFuncN::create([&, point, animation](Node* node){
        if (animation) {
            if (point != 0) {
                auto count = point;
                auto x = 0;
                if (point < 0) {
                    count *= -1;
                    x = 100;
                    if (isEnemy()) {
                        x *= -1;
                    }
                }
                std::stringstream ss;
                for (auto i = 0; i < count; i++) {
                    ss << "★";
                }
                auto apLabel = TextBMFont::create(ss.str(), "Fonts/BasicLabel.fnt");
                apLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
                apLabel->setPosition(Vec2::ZERO);
                apLabel->setScale(0.5f);
                if (point > 0) {
                    apLabel->setColor(Color3B(255, 204, 0));
                } else {
                    apLabel->setColor(Color3B(255, 68, 68));
                }
                node->getParent()->addChild(apLabel);
                animationLabel(apLabel, x);
            }
        }
    });
    auto wait = DelayTime::create(0.1f);
    auto finish = CallFuncN::create([&, point](Node* node){
        setAP();
    });
    auto action = Sequence::create(labelAnimation, wait, finish, nullptr);
    getAvatar()->runAction(action);
}

void BattleUnit::attack()
{
}

void BattleUnit::damaged(const int damage, const bool weak, const WeaponType weaponType)
{
}

void BattleUnit::healed(const int heal)
{
}

void BattleUnit::turnChange()
{
}

const UnitData& BattleUnit::getUnitData() const
{
    return unitDatas.at(getUnitId());
}

const WeaponData& BattleUnit::getWeaponData() const
{
    return weaponDatas.at(getWeaponId());
}
