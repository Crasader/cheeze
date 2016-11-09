//
//  CommonData.h
//  cheeze
//
//  Created by 上野 真史 on 2016/11/09.
//
//

#ifndef CommonData_h
#define CommonData_h

#include "scheme.h"
#include "cocos2d.h"

using namespace cocos2d;

enum class WeaponType : int {
    ENEMY, SWORD, LANCE, ARCH, KNIFE, AX, CANE, BOOK
};
enum class ElementType : int {
    SELF, FIRE, WATER, WIND,
    //    EARTH,
};
enum class TargetType : int {
    OWN, SAME, PARTY_ONE, PARTY_ALL, ENEMY_ONE, ENEMY_ALL
};
enum class EffectType : int {
    DAMAGE, ATK_UP, ATK_DOWN, DAMAGE_CUT, AP_UP, AP_DOWN, POISON, REGENE, INVICIBLE, REFRESH,
    TP_UP, TP_DOWN, HEAL, RESURRECTION, MORE_DROP
};
enum class ItemId : int {
    NONE, COIN, HEAL, HEAL_ALL, RESURRECTION, AP_UP, MORE_DROP,
    PUMPKIN_COIN
};

typedef struct EffectData {
    const EffectType type;
    const TargetType target;
    const ElementType element;
    const std::array<int, 2> power;
} EffectData;

typedef struct CodeName {
    const std::string name;
    const std::string code;
    const Color3B color;
} CodeName;

extern const std::unordered_map<WeaponType, const CodeName> weaponCodes;
extern const std::unordered_map<ElementType, const CodeName> elementCodes;

#endif /* CommonData_h */
