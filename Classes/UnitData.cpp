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
    {1, {"キラリ", "1", 3, 1800, 650, 5, ElementType::FIRE, {WeaponType::SWORD, WeaponType::KNIFE, WeaponType::AX},
        {"トライアドスター", "敵全体に火属性ダメージ(大) / 水属性の追加ダメージ(中) / 風属性の追加ダメージ(中)", "", 100,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::FIRE,  DAMAGE_LARGE},
                {EffectType::DAMAGE, TargetType::SAME, ElementType::WATER, DAMAGE_MIDDLE},
                {EffectType::DAMAGE, TargetType::SAME, ElementType::WIND,  DAMAGE_MIDDLE}
            }
        },
    }},
    {2, {"ヒラリ", "2", 2, 1600, 500, 5, ElementType::WIND, {WeaponType::ARCH},
        {"しんぴのかぜ", "味方全員のAPを+5する", "", 100,
            {
                {EffectType::REGENE, TargetType::PARTY_ALL, ElementType::WIND, {50, 3}},
                {EffectType::AP_UP, TargetType::PARTY_ALL, ElementType::WIND, {5, 5}}
            }
        },
    }},
    {3, {"サラリ", "3", 1, 1500, 400, 5, ElementType::WATER, {WeaponType::CANE},
        {"めいきょうしすい", "味方全体のＨＰを回復(特大) / 気絶した仲間を復活させる(HP:50%)", "", 100,
            {
                {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::WATER, HEAL_L_LARGE},
                {EffectType::RESURRECTION, TargetType::PARTY_ALL, ElementType::WATER, {45, 55}},
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
                {EffectType::AP_DOWN, TargetType::ENEMY_ALL, ElementType::SELF, {1, 3}}
            }
        },
    }},
    {16, {"さるっちゃ", "16", 1, 8000, 260, 3, ElementType::FIRE, {WeaponType::ENEMY},
        {"あばれまわる", "", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::SELF, DAMAGE_MIDDLE}
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
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_LARGE}
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

const std::unordered_map<int, const WeaponData> weaponDatas = {
    { 0, {"なし　　　　　　", WeaponType::ENEMY,   0,   0, {0} }},
    { 1, {"バスタードソード", WeaponType::SWORD, 100, 300, { 1,  18,  3} }},
    { 2, {"もりびとのゆみ　", WeaponType::ARCH,  150, 250, {12, 5, 10} }},
    { 3, {"あめふりのつえ　", WeaponType::CANE,  200, 200, {7, 8, 9}}},
    { 4, {"きしのつるぎ　　", WeaponType::SWORD, 250, 150, {13, 14, 15} }},
    { 5, {"てんかいのやり　", WeaponType::ARCH,  200, 200, {12, 5, 6} }},
    { 6, {"ほしよみのつえ　", WeaponType::CANE,  200, 200, {13, 14, 15} }},
    { 7, {"とうぞくのけん　", WeaponType::SWORD, 150, 150, {12, 16, 17} }},
    { 8, {"マスケットじゅう", WeaponType::ARCH,  350,  50, { 4,  5, 11} }},
    { 9, {"そよかぜのハープ", WeaponType::CANE,  200, 200, {13, 14, 15} }},
};

const std::unordered_map<int, const CommandData> commandDatas = {
    { 0, {"こうげき", "", "", 0,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_NORMAL}
        }
    }},
    { 1, {"ぶったぎり", "敵単体に自属性ダメージ(小)", "", 1,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL}
        }
    }},
    { 2, {"おたけび", "味方全体のATを25%アップ(2ターン)", "", 2,
        {
            {EffectType::ATK_UP, TargetType::PARTY_ALL, ElementType::SELF, {25, 2}},
        }
    }},
    { 3, {"らんぺーじ", "敵単体に自属性ダメージ(中) / 3回繰り返す", "", 4,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_MIDDLE},
            {EffectType::DAMAGE, TargetType::SAME, ElementType::SELF, DAMAGE_MIDDLE},
            {EffectType::DAMAGE, TargetType::SAME, ElementType::SELF, DAMAGE_MIDDLE}
        }
    }},
    { 4, {"どくや", "敵単体に自属性ダメージ(小) / 対象に3ターンの継続ダメージ", "", 2,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL},
            {EffectType::POISON, TargetType::SAME, ElementType::SELF, {35, 3}}
        }
    }},
    { 5, {"あしどめのや", "敵単体に武器属性ダメージ(小) / 対象のAPを-1する", "", 2,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL},
            {EffectType::AP_DOWN, TargetType::SAME, ElementType::SELF, {1, 1}},
        }
    }},
    { 6, {"やのあらし", "敵全体に自属性ダメージ(中)", "", 3,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::SELF, DAMAGE_MIDDLE}
        }
    }},
    { 7, {"いのちのみず", "現在のＨＰが一番少ない味方単体のＨＰを回復(小)", "", 1,
        {
            {EffectType::HEAL, TargetType::PARTY_ONE, ElementType::WATER, HEAL_SMALL}
        }
    }},
    { 8, {"みずでっぽう", "敵単体に水属性ダメージ(大)", "", 2,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WATER, DAMAGE_LARGE}
        }
    }},
    { 9, {"いやしのあめ", "味方全体のＨＰを回復(中)", "", 3,
        {
            {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::WATER, HEAL_MIDDLE}
        }
    }},
    {10, {"みだれうち", "敵単体に自属性ダメージ(小) / ターゲットランダムで4回繰り返す", "", 3,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL},
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL},
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL},
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL}
        }
    }},
    {11, {"まぼろしのきり", "自分が受けるダメージを0にする(1ターン)", "", 1,
        {
            {EffectType::DAMAGE_CUT, TargetType::OWN, ElementType::SELF, {100, 1}}
        }
    }},
    {12, {"しんこきゅう", "自分のAPを+2する", "", 1,
        {
            {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {2, 2}}
        }
    }},
    {13, {"じゅうじぎり", "敵単体に自属性ダメージ(小) / 自属性の追加ダメージ(小)", "", 2,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL},
            {EffectType::DAMAGE, TargetType::SAME, ElementType::SELF, DAMAGE_SMALL}
        }
    }},
    {14, {"まもりのかまえ", "味方全体が受けるダメージを50%カット(1ターン)", "", 3,
        {
            {EffectType::DAMAGE_CUT, TargetType::PARTY_ALL, ElementType::SELF, {50, 1}},
        }
    }},
    {15, {"いやしのひかり", "味方全体のＨＰを回復(小)", "", 3,
        {
            {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::SELF, HEAL_SMALL},
        }
    }},
    {16, {"どろぼうぎり", "敵単体に自属性ダメージ(小) / 対象のAPを-1する / 自分のAPを+1する", "", 2,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL},
            {EffectType::AP_DOWN, TargetType::SAME, ElementType::SELF, {1, 1}},
            {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {1, 1}},
        }
    }},
    {17, {"みだれぎり", "敵単体に自属性ダメージ(小) / ターゲットランダムで4回繰り返す", "", 3,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL},
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL},
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL},
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, DAMAGE_SMALL}
        }
    }},
    {18, {"ぶんまわす", "敵全体に自属性ダメージ(小)", "", 2,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::SELF, DAMAGE_SMALL}
        }
    }},
};

const std::unordered_map<WeaponType, const CodeName> weaponCodes = {
    {WeaponType::SWORD, {"けん", "sword"}},
    {WeaponType::LANCE, {"やり", "lance"}},
    {WeaponType::ARCH,  {"ゆみ", "arch"}},
    {WeaponType::CANE,  {"つえ", "cane"}},
    {WeaponType::AX,    {"おの", "ax"}},
    {WeaponType::KNIFE, {"ないふ", "knife"}},
    {WeaponType::ENEMY, {"", "enemy"}},
};

const std::unordered_map<ElementType, const CodeName> elementCodes = {
    {ElementType::FIRE,  {"ほのお", "fire", Color3B(138, 0, 0)}},
    {ElementType::WATER, {"み　ず", "water", Color3B(0, 0, 138)}},
//    {ElementType::EARTH, {"だいち", "earth", Color3B(138, 68, 0)}},
    {ElementType::WIND,  {"か　ぜ", "wind", Color3B(0, 138, 0)}},
};

