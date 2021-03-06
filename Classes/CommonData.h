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

enum class ItemType : int {
    BATTLE, MEDAL, SWEETS
};
enum class WeaponType : int {
    ENEMY, SWORD, LANCE, ARCH, AX, CANE, MUSIC
};
enum class UnitAnimationType : int {
    WALK, FLOAT, FLY, CRAWL, FALL
};
enum class ElementType : int {
    SELF, NONE, FIRE, WATER, WIND
};
enum class TargetType : int {
    OWN, SAME, PARTY_ONE, PARTY_ALL, ENEMY_ONE, ENEMY_ONE_MIN, ENEMY_ONE_MAX, ENEMY_ALL
};
enum class EffectType : int {
    DAMAGE, HEAL, AP_UP, AP_DOWN, RESURRECTION, MORE_DROP, 
    TP_UP, TP_DOWN, ATK_UP, ATK_DOWN, DAMAGE_CUT, POISON, REGENE, INVICIBLE, REFRESH
};
enum class ItemId : int {
    NONE, CHARGE, SOUL, HEAL, HEAL_ALL, RESURRECTION, AP_UP, MORE_DROP,
    SWEETS_DONUT, SWEETS_CANDY_LOLLIPOP, SWEETS_CHOCOLATE,
    SWEETS_MACAROON_RED, SWEETS_MACAROON_GREEN, SWEETS_MACAROON_BLUE,
    SWEETS_COOKIE, SWEETS_CANDY, SWEETS_PUDDING, SWEETS_CAKE,
    GHOST_MEDAL, PUMPKIN_MEDAL
};
enum class WeaponId : int {
    NONE, 
    SWORD_1, SWORD_2, SWORD_3, SWORD_4, SWORD_5,
    AX_1, AX_2, AX_3, AX_4, AX_5,
    LANCE_1, LANCE_2, LANCE_3, LANCE_4, LANCE_5,
    ARCH_1, ARCH_2, ARCH_3, ARCH_4, ARCH_5,
    CANE_1, CANE_2, CANE_3, CANE_4, CANE_5,
    MUSIC_1, MUSIC_2, MUSIC_3, MUSIC_4, MUSIC_5,
};

typedef struct EffectData {
    const EffectType type;
    const TargetType target;
    const ElementType element;
    const std::array<int, 2> power;
} EffectData;

typedef struct CommandData {
    const std::string name;
    const std::string explain;
    const std::string code;
    const int ap;
    const std::vector<EffectData> effect_datas;
} CommandData;

typedef struct CodeName {
    const std::string name;
    const std::string code;
    const Color3B bg_color;
    const Color3B text_color;
} CodeName;

extern const std::unordered_map<WeaponType, const CodeName> weaponCodes;
extern const std::unordered_map<ElementType, const CodeName> elementCodes;

#endif /* CommonData_h */
