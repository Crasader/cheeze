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
    ENEMY, SWORD, LANCE, ARCH, KNIFE, AX, CANE
};
enum class ElementType : int {
    WEAPON, FIRE, WATER, WIND, EARTH,
};
enum class TargetType : int {
    OWN, PARTY_ONE, PARTY_ALL, ENEMY_ONE, ENEMY_ALL, ENEMY_RANDOM
};
enum class EffectType : int {
    WEAPON_BURST, DAMAGE, ATK_UP, ATK_DOWN, DAMAGE_CUT, GUARD_BREAK, AP_UP, AP_DOWN, POISON, REGENE, INVICIBLE, REFRESH, TP_UP, TP_DOWN, HEAL, RESURRECTION
};

typedef struct EffectData {
    const EffectType type;
    const TargetType target;
    const ElementType element;
    const std::array<int, 2> power;
} EffectData;

typedef struct WeaponBurstData {
    const std::string name;
    const std::string explain;
    const std::vector<EffectData> effects;
} WeaponBurstData;

typedef struct WeaponData {
    const std::string name;
    const WeaponType type;
    const ElementType element;
    const int hp;
    const int attack;
    const int accuracy;
    const int critical;
    const WeaponBurstData burst;
} WeaponData;

typedef struct CommandData {
    const std::string name;
    const std::string explain;
    const int ap;
    const std::vector<EffectData> effects;
} CommandData;

typedef struct UnitData {
    const std::string name;
    const int hp;
    const int attack;
    const std::vector<WeaponType> weaponTypes;
    const std::vector<int> commandIds;
} UnitData;

typedef struct EnemyData {
    const std::string name;
    const std::string code;
    const int hp;
    const int attack;
    const int ap;
    const std::vector<CommandData> skills;
} EnemyData;

typedef struct CodeName{
    const std::string name;
    const std::string code;
    const Color3B color;
} CodeName;

extern const std::unordered_map<int, const UnitData> partyUnitDatas;
extern const std::unordered_map<int, const EnemyData> enemyUnitDatas;
extern const std::unordered_map<int, const WeaponData> weaponDatas;
extern const std::unordered_map<int, const CommandData> commandDatas;
extern const std::unordered_map<WeaponType, const CodeName> weaponCodes;
extern const std::unordered_map<ElementType, const CodeName> elementCodes;

#endif /* UnitData_h */
