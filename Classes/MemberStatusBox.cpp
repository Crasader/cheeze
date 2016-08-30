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
    auto image = getCsb()->getChildByName<ImageView*>("Image");
    auto command = getCsb()->getChildByName("Command");
    command->setVisible(false);
    auto& data = getUnitData();
    auto filePath = "Images/" + data.code + "_large.png";
    ImageManager::loadTexture(image, filePath);
    onTouch(image, [&](Ref* ref){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
        auto status = getCsb()->getChildByName("Status");
        status->setVisible(!status->isVisible());
        auto weapon = getCsb()->getChildByName("Weapon");
        weapon->setVisible(!weapon->isVisible());
        auto command = getCsb()->getChildByName("Command");
        command->setVisible(!status->isVisible());
    });
    
    setStatus();
    setWeapon();
    setCommands();
    
    pageView->addChild(getCsb());
    tmpl->release();
}

void MemberStatusBox::setStatus()
{
    auto& data = getUnitData();
    auto node = getCsb()->getChildByName("Status");
    
    auto image = node->getChildByName<ImageView*>("Image");
    auto filePath = "Images/" + data.code + ".png";
    ImageManager::loadTexture(image, filePath);
    
    auto parameter = node->getChildByName<Text*>("Parameter");
    std::stringstream parameterSS;
    parameterSS << data.name;
    parameterSS << "\n";
    parameterSS << "Lv.";
    parameterSS << 99;
    parameterSS << " / Next ";
    parameterSS << 99999;
    parameterSS << "\n";
    parameterSS << "HP : ";
    parameterSS << data.hp;
    parameterSS << "+";
    parameterSS << getWeaponData().hp;
    parameterSS << "\n";
    parameterSS << "ATK : ";
    parameterSS << data.attack;
    parameterSS << "+";
    parameterSS << getWeaponData().attack;
    parameterSS << "\n";
    parameterSS << "\n";
    parameterSS << "武器 : ";
    auto n = 0;
    for (auto& weaponType : data.weaponTypes) {
        parameterSS << weaponCodes.at(weaponType).name;
        n++;
        if (n < data.weaponTypes.size()) {
            parameterSS << "・";
        }
    }
    parameter->setString(parameterSS.str());
}

void MemberStatusBox::setWeapon()
{
    auto& data = getWeaponData();
    auto node = getCsb()->getChildByName("Weapon");
    auto bgImage = node->getChildByName<ImageView*>("BgLucent");
    bgImage->setColor(elementCodes.at(data.element).color);
    
    auto parameter = node->getChildByName<Text*>("Parameter");
    std::stringstream parameterSS;
    parameterSS << "【";
    parameterSS << weaponCodes.at(data.type).name;
    parameterSS << " / ";
    parameterSS << elementCodes.at(data.element).name;
    parameterSS << "】";
    parameterSS << data.name;
    parameterSS << "+";
    parameterSS << random(1, 5);
    parameterSS << "\n";
    parameterSS << "HP : ";
    parameterSS << data.hp;
    parameterSS << " / ATK : ";
    parameterSS << data.attack;
    parameterSS << "\n";
    parameterSS << "命中 : ";
    parameterSS << data.accuracy;
    parameterSS << "% / ";
    parameterSS << "クリティカル : ";
    parameterSS << data.critical;
    parameterSS << "%";
    parameter->setString(parameterSS.str());
    
    auto burst = node->getChildByName<Text*>("WeaponBurst");
    auto& burstData = weaponBurstDatas.at(data.burstId);
    std::stringstream burstSS;
    burstSS << "ウェポンバースト : ";
    burstSS << burstData.name;
    burstSS << "\n→";
    burstSS << burstData.explain;
    burst->setString(burstSS.str());
}

void MemberStatusBox::setCommands()
{
    auto commands = getUnitData().commands;
    auto node = getCsb()->getChildByName("Command");
    for (auto n = 1; n <= 3; n++) {
        auto& command = commands.at(n);
        auto text = node->getChildByName<Text*>("Text_" + std::to_string(n));
        std::stringstream textSS;
        textSS << "コマンド";
        textSS << n;
        textSS << " : ";
        textSS << command.name;
        textSS << " [AP:";
        textSS << command.ap;
        textSS << "]\n→";
        textSS << command.explain;
        text->setString(textSS.str());
    }
    
}

const UnitData& MemberStatusBox::getUnitData() const
{
    return partyUnitDatas.at(getPosition());
}

const WeaponData& MemberStatusBox::getWeaponData() const
{
    return weaponDatas.at(getPosition());
}

