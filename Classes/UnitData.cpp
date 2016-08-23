//
//  UnitData.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/08/23.
//
//

#include "UnitData.h"

const std::unordered_map<int, const UnitData> partyUnitDatas = {
    {1, {"ラグナス", 1600, 650, {WeaponType::AX, WeaponType::SWORD, WeaponType::LANCE}, {1, 2, 3}} },
    {2, {"アレックス", 1200, 480, {WeaponType::CANE, WeaponType::ARCH, WeaponType::KNIFE}, {4, 5, 6}} },
    {3, {"ソフィア", 1500, 600, {WeaponType::LANCE, WeaponType::CANE, WeaponType::SWORD}, {7, 8, 9}} },
    {4, {"ミケーラ", 1400, 540, {WeaponType::KNIFE, WeaponType::ARCH, WeaponType::AX}, {10, 11, 12}} },
};

const std::unordered_map<int, const EnemyData> enemyUnitDatas = {
    {1, {"グリーンドラゴン", "s_dragon_green", 12000, 450, 4,
        {
            {"ファイアブレス", "", 0,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::FIRE, {300, 350}},
                    {EffectType::ATK_DOWN, TargetType::ENEMY_ALL, ElementType::FIRE, {20, 1}}
                }
            }
        },
    }},
    {2, {"くま", "s_bear", 4000, 240, 4,
        {
            {"ファイアブレス", "", 0,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::FIRE, {300, 350}},
                    {EffectType::ATK_DOWN, TargetType::ENEMY_ALL, ElementType::FIRE, {20, 1}}
                }
            }
        },
    }},
    {3, {"ねずみ", "s_rat", 2000, 180, 4,
        {
            {"ファイアブレス", "", 0,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::FIRE, {300, 350}},
                    {EffectType::ATK_DOWN, TargetType::ENEMY_ALL, ElementType::FIRE, {20, 1}}
                }
            }
        },
    }},
};

const std::unordered_map<int, const WeaponData> weaponDatas = {
    {1, {"バトルアクス", WeaponType::AX, ElementType::FIRE, 200, 150, 80, 8,
        {"ファイアブリッツ", "敵単体に火属性ダメージ(中) / 攻撃後、自分のATKを30%アップ(1ターン)",
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::FIRE, {250, 300}},
                {EffectType::ATK_UP, TargetType::OWN, ElementType::FIRE, {30, 1}}
            }
        }
    }},
    {2, {"ロングケーン", WeaponType::CANE, ElementType::EARTH, 80, 240, 96, 4,
        {"クラックスペル", "敵全体に土属性ダメージ(小) / APを-1する",
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::EARTH, {150, 200}},
                {EffectType::AP_DOWN, TargetType::ENEMY_ALL, ElementType::EARTH, {1, 1}}
            }
        }
    }},
    {3, {"トライデント", WeaponType::LANCE, ElementType::WATER, 320, 120, 88, 4,
        {"アクアスラスト", "敵単体に水属性ダメージ(中) / 攻撃後、自分にダメージカット40%を付与(1ターン)",
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WATER, {250, 300}},
                {EffectType::DAMAGE_CUT, TargetType::OWN, ElementType::WATER, {40, 1}}
            }
        }
    }},
    {4, {"ククリナイフ", WeaponType::KNIFE, ElementType::WIND, 100, 120, 96, 16,
        {"ゲイルストライク", "敵単体に風属性ダメージ(大)",
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WIND, {450, 500}}
            }
        }
    }},
};

const std::unordered_map<int, const CommandData> commandDatas = {
    { 0, {"こうげき", "", 0,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {95, 105}}
        }
    }},
    {-1, {"ウェポンバースト", "", 100,
        {
            {EffectType::WEAPON_BURST, TargetType::OWN, ElementType::WEAPON, {0, 0}}
        }
    }},

    { 1, {"ウォークライ", "味方全体のATKを20%アップ(1ターン)", 3,
        {
            {EffectType::ATK_UP, TargetType::PARTY_ALL, ElementType::FIRE, {20, 1}}
        }
    }},
    { 2, {"アーマーブレイク", "敵単体に火属性ダメージ / ガードブレイク15%を付与(3ターン)", 2,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::FIRE, {150, 200}},
            {EffectType::GUARD_BREAK, TargetType::ENEMY_ONE, ElementType::FIRE, {15, 3}}
        }
    }},
    { 3, {"なし", "", 0,
        {
            {EffectType::ATK_UP, TargetType::PARTY_ALL, ElementType::FIRE, {20, 1}}
        }
    }},
    { 4, {"クイックヒール", "味方単体のHPを回復", 1,
        {
            {EffectType::HEAL, TargetType::PARTY_ONE, ElementType::EARTH, {100, 120}}
        }
    }},
    { 5, {"オールヒール", "味方全体のHPを回復", 4,
        {
            {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::EARTH, {75, 100}}
        }
    }},
    { 6, {"なし", "", 0,
        {
            {EffectType::ATK_UP, TargetType::PARTY_ALL, ElementType::FIRE, {20, 1}}
        }
    }},
    { 7, {"ランパート", "味方全体にダメージカット40%を付与(2ターン)", 3,
        {
            {EffectType::DAMAGE_CUT, TargetType::PARTY_ALL, ElementType::WATER, {40, 3}}
        }
    }},
    { 8, {"リフレッシュ", "味方単体の弱体効果を1つ取り除く", 1,
        {
            {EffectType::REFRESH, TargetType::PARTY_ONE, ElementType::WATER, {1, 1}}
        }
    }},
    { 9, {"なし", "", 0,
        {
            {EffectType::ATK_UP, TargetType::PARTY_ALL, ElementType::FIRE, {20, 1}}
        }
    }},
    {10, {"スナッチ", "敵単体のAPを-1する / 自分のAPを+1する", 3,
        {
            {EffectType::AP_DOWN, TargetType::ENEMY_ONE, ElementType::WIND, {1, 1}},
            {EffectType::AP_UP, TargetType::OWN, ElementType::WIND, {1, 1}}
        }
    }},
    {11, {"ミラージュ", "自分に無敵効果を付与する(1ターン)", 3,
        {
            {EffectType::INVICIBLE, TargetType::OWN, ElementType::WIND, {1, 1}}
        }
    }},
    {12, {"なし", "", 0,
        {
            {EffectType::ATK_UP, TargetType::PARTY_ALL, ElementType::FIRE, {20, 1}}
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

