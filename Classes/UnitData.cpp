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

const std::unordered_map<int, const UnitData> unitDatas = {
    {1, {"キラリ", "kiraly", UnitAnimationType::WALK, 1800, 650, 5, ElementType::FIRE, {WeaponType::SWORD, WeaponType::AX},
        {"トライアドスター", "敵単体に火属性ダメージ(大) / 水属性の追加ダメージ(大) / 風属性の追加ダメージ(大)", "", 100,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::FIRE,  {325, 400}},
                {EffectType::DAMAGE, TargetType::SAME, ElementType::WATER, {325, 400}},
                {EffectType::DAMAGE, TargetType::SAME, ElementType::WIND,  {325, 400}}
            }
        },
    }},
    {2, {"ヒラリ", "hiraly", UnitAnimationType::WALK, 1600, 500, 5, ElementType::WIND, {WeaponType::ARCH, WeaponType::LANCE},
        {"ミラクルウィンド", "味方全員のAPを+5する", "", 100,
            {
                {EffectType::REGENE, TargetType::PARTY_ALL, ElementType::WIND, {50, 3}},
                {EffectType::AP_UP, TargetType::PARTY_ALL, ElementType::WIND, {5, 5}}
            }
        },
    }},
    {3, {"サラリ", "saraly", UnitAnimationType::WALK, 1500, 400, 5, ElementType::WATER, {WeaponType::CANE, WeaponType::MUSIC},
        {"マーシーレイン", "味方全体を気絶から復活 / 味方全体のＨＰを回復(特大)", "", 100,
            {
                {EffectType::RESURRECTION, TargetType::PARTY_ALL, ElementType::WATER, {650, 780}},
            }
        },
    }},
    {11, {"ばうわう", "1", UnitAnimationType::WALK, 6000, 200, 3, ElementType::FIRE, {WeaponType::ENEMY},
        {"かみつく", "", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_LARGE},
            }
        },
    }},
    {12, {"あるみらじ", "2", UnitAnimationType::WALK, 5400, 180, 5, ElementType::WIND, {WeaponType::ENEMY},
        {"とびげり", "", "", 5,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_L_LARGE},
            }
        },
    }},
    {13, {"きのこりお", "3", UnitAnimationType::WALK, 4800, 160, 2, ElementType::WATER, {WeaponType::ENEMY},
        {"たいあたり", "", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_MIDDLE}
            }
        },
    }},
    {14, {"まーきー", "4", UnitAnimationType::WALK, 6800, 240, 2, ElementType::FIRE, {WeaponType::ENEMY},
        {"とっしん", "", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_MIDDLE}
            }
        },
    }},
    {15, {"かざりばな", "5", UnitAnimationType::WALK, 7000, 140, 3, ElementType::WIND, {WeaponType::ENEMY},
        {"げんわくのこな", "", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::SELF, DAMAGE_NORMAL},
                {EffectType::AP_DOWN, TargetType::ENEMY_ALL, ElementType::SELF, {0, 2}}
            }
        },
    }},
    {16, {"さるっちゃ", "6", UnitAnimationType::WALK, 8000, 260, 4, ElementType::FIRE, {WeaponType::ENEMY},
        {"あばれまわる", "", "", 4,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::SELF, DAMAGE_SMALL}
            }
        },
    }},
    {17, {"れいぶ", "7", UnitAnimationType::FLY, 7500, 200, 2, ElementType::WATER, {WeaponType::ENEMY},
        {"きゅうこうか", "", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_LARGE}
            }
        },
    }},
    {18, {"らっく", "8", UnitAnimationType::WALK, 6400, 160, 3, ElementType::WIND, {WeaponType::ENEMY},
        {"よつばのかぜ", "", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL}
            }
        },
    }},
    {19, {"ごれむん", "9", UnitAnimationType::WALK, 9000, 240, 3, ElementType::WATER, {WeaponType::ENEMY},
        {"のしかかる", "", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_MIDDLE},
                {EffectType::AP_DOWN, TargetType::SAME, ElementType::SELF, {0, 2}}
            }
        },
    }},
    {20, {"ぱんぷきんぐ", "10", UnitAnimationType::FALL, 40000, 400, 4, ElementType::FIRE, {WeaponType::ENEMY},
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
};
