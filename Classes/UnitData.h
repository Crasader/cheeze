//
//  CharacterData.h
//  cheeze
//
//  Created by 上野 真史 on 2016/08/23.
//
//

#ifndef UnitData_h
#define UnitData_h

#include "CommonData.h"

typedef struct UnitData {
    const std::string name;
    const std::string code;
    const UnitAnimationType animation;
    const int hp;
    const int attack;
    const int ap;
    const ElementType element;
    const std::vector<WeaponType> weapon_types;
    const CommandData command_data;
} UnitData;

typedef struct EnemyData {
    const int unit_id;
    const int hp;
    const int attack;
    const int ap;
} EnemyData;

extern const std::unordered_map<int, const UnitData> unitDatas;
extern const std::unordered_map<int, const CommandData> commandDatas;

#endif /* UnitData_h */
