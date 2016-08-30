//
//  UnitData.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/08/23.
//
//

#include "UnitData.h"

const std::unordered_map<int, const UnitData> partyUnitDatas = {
    {1, {"ラグナス", "Party/character_1", 1800, 650, 5, ElementType::FIRE, {WeaponType::AX, WeaponType::SWORD, WeaponType::LANCE},
        {
            {"こうげき", "", "", 0,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {95, 105}}
                }
            },
            {"ストライク", "敵単体に武器属性ダメージ", "", 1,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {150, 200}}
                }
            },
            {"アーマーブレイク", "敵単体に武器属性ダメージ / ガードブレイク15%を付与(3ターン)", "", 2,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {150, 200}},
                    {EffectType::GUARD_BREAK, TargetType::ENEMY_ONE, ElementType::WEAPON, {15, 3}}
                }
            },
            {"ウォークライ", "味方全体のATKを20%アップ(1ターン)", "", 3,
                {
                    {EffectType::ATK_UP, TargetType::PARTY_ALL, ElementType::WEAPON, {20, 1}}
                }
            },
        }
    }},
    {2, {"アレックス", "Party/character_2", 1400, 480, 5, ElementType::EARTH, {WeaponType::CANE, WeaponType::ARCH, WeaponType::KNIFE},
        {
            {"こうげき", "", "", 0,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {95, 105}}
                }
            },
            {"クラック", "敵全体に土属性ダメージ", "", 2,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::EARTH, {75, 100}}
                }
            },
            {"アースヒール", "味方全体のHPを回復", "", 4,
                {
                    {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::EARTH, {60, 75}}
                }
            },
            {"ディスペル", "敵単体の強化効果を1つ取り除く", "", 3,
                {
                    {EffectType::ATK_UP, TargetType::PARTY_ALL, ElementType::WEAPON, {20, 1}}
                }
            },
        },
    }},
    {3, {"ソフィア", "Party/character_3", 1600, 600, 5, ElementType::WATER, {WeaponType::LANCE, WeaponType::CANE, WeaponType::SWORD},
        {
            {"こうげき", "", "", 0,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {95, 105}}
                }
            },
            {"ペネトレイト", "敵単体に武器属性ダメージ / ダメージカットを無視する", "", 2,
                {
                    {EffectType::PENETRATE, TargetType::PARTY_ALL, ElementType::WEAPON, {40, 60}},
                    {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {125, 150}}
                }
            },
            {"クイックヒール", "現在のＨＰが一番少ない味方単体のＨＰを回復", "", 2,
                {
                    {EffectType::HEAL, TargetType::PARTY_ONE, ElementType::WEAPON, {75, 100}}
                }
            },
            {"リフレッシュ", "味方全体の弱体効果を1つ取り除く", "", 2,
                {
                    {EffectType::REFRESH, TargetType::PARTY_ONE, ElementType::WEAPON, {1, 1}}
                }
            },
        },
    }},
    {4, {"ミケーラ", "Party/character_4", 1500, 540, 5, ElementType::WIND, {WeaponType::KNIFE, WeaponType::ARCH, WeaponType::AX},
        {
            {"こうげき", "", "", 0,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {95, 105}}
                }
            },
            {"ウィンド", "敵単体に風属性ダメージ", "", 1,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WIND, {150, 200}}
                }
            },
            {"スナッチ", "敵単体のAPを-1する / 自分のAPを+1する", "", 3,
                {
                    {EffectType::AP_DOWN, TargetType::ENEMY_ONE, ElementType::WEAPON, {1, 1}},
                    {EffectType::AP_UP, TargetType::OWN, ElementType::WEAPON, {1, 1}}
                }
            },
            {"ワイルドラッシュ", "敵単体に武器属性ダメージ / ターゲットランダムで4回繰り返す", "", 3,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_RANDOM_4, ElementType::WEAPON, {125, 150}}
                }
            },
        },
    }},
};

const std::unordered_map<int, const UnitData> enemyUnitDatas = {
    {1, {"グリーンドラゴン", "Monster/s_dragon_green", 50000, 450, 3, ElementType::WIND, {WeaponType::ENEMY},
        {
            {"こうげき", "", "", 0,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {95, 105}}
                }
            },
            {"ストームブラスト", "", "skill_fire_breath", 3,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::WEAPON, {150, 200}},
                }
            }
        },
    }},
    {2, {"くま", "Monster/s_bear", 4000, 240, 4, ElementType::FIRE, {WeaponType::ENEMY},
        {
            {"こうげき", "", "", 0,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {95, 105}}
                }
            },
            {"とっしん", "", "skill_fire_breath", 4,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {250, 300}},
                    {EffectType::AP_DOWN, TargetType::ENEMY_ONE, ElementType::WEAPON, {1, 1}}
                }
            }
        },
    }},
    {3, {"ねずみ", "Monster/s_rat", 2000, 180, 2, ElementType::WATER, {WeaponType::ENEMY},
        {
            {"こうげき", "", "", 0,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {95, 105}}
                }
            },
            {"たいあたり", "", "skill_fire_breath", 2,
                {
                    {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {150, 200}}
                }
            }
        },
    }},
};

const std::unordered_map<int, const WeaponData> weaponDatas = {
    {0, {"なし", WeaponType::ENEMY, ElementType::WEAPON, 0, 0, 0, 0, 0 }},
    {1, {"バトルアクス", WeaponType::AX, ElementType::FIRE, 200, 150, 80, 8, 1 }},
    {2, {"ロングケーン", WeaponType::CANE, ElementType::EARTH, 80, 240, 96, 4, 2 }},
    {3, {"トライデント", WeaponType::LANCE, ElementType::WATER, 320, 120, 88, 4, 3}},
    {4, {"ククリナイフ", WeaponType::KNIFE, ElementType::WIND, 100, 120, 96, 16, 4}},
};

const std::unordered_map<int, const CommandData> weaponBurstDatas = {
    { 0, {"ストライク", "敵単体に武器属性ダメージ", "", 100,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WEAPON, {100, 150}},
        }
    }},
    { 1, {"ファイアブリッツ", "敵単体に火属性ダメージ(中) / 攻撃後、自分のATKを30%アップ(1ターン)", "", 100,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::FIRE, {500, 600}},
            {EffectType::ATK_UP, TargetType::OWN, ElementType::FIRE, {30, 1}}
        }
    }},
    { 2, {"アースクエイク", "敵全体に土属性ダメージ(小) / APを-1する", "", 100,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::EARTH, {300, 350}},
            {EffectType::AP_DOWN, TargetType::ENEMY_ALL, ElementType::EARTH, {1, 1}}
        }
    }},
    { 3, {"アクアスラスト", "敵単体に水属性ダメージ(中) / 攻撃後、自分にダメージカット40%を付与(1ターン)", "", 100,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WATER, {500, 600}},
            {EffectType::DAMAGE_CUT, TargetType::OWN, ElementType::WATER, {40, 1}}
        }
    }},
    { 4, {"ゲイルストライク", "敵単体に風属性ダメージ(大)", "", 100,
        {
            {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WIND, {800, 900}}
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

