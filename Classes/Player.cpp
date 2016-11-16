//
//  Player.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/11/15.
//
//

#include "Player.h"
#include "UnitData.h"
#include "ItemData.h"
#include "CommonData.h"
#include "StageData.h"
#include "Env.h"
#include "CentralClient.h"
//#include "CCLocalNotification.h"

const std::unordered_map<ItemId, int> Player::INITIAL_ITEMS = {
    {ItemId::CHARGE, 0},
    {ItemId::SOUL,   0},
};
const std::unordered_map<int, int> Player::INITIAL_CHARACTERS = {
    {1, static_cast<int>(WeaponId::SWORD_1) },
    {2, static_cast<int>(WeaponId::ARCH_1) },
    {3, static_cast<int>(WeaponId::CANE_1) }
};

Player* Player::getInstance()
{
    static Player s_instance;
    return &s_instance;
}

void Player::load()
{
    PlayerBase::load();
}

void Player::reset()
{
    PlayerBase::reset();
//    LocalNotification::getInstance()->setEnabled(true);
    auto& playData = getPlayData();
    ValueMap map;
    ValueVector vec;
    const std::vector<const char*> mapKeys = {CHARACTERS, WEAPONS};
    for(auto k: mapKeys){ playData[k] = map; }
    const std::vector<const char*> vecKeys = {};
    for(auto k: vecKeys){ playData[k] = vec; }
    const std::vector<const char*> intKeys = {RANK, TOTAL_BATTLE};
    for(auto k: intKeys){ playData[k] = 0; }
    for (auto& item : INITIAL_ITEMS) {
        auto itemId = item.first;
        auto count = item.second;
        addItem(itemId, count);
    }
    for (auto& map : INITIAL_CHARACTERS) {
        auto characterId = map.first;
        auto weaponId = map.second;
        addCharacter(characterId, weaponId);
        addWeapon(weaponId);
    }
    
    createGift("Opening1", ItemId::CHARGE, 5, "[はろくえ]ダウンロードありがとうプレゼント!!");
    createGift("Opening2", ItemId::SOUL, 1000, "[はろくえ]ダウンロードありがとうプレゼント!!");
    
    setVolume(100);
    setVolumeSE(100);
    setAudioId(-1);
    
    save();
}
