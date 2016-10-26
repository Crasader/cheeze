//
//  MemberStatusBox.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/08/23.
//
//

#include "MemberStatusBox.h"
#include "UnitData.h"

#include "ImageManager.h"
#include "BGMPlayer.h"

#include "editor-support/cocostudio/CocoStudio.h"
using namespace cocostudio;

void MemberStatusBox::appendTo(PageView* pageView, const int position)
{
    _position = position;
    auto tmpl = CSLoader::createNode("Csbs/Home/MemberStatusPageBox.csb")->getChildByName<Widget*>("Template");
    tmpl->retain();
    _csb = tmpl->clone();

    auto csb = getCsb();
    auto& data = getUnitData();

    auto avatar = csb->getChildByName<ImageView*>("Avatar");
    auto filePath = "Images/Character/Normal/" + data.code + ".png";
    ImageManager::loadTexture(avatar, filePath);

    _menuLabels = csb->getChildByName("MenuLabels");
    _basicLabels = csb->getChildByName("BasicLabels");
    _labels = csb->getChildByName("Labels");

    setStatus();
    setWeapon();
//    setCommands();
    
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
//    std::stringstream parameterSS;
//    auto n = 0;
//    for (auto& weaponType : data.weapon_types) {
//        parameterSS << weaponCodes.at(weaponType).name;
//        n++;
//        if (n < data.weapon_types.size()) {
//            parameterSS << "・";
//        }
//    }
//    parameter->setString(parameterSS.str());
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

    auto commandIds = data.command_ids;
    auto i = 1;
    for (auto commandId : commandIds) {
        auto& command = commandDatas.at(commandId);
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

void MemberStatusBox::setCommands()
{
    auto& data = getWeaponData();
//    auto commands = data.commands;
//    for (auto n = 1; n <= 3; n++) {
//        auto& command = commands.at(n);
//        auto text = node->getChildByName<Text*>("Text_" + std::to_string(n));
//        std::stringstream textSS;
//        textSS << "コマンド";
//        textSS << n;
//        textSS << " : ";
//        textSS << command.name;
//        textSS << " [AP:";
//        textSS << command.ap;
//        textSS << "]\n→";
//        textSS << command.explain;
//        text->setString(textSS.str());
//    }
//    
}

const UnitData& MemberStatusBox::getUnitData() const
{
    return unitDatas.at(getPosition());
}

const WeaponData& MemberStatusBox::getWeaponData() const
{
    return weaponDatas.at(getPosition());
}

