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
    auto filePath = "Images/Character/" + getUnitData().code + ".png";
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
    auto apLabel = getCsb()->getChildByName<TextBMFont*>("APLabel");
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

const Vec2 BattleUnit::getRandomPosition(const Node* node)
{
    auto size = node->getContentSize();
    auto x = random(-size.width / 6, size.width / 6);
    auto y = random(size.height / 6, size.height / 6 * 2);
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

void BattleUnit::updateAP(const int point)
{
    _ap += point;
    if(_ap > getAPMax()) _ap = getAPMax();
    auto labelAnimation = CallFuncN::create([&, point](Node* node){
        if (point != 0) {
            std::stringstream ss;
            ss << "AP";
            if (point > 0) {
                ss << "+";
            }
            ss << point;
            auto apLabel = TextBMFont::create(ss.str(), "Fonts/BasicLabel.fnt");
            apLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
            apLabel->setPosition(Vec2::ZERO);
            apLabel->setScale(0.5f);
            if (point > 0) {
                ss << "+";
                apLabel->setColor(Color3B(136, 238, 255));
            } else {
                apLabel->setColor(Color3B(255, 136, 136));
            }
            node->getParent()->addChild(apLabel);
            animationLabel(apLabel);
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
