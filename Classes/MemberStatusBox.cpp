//
//  MemberStatusBox.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/08/23.
//
//

#include "MemberStatusBox.h"
#include "WeaponListBoard.h"
#include "Player.h"
#include "UnitData.h"
#include "ItemData.h"

#include "ImageManager.h"
#include "BGMPlayer.h"

#include "editor-support/cocostudio/CocoStudio.h"
using namespace cocostudio;

void MemberStatusBox::appendTo(PageView* pageView, const int position)
{
    auto player = Player::getInstance();
    _position = position;
    _characterId = position;
    _weaponId = static_cast<WeaponId>(player->getCharacterWeaponId(_characterId));
    
    auto tmpl = CSLoader::createNode("Csbs/Home/MemberStatusPageBox.csb")->getChildByName<Widget*>("Template");
    tmpl->retain();
    _csb = tmpl->clone();

    auto csb = getCsb();
    auto& data = getUnitData();

    auto avatar = csb->getChildByName<ImageView*>("Avatar");
    auto filePath = "Images/Character/Normal/" + data.code + "_" + getWeaponData().code + ".png";
    ImageManager::loadTexture(avatar, filePath);

    _menuLabels = csb->getChildByName("MenuLabels");
    _basicLabels = csb->getChildByName("BasicLabels");
    _labels = csb->getChildByName("Labels");

    setStatus();
    setWeapon();
    
    pageView->addChild(getCsb());
    tmpl->release();
}

void MemberStatusBox::setStatus()
{
    auto& data = getUnitData();
    auto& spCommand = data.command_data;
    auto icon = getCsb()->getChildByName<ImageView*>("IconElementType");
    ImageManager::loadTexture(icon, "Images/UIParts/icon_" + elementCodes.at(data.element).code + ".png");
    auto name = _menuLabels->getChildByName<TextBMFont*>("Name");
    name->setString(data.name);
    auto level = _basicLabels->getChildByName<TextBMFont*>("Level");
    level->setString("Lv." + std::to_string(1) + "/" + std::to_string(30));
    auto hp = _basicLabels->getChildByName<TextBMFont*>("HP");
    hp->setString(std::to_string(data.hp));
    auto attack = _basicLabels->getChildByName<TextBMFont*>("Attack");
    attack->setString(std::to_string(data.attack));
    auto spName = _basicLabels->getChildByName<TextBMFont*>("Special");
    spName->setString(spCommand.name);
    auto spExplain = _labels->getChildByName<Text*>("Special");
    spExplain->setString(spCommand.explain);
}

void MemberStatusBox::setWeapon()
{
    auto& data = getWeaponData();
    auto icon = getCsb()->getChildByName<ImageView*>("IconWeaponType");
    ImageManager::loadTexture(icon, "Images/UIParts/icon_" + weaponCodes.at(data.type).code + ".png");
    auto name = _menuLabels->getChildByName<TextBMFont*>("WeaponName");
    name->setString(data.name);
    auto hp = _basicLabels->getChildByName<TextBMFont*>("WeaponHP");
    hp->setString("(+" + std::to_string(data.hp) + ")");
    auto attack = _basicLabels->getChildByName<TextBMFont*>("WeaponAT");
    attack->setString("(+" + std::to_string(data.attack) + ")");

    auto commands = data.commands;
    auto i = 1;
    for (auto& command : commands) {
        std::stringstream nameSS;
        nameSS << "コマンド";
        nameSS << i;
        nameSS << " : ";
        nameSS << command.name;
        nameSS << " [AP:";
        nameSS << command.ap;
        nameSS << "]";
        auto name = _basicLabels->getChildByName<TextBMFont*>("Command_" + std::to_string(i));
        name->setString(nameSS.str());
        auto text = _labels->getChildByName<Text*>("Command_" + std::to_string(i));
        text->setString(command.explain);
        i++;
    }
}

void MemberStatusBox::setAction(const std::string name, const Callback& action)
{
    onTouch(getCsb()->getChildByName<Button*>(name), [&, action](Ref* ref){
        action(ref);
    });
}

const UnitData& MemberStatusBox::getUnitData() const
{
    return unitDatas.at(getCharacterId());
}

const WeaponData& MemberStatusBox::getWeaponData() const
{
    return weaponDatas.at(getWeaponId());
}

