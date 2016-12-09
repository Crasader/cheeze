//
//  CommonData.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/11/09.
//
//

#include "CommonData.h"

const std::unordered_map<WeaponType, const CodeName> weaponCodes = {
    {WeaponType::SWORD, {"けん", "sword"}},
    {WeaponType::LANCE, {"やり", "lance"}},
    {WeaponType::ARCH,  {"ゆみ", "arch"}},
    {WeaponType::CANE,  {"つえ", "cane"}},
    {WeaponType::AX,    {"おの", "ax"}},
    {WeaponType::MUSIC, {"がっき", "music"}},
    {WeaponType::ENEMY, {"", "enemy"}},
};

const std::unordered_map<ElementType, const CodeName> elementCodes = {
    {ElementType::FIRE,  {"ほのお", "fire", Color3B(138, 0, 0), Color3B(255, 138, 138)}},
    {ElementType::WATER, {"み　ず", "water", Color3B(0, 0, 138), Color3B(138, 238, 255)}},
    {ElementType::WIND,  {"か　ぜ", "wind", Color3B(0, 138, 0), Color3B(138, 255, 138)}},
};
