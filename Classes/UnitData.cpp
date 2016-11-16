//
//  UnitData.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/08/23.
//
//

#include "UnitData.h"

const std::array<int, 2> DAMAGE_NORMAL =  { 95, 105};
const std::array<int, 2> DAMAGE_SMALL =   {125, 150};
const std::array<int, 2> DAMAGE_MIDDLE =  {200, 250};
const std::array<int, 2> DAMAGE_LARGE =   {325, 400};
const std::array<int, 2> DAMAGE_L_LARGE = {525, 625};
const std::array<int, 2> HEAL_SMALL =     { 60,  75};
const std::array<int, 2> HEAL_MIDDLE =    {100, 125};
const std::array<int, 2> HEAL_LARGE =     {160, 200};
const std::array<int, 2> HEAL_L_LARGE =   {250, 300};

const std::unordered_map<int, const UnitData> unitDatas = {
    {1, {"キラリ", "kiraly", 3, 1800, 650, 5, ElementType::FIRE, {WeaponType::SWORD, WeaponType::AX},
        {"トライアドスター", "敵全体に火属性ダメージ(大) / 水属性の追加ダメージ(大) / 風属性の追加ダメージ(大)", "", 100,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::FIRE,  {325, 400}},
                {EffectType::DAMAGE, TargetType::SAME, ElementType::WATER, {325, 400}},
                {EffectType::DAMAGE, TargetType::SAME, ElementType::WIND,  {325, 400}}
            }
        },
    }},
    {2, {"ヒラリ", "hiraly", 2, 1600, 500, 5, ElementType::WIND, {WeaponType::ARCH, WeaponType::LANCE},
        {"しんぴのかぜ", "味方全体のHPを3ターン継続回復する / 味方全員のAPを+5する", "", 100,
            {
                {EffectType::REGENE, TargetType::PARTY_ALL, ElementType::WIND, {50, 3}},
                {EffectType::AP_UP, TargetType::PARTY_ALL, ElementType::WIND, {5, 5}}
            }
        },
    }},
    {3, {"サラリ", "saraly", 1, 1500, 400, 5, ElementType::WATER, {WeaponType::CANE, WeaponType::MUSIC},
        {"めいきょうしすい", "気絶している仲間を復活させる / 味方全体のＨＰを回復(特大)", "", 100,
            {
                {EffectType::RESURRECTION, TargetType::PARTY_ALL, ElementType::WATER, {1, 1}},
                {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::WATER, {250, 300}},
            }
        },
    }},
    {11, {"ばうわう", "11", -1, 6000, 200, 3, ElementType::FIRE, {WeaponType::ENEMY},
        {"かみつく", "", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_LARGE},
            }
        },
    }},
    {12, {"あるみらじ", "12", 1, 5400, 140, 3, ElementType::WIND, {WeaponType::ENEMY},
        {"とびげり", "", "", 5,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_L_LARGE},
            }
        },
    }},
    {13, {"きのこりお", "13", 1, 4800, 160, 2, ElementType::WATER, {WeaponType::ENEMY},
        {"たいあたり", "", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_MIDDLE}
            }
        },
    }},
    {14, {"まーきー", "14", 1, 6800, 240, 2, ElementType::FIRE, {WeaponType::ENEMY},
        {"とっしん", "", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_MIDDLE}
            }
        },
    }},
    {15, {"かざりばな", "15", 1, 7000, 140, 3, ElementType::WIND, {WeaponType::ENEMY},
        {"げんわくのこな", "", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::SELF, DAMAGE_NORMAL},
                {EffectType::AP_DOWN, TargetType::ENEMY_ALL, ElementType::SELF, {0, 2}}
            }
        },
    }},
    {16, {"さるっちゃ", "16", 1, 8000, 260, 4, ElementType::FIRE, {WeaponType::ENEMY},
        {"あばれまわる", "", "", 4,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::SELF, DAMAGE_SMALL}
            }
        },
    }},
    {17, {"れいぶ", "17", 1, 7500, 200, 2, ElementType::WATER, {WeaponType::ENEMY},
        {"きゅうこうか", "", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_LARGE}
            }
        },
    }},
    {18, {"らっく", "18", 1, 6400, 160, 3, ElementType::WIND, {WeaponType::ENEMY},
        {"よつばのかぜ", "", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL}
            }
        },
    }},
    {19, {"ごれむん", "19", 1, 9000, 240, 3, ElementType::WATER, {WeaponType::ENEMY},
        {"のしかかる", "", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_MIDDLE},
                {EffectType::AP_DOWN, TargetType::SAME, ElementType::SELF, {0, 2}}
            }
        },
    }},
    {20, {"ぱんぷきんぐ", "20", 1, 40000, 400, 4, ElementType::FIRE, {WeaponType::ENEMY},
        {"かぼちゃばくだん", "", "", 4,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::SELF, DAMAGE_MIDDLE},
                {EffectType::AP_DOWN, TargetType::ENEMY_ALL, ElementType::SELF, {1, 1}}
            }
        },
    }},
};

const std::unordered_map<int, const CommandData> commandDatas = {
    { 0, {"こうげき", "", "", 0,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, { 95, 105}}
        }
    }},
    { 2, {"おたけび", "味方全体のATを25%アップ(2ターン)", "", 2,
        {
            {EffectType::ATK_UP, TargetType::PARTY_ALL, ElementType::SELF, {25, 2}},
        }
    }},
};
