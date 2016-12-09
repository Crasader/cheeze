//
//  WeaponListBoard.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/11/10.
//
//

#include "WeaponListBoard.h"
#include "HomeScene.h"
#include "Player.h"
#include "UnitData.h"
#include "ItemData.h"
#include "CommonData.h"
#include "ImageManager.h"
#include "BGMPlayer.h"
#include "SupportFunctions.h"
#include "editor-support/cocostudio/CocoStudio.h"

void WeaponListBoard::init()
{
    onPressConfirm([&](const int orderId){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
        Player::getInstance()->changeCharacterWeaponId(_characterId, orderId);
        static_cast<HomeScene*>(getWorld())->setPartyMembers();
        hide();
    });
    onClose([&](Ref* ref){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
    });
}

void WeaponListBoard::setWeaponList(const int characterId)
{
    _characterId = characterId;
    std::vector<WeaponType> types = unitDatas.at(_characterId).weapon_types;
    std::vector<WeaponId> orderedIds;
    for (auto& weaponType : types) {
        for (auto& weapon : weaponDatas) {
            auto data = weapon.second;
            if (weaponType == data.type) {
                auto weaponId = weapon.first;
                orderedIds.push_back(weaponId);
            }
        }
    }
    std::sort(orderedIds.begin(), orderedIds.end());
    auto tmpl = CSLoader::createNode("Csbs/Home/WeaponListBox.csb")->getChildByName<Widget*>("Template");
    tmpl->retain();
    setBoxTemplate(tmpl);
    render<WeaponData, WeaponId>(weaponDatas, orderedIds, [&](Node* node, const WeaponId orderId, const WeaponData& data){
        setListBox(node, data);
    });
    tmpl->release();
}

void WeaponListBoard::setListBox(Node* node, const WeaponData data)
{
    auto icon = node->getChildByName<ImageView*>("IconWeaponType");
    ImageManager::loadTexture(icon, "Images/UIParts/icon_" + weaponCodes.at(data.type).code + ".png");
    auto image = node->getChildByName<ImageView*>("Image");
//    auto path = "Images/UIParts/" + data.code + ".png";
//    ImageManager::loadTexture(image, path);
    auto nameLabel = node->getChildByName<TextBMFont*>("Name");
    nameLabel->setString(data.name);
    auto hpLabel = node->getChildByName<TextBMFont*>("HP");
    hpLabel->setString("+" + std::to_string(data.hp));
    auto atLabel = node->getChildByName<TextBMFont*>("AT");
    atLabel->setString("+" + std::to_string(data.attack));
    auto commands = data.commands;
    auto i = 1;
    for (auto& command : commands) {
        auto nameLabel = node->getChildByName<TextBMFont*>("NameCommand_" + std::to_string(i));
        nameLabel->setString(command.name);
        auto needAPLabel = node->getChildByName<TextBMFont*>("APCommand_" + std::to_string(i));
        std::stringstream apSS;
        for (auto i = 0; i < command.ap; i++) {
            apSS << "★";
        }
        needAPLabel->setString(apSS.str());
        i++;
    }
}
