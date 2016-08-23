//
//  MemberListBox.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/08/23.
//
//

#include "MemberListBox.h"
#include "UnitData.h"

#include "ImageManager.h"
#include "BGMPlayer.h"

#include "editor-support/cocostudio/CocoStudio.h"
using namespace cocostudio;

void MemberListBox::appendTo(ListView* list, const int position, ImageView* avatar)
{
    _avatar = avatar;
    _position = position;
    auto tmpl = CSLoader::createNode("Csbs/Battle/MemberListBox.csb")->getChildByName<Widget*>("Template");
    tmpl->retain();
    _csb = tmpl->clone();
    auto thumbnail = getCsb()->getChildByName("Thumbnail")->getChildByName<ImageView*>("Image");
    auto filePath = "Images/UIParts/character_thumbnail_" + std::to_string(position) + ".png";
    ImageManager::loadTexture(thumbnail, filePath);
    
    auto bgImage = getCsb()->getChildByName<ImageView*>("BgImage");
    bgImage->setColor(elementCodes.at(getWeaponData().element).color);

    addAP();
    
    setHP();
    setAP();
    setTP();
    setCommands();
    
    list->addChild(getCsb());
    tmpl->release();
}

void MemberListBox::setHP()
{
    auto data = getUnitData();
    _hp = _hpMax = data.hp + getWeaponData().hp;
    std::stringstream nameSS;
    nameSS << data.name;
    nameSS << " HP : ";
    nameSS << getHP();
    nameSS << " / ";
    nameSS << getHPMax();
    auto nameLabel = getCsb()->getChildByName<Text*>("HPLabel");
    nameLabel->setString(nameSS.str());
}

void MemberListBox::setAP()
{
    auto currentAp = getAP();
    auto apLabel = getCsb()->getChildByName<Text*>("APLabel");
    apLabel->setString("[AP:" + std::to_string(currentAp) + "]");
    for (auto i = 0; i < 5; i++) {
        auto ap = getCsb()->getChildByName<Button*>("AP_" + std::to_string(i + 1));
        ap->setBright(i < currentAp);
    }
}

void MemberListBox::setTP()
{
    auto currentTp = getTP();
    auto node = getCsb()->getChildByName("TP");
    auto tpLabel = node->getChildByName<Text*>("Label");
    tpLabel->setString("TP:" + std::to_string(currentTp) + "%");
    auto tpBar = node->getChildByName<LoadingBar*>("Bar");
    tpBar->setPercent(getTpPercent());
}

void MemberListBox::setCommands()
{
    selectCommands();
    for (auto num = 0; num < 5; num++) {
        setCommand(num);
    }
}

void MemberListBox::setCommand(const int number)
{
    auto commandId = 0;
    auto command = getCsb()->getChildByName<Button*>("Command_" + std::to_string(number));
    auto needAPLabel = command->getChildByName<Text*>("Label");
    if (number == 4) {
        commandId = -1;
    } else if (number != 0) {
        commandId = getUnitData().commandIds.at(number - 1);
    }
    auto data = commandDatas.at(commandId);
    auto needAP = data.ap;
    if (number == 4) {
        needAPLabel->setString("TP:" + std::to_string(needAP) + "%");
        needAPLabel->setColor(Color3B(0, 255, 68));
        if (getTP() >= 100) {
            command->setBright(true);
            command->setEnabled(true);
        } else {
            command->setBright(false);
            command->setEnabled(false);
        }
    } else if (number != 0) {
        needAPLabel->setString("AP:" + std::to_string(needAP));
        needAPLabel->setColor(Color3B(255, 0, 68));
        if (needAP > 0 && getAP() >= needAP) {
            command->setBright(true);
            command->setEnabled(true);
        } else {
            command->setBright(false);
            command->setEnabled(false);
        }
    } else {
        needAPLabel->setVisible(false);
    }
    onTouch(command, [&, number](Ref* ref){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
        selectCommands(number);
    });
}

void MemberListBox::selectCommands(const int number)
{
    _command = number;
    for (auto num = 0; num < 5; num++) {
        auto command = getCsb()->getChildByName<Button*>("Command_" + std::to_string(num));
        if (number == num) {
            command->setColor(Color3B(255, 238, 136));
        } else {
            command->setColor(Color3B::WHITE);
        }
    }
}

void MemberListBox::attack()
{
    auto jump = JumpBy::create(0.2f, Vec2(-60, 0), 30, 1);
    auto wait = DelayTime::create(0.4f);
    auto finish = CallFunc::create([&]{
        addAP();
        setAP();
        addTP(random(10, 15));
        setTP();
        setCommands();
    });
    auto action = Sequence::create(jump, wait, jump->reverse(), finish, nullptr);
    getAvatar()->runAction(action);
}

const int MemberListBox::getAtk()
{
    auto data = getUnitData();
    auto atk = data.attack + getWeaponData().attack;
    return atk;
}


void MemberListBox::init()
{
    
}


const UnitData& MemberListBox::getUnitData() const
{
    return partyUnitDatas.at(getPosition());
}

const WeaponData& MemberListBox::getWeaponData() const
{
    return weaponDatas.at(getPosition());
}

