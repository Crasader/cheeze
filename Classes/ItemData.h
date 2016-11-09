//
//  ItemData.h
//  cheeze
//
//  Created by 上野 真史 on 2016/11/09.
//
//

#ifndef ItemData_h
#define ItemData_h

#include "PlayerBase.h"
#include "CommonData.h"

struct Money {
    const ItemId itemId;
    const int amount;
};
typedef struct ItemData {
    const std::string name;
    const std::string explain;
    const std::string code;
    const std::vector<Money> prices;
    const std::vector<EffectData> effect_datas;
} ItemData;

typedef struct WeaponData {
    const std::string name;
    const WeaponType type;
    const int hp;
    const int attack;
    const std::vector<int> command_ids;
} WeaponData;

extern const std::unordered_map<ItemId, const ItemData> itemDatas;
extern const std::unordered_map<int, const WeaponData> weaponDatas;

#endif /* ItemData_h */
