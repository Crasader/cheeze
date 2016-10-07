//
//  CharacterData.h
//  cheeze
//
//  Created by 上野 真史 on 2016/08/23.
//
//

#ifndef UnitData_h
#define UnitData_h

#include "scheme.h"
#include "cocos2d.h"

using namespace cocos2d;

enum class WeaponType : int {
    ENEMY, SWORD, LANCE, ARCH, KNIFE, AX, CANE, BOOK
};
enum class ElementType : int {
    WEAPON, FIRE, WATER, WIND, EARTH,
};
enum class TargetType : int {
    OWN, PARTY_ONE, PARTY_ALL, ENEMY_ONE, ENEMY_ALL, ENEMY_RANDOM_4
};
enum class EffectType : int {
    WEAPON_BURST, DAMAGE, ATK_UP, ATK_DOWN, DAMAGE_CUT, AP_UP, AP_DOWN, POISON, REGENE, INVICIBLE, REFRESH, TP_UP, TP_DOWN, HEAL, RESURRECTION
};

typedef struct EffectData {
    const EffectType type;
    const TargetType target;
    const ElementType element;
    const std::array<int, 2> power;
} EffectData;

typedef struct WeaponData {
    const std::string name;
    const WeaponType type;
    const ElementType element;
    const int hp;
    const int attack;
    const std::vector<int> command_ids;
} WeaponData;

typedef struct CommandData {
    const std::string name;
    const std::string explain;
    const std::string code;
    const int ap;
    const std::vector<EffectData> effect_datas;
} CommandData;

typedef struct UnitData {
    const std::string name;
    const std::string code;
    const int rank;
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

typedef struct CodeName {
    const std::string name;
    const std::string code;
    const Color3B color;
} CodeName;

extern const std::unordered_map<int, const UnitData> unitDatas;
extern const std::unordered_map<int, const WeaponData> weaponDatas;
extern const std::unordered_map<int, const CommandData> commandDatas;
extern const std::unordered_map<WeaponType, const CodeName> weaponCodes;
extern const std::unordered_map<ElementType, const CodeName> elementCodes;

#endif /* UnitData_h */
