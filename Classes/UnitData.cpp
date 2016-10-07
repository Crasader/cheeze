//
//  UnitData.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/08/23.
//
//

#include "UnitData.h"

const std::unordered_map<int, const UnitData> unitDatas = {
    {1, {"キラリ", "1", 3, 1800, 650, 5, ElementType::FIRE, {WeaponType::SWORD, WeaponType::KNIFE, WeaponType::AX},
        {"トライアドスター", "敵全体に火属性ダメージ(中) / 水属性の追加ダメージ(中) / 風属性の追加ダメージ(中)", "", 1,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::FIRE, {200, 250}},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WATER, {200, 250}},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WIND, {200, 250}}
            }
        },
    }},
    {2, {"ヒラリ", "2", 2, 1400, 480, 5, ElementType::WIND, {WeaponType::ARCH},
        {"しんぴのかぜ", "味方全体に活性効果を付与する(3ターン) / 味方全員のAPを+5する", "", 1,
            {
                {EffectType::REGENE, TargetType::PARTY_ALL, ElementType::WIND, {50, 3}},
                {EffectType::AP_UP, TargetType::PARTY_ALL, ElementType::WIND, {5, 5}}
            }
        },
    }},
    {3, {"サラリ", "3", 1, 1600, 600, 5, ElementType::WATER, {WeaponType::CANE},
        {"めいきょうしすい", "味方全体のＨＰを回復(特大) / 気絶した仲間を復活させる(HP:50%)", "", 1,
            {
                {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::WATER, {525, 625}},
                {EffectType::RESURRECTION, TargetType::PARTY_ALL, ElementType::WATER, {45, 55}},
            }
        },
    }},
//    {4, {"ミケーラ", "4", 1, 1500, 540, 5, ElementType::WIND, {WeaponType::KNIFE, WeaponType::ARCH, WeaponType::AX},
//        {
//            {"こうげき", "", "", 0,
//                {
//                    {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {95, 105}}
//                }
//            },
//            {"ウィンド", "敵単体に風属性ダメージ", "", 1,
//                {
//                    {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WIND, {150, 200}}
//                }
//            },
//            {"スナッチ", "敵単体のAPを-1する / 自分のAPを+1する", "", 3,
//                {
//                    {EffectType::AP_DOWN, TargetType::ENEMY_ONE, ElementType::WEAPON, {1, 1}},
//                    {EffectType::AP_UP, TargetType::OWN, ElementType::WEAPON, {1, 1}}
//                }
//            },
//            {"ワイルドラッシュ", "敵単体に武器属性ダメージ / ターゲットランダムで4回繰り返す", "", 3,
//                {
//                    {EffectType::DAMAGE, TargetType::ENEMY_RANDOM_4, ElementType::WEAPON, {125, 150}}
//                }
//            },
//        },
//    }},
    {11, {"ばうわう", "11", -1, 50000, 300, 3, ElementType::WIND, {WeaponType::ENEMY},
        {"ストームブラスト", "", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::WEAPON, {150, 200}},
            }
        },
    }},
    {12, {"あるみらじ", "12", 1, 4000, 200, 4, ElementType::FIRE, {WeaponType::ENEMY},
        {"とっしん", "", "", 4,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {250, 300}},
                {EffectType::AP_DOWN, TargetType::ENEMY_ONE, ElementType::WEAPON, {1, 1}}
            }
        },
    }},
    {13, {"きのこりお", "13", 1, 2000, 150, 2, ElementType::WATER, {WeaponType::ENEMY},
        {"たいあたり", "", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {150, 200}}
            }
        },
    }},
};

const std::unordered_map<int, const WeaponData> weaponDatas = {
    { 0, {"なし", WeaponType::ENEMY, ElementType::WEAPON, 0, 0, {0} }},
    { 1, {"せんしのおの", WeaponType::AX, ElementType::FIRE, 200, 200, {1, 2, 3} }},
    { 2, {"もりびとのゆみ", WeaponType::ARCH, ElementType::WIND, 150, 250, {4, 5, 6} }},
    { 3, {"あめふりのつえ", WeaponType::CANE, ElementType::WATER, 100, 300, {7, 8, 9}}},
};

const std::unordered_map<int, const CommandData> commandDatas = {
    { 0, {"こうげき", "", "", 0,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {95, 105}}
        }
    }},
    { 1, {"ぶったぎり", "敵単体に武器属性ダメージ(小)", "", 1,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {125, 150}}
        }
    }},
    { 2, {"おたけび", "味方全体のATを25%アップ(2ターン)", "", 2,
        {
            {EffectType::ATK_UP, TargetType::PARTY_ALL, ElementType::WEAPON, {25, 2}},
        }
    }},
    { 3, {"あばれまわる", "敵全体に武器属性ダメージ(中)", "", 3,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::WEAPON, {200, 250}}
        }
    }},
    { 4, {"どくや", "敵単体に武器属性ダメージ(小) / 対象に3ターンの継続ダメージ", "", 2,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {125, 150}},
            {EffectType::POISON, TargetType::ENEMY_ONE, ElementType::WEAPON, {35, 3}}
        }
    }},
    { 5, {"かげぬい", "敵単体に武器属性ダメージ(小) / 対象のAPを-1する", "", 3,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {125, 150}},
            {EffectType::AP_DOWN, TargetType::ENEMY_ONE, ElementType::WEAPON, {1, 1}},
        }
    }},
    { 6, {"やのあらし", "敵全体に武器属性ダメージ(中)", "", 3,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::WEAPON, {200, 250}}
        }
    }},
    { 7, {"いのちのみず", "現在のＨＰが一番少ない味方単体のＨＰを回復(小)", "", 2,
        {
            {EffectType::HEAL, TargetType::PARTY_ONE, ElementType::WATER, {125, 150}}
        }
    }},
    { 8, {"こおりのやいば", "敵単体に水属性ダメージ(中)", "", 2,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WATER, {200, 250}}
        }
    }},
    { 9, {"いやしのあめ", "味方全体のＨＰを回復(中)", "", 3,
        {
            {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::WATER, {200, 250}}
        }
    }},
    {10, {"みだれうち", "敵単体に風属性ダメージ(小) / ターゲットランダムで4回繰り返す", "", 3,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_RANDOM_4, ElementType::WEAPON, {125, 150}}
        }
    }},
    {11, {"まぼろしのきり", "自分が受けるダメージを0にする(1ターン)", "", 1,
        {
            {EffectType::DAMAGE_CUT, TargetType::OWN, ElementType::WEAPON, {100, 1}}
        }
    }},
};


const std::unordered_map<WeaponType, const CodeName> weaponCodes = {
    {WeaponType::SWORD, {"剣", "sword"}},
    {WeaponType::LANCE, {"槍", "lance"}},
    {WeaponType::ARCH,  {"弓", "arch"}},
    {WeaponType::CANE,  {"杖", "cane"}},
    {WeaponType::AX,    {"斧", "ax"}},
    {WeaponType::KNIFE, {"短剣", "knife"}},
    {WeaponType::ENEMY, {"", "enemy"}},
};

const std::unordered_map<ElementType, const CodeName> elementCodes = {
    {ElementType::FIRE,  {"火", "fire", Color3B(138, 0, 0)}},
    {ElementType::WATER, {"水", "water", Color3B(0, 0, 138)}},
    {ElementType::EARTH, {"土", "earth", Color3B(138, 68, 0)}},
    {ElementType::WIND,  {"風", "wind", Color3B(0, 138, 0)}},
};

