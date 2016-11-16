//
//  ItemData.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/11/09.
//
//

#include "ItemData.h"

const std::unordered_map<ItemId, const ItemData> itemDatas = {
    {ItemId::COIN, {"おばけコイン", "アイテムの購入に利用します", "icon_coin", ItemType::COIN, {}, {} } },
    {ItemId::PUMPKIN_COIN, {"かぼちゃコイン", "カボチャの王を討伐した証 / 特別なアイテムと交換できる", "icon_coin_pumpkin", ItemType::COIN, {}, {} } },
    {ItemId::HEAL, {"かいふくやく", "味方単体のＨＰを回復", "item_potion_heal", ItemType::BATTLE,
        {{ItemId::COIN, 100}},
        {
            {EffectType::HEAL, TargetType::PARTY_ONE, ElementType::SELF, {450, 550}}
        }
    }},
    {ItemId::HEAL_ALL, {"いやしのエキス", "味方全体のＨＰを回復", "item_potion_heal_all", ItemType::BATTLE,
        {{ItemId::COIN, 300}},
        {
            {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::SELF, {440, 520}}
        }
    }},
    {ItemId::RESURRECTION, {"きつけぐすり", "味方単体を気絶から復活させる", "item_potion_raise", ItemType::BATTLE,
        {{ItemId::COIN, 1000}},
        {
            {EffectType::RESURRECTION, TargetType::PARTY_ONE, ElementType::SELF, {220, 260}}
        }
    }},
    {ItemId::AP_UP, {"しゅんそくのはね", "味方単体のAPを+1する", "item_ap_wing", ItemType::BATTLE,
        {{ItemId::COIN, 150}},
        {
            {EffectType::AP_UP, TargetType::PARTY_ONE, ElementType::SELF, {1, 1}}
        }
    }},
    {ItemId::MORE_DROP, {"こううんのよつば", "敵単体のドロップアイテム数を+1する", "item_lucky_clover", ItemType::BATTLE,
        {{ItemId::COIN, 2500}},
        {
            {EffectType::MORE_DROP, TargetType::ENEMY_ONE, ElementType::SELF, {1000, 1000}}
        }
    }},
};


const std::unordered_map<WeaponId, const WeaponData> weaponDatas = {
    {WeaponId::NONE, {"なし", "none", WeaponType::ENEMY, 0, 0, {} }},
    {WeaponId::SWORD_1, {"バスタードソード", "bustered", WeaponType::SWORD, 100, 300, {
        {"ぶったぎり", "敵単体に自属性ダメージ(小)", "", 1,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}}
            }
        },
        {"ぶんまわす", "敵全体に自属性ダメージ(小)", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::SELF, {125, 150}}
            }
        },
        {"らんぺーじ", "敵単体に自属性ダメージ(中) / 3回繰り返す", "", 4,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {200, 250}},
                {EffectType::DAMAGE, TargetType::SAME, ElementType::SELF, {200, 250}},
                {EffectType::DAMAGE, TargetType::SAME, ElementType::SELF, {200, 250}}
            }
        }
    }}},
    {WeaponId::SWORD_2, {"きしのつるぎ", "knight", WeaponType::SWORD, 250, 150, {
        {"じゅうじぎり", "敵単体に自属性ダメージ(小) / 自属性の追加ダメージ(小)", "", 1,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {60, 75}},
                {EffectType::DAMAGE, TargetType::SAME, ElementType::SELF, {65, 75}}
            }
        },
        {"まもりのかべ", "味方全体が受けるダメージを40%カット", "", 3,
            {
                {EffectType::DAMAGE_CUT, TargetType::PARTY_ALL, ElementType::SELF, {40, 1}},
            }
        },
        {"いやしのひかり", "味方全体のＨＰを回復(小)", "", 3,
            {
                {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::SELF, {75, 100}},
            }
        },
    }}},
    {WeaponId::SWORD_3, {"とうぞくのけん", "thief", WeaponType::SWORD, 180, 220, {
        {"まぼろしのきり", "自分が受けるダメージを0にする(1ターン)", "", 1,
            {
                {EffectType::DAMAGE_CUT, TargetType::OWN, ElementType::SELF, {100, 1}}
            }
        },
        {"どろぼうぎり", "敵単体に自属性ダメージ(小) / 対象のAPを-1する / 自分のAPを+1する", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}},
                {EffectType::AP_DOWN, TargetType::SAME, ElementType::SELF, {1, 1}},
                {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {1, 1}},
            }
        },
        {"みだれぎり", "敵単体に自属性ダメージ(小) / 時々自分のAPを+1する / ターゲットランダムで4回繰り返す", "", 4,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}},
                {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {0, 1}},
            }
        },
    }}},
    {WeaponId::AX_1, {"パンプキンアクス", "pumpkin_ax", WeaponType::AX, 300, 400, {
        {"ぶんまわす", "敵全体に自属性ダメージ(小)", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::SELF, {125, 150}}
            }
        },
        {"まもりのかべ", "味方全体が受けるダメージを60%カット", "", 3,
            {
                {EffectType::DAMAGE_CUT, TargetType::PARTY_ALL, ElementType::SELF, {60, 1}},
            }
        },
        {"かぼちゃぎり", "敵単体に自属性ダメージ(特大) / 自分の状態異常を3つ除去する", "", 4,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {525, 625}},
                {EffectType::REFRESH, TargetType::OWN, ElementType::SELF, {3, 3}}
            }
        },
    }}},
    {WeaponId::LANCE_1, {"てんかいのやり", "valkyrie", WeaponType::LANCE, 280, 120, {
        {"つきさす", "敵単体に自属性ダメージ(小)", "", 1,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}}
            }
        },
        {"まもりのかべ", "味方全体が受けるダメージを2ターンの間25%カットする", "", 3,
            {
                {EffectType::DAMAGE_CUT, TargetType::PARTY_ALL, ElementType::SELF, {25, 2}},
            }
        },
        {"きせきのひかり", "現在のＨＰが一番少ない味方単体のＨＰを回復(大)", "", 3,
            {
                {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::SELF, {160, 200}},
            }
        },
    }}},
    {WeaponId::ARCH_1, {"もりびとのゆみ", "forest", WeaponType::ARCH, 180, 220, {
        {"どくや", "敵単体に自属性ダメージ(小) / 対象に3ターンの継続ダメージ", "", 1,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {45, 60}},
                {EffectType::POISON, TargetType::SAME, ElementType::SELF, {30, 3}}
            }
        },
        {"あしどめのや", "敵単体に武器属性ダメージ(小) / 対象のAPを-1する", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {100, 125}},
                {EffectType::AP_DOWN, TargetType::SAME, ElementType::SELF, {1, 1}},
            }
        },
        {"やのあらし", "敵全体に自属性ダメージ(中)", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::SELF, {200, 250}}
            }
        },
    }}},
    {WeaponId::ARCH_2, {"マスケットじゅう", "masket", WeaponType::ARCH,  160, 240, {
        {"しんこきゅう", "自分のAPを+2する", "", 1,
            {
                {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {2, 2}}
            }
        },
        {"ねらいうち", "自分の次の攻撃のダメージをアップする(大)", "", 3,
            {
                {EffectType::ATK_UP, TargetType::OWN, ElementType::SELF, {50, 1}},
            }
        },
        {"みだれうち", "敵単体に自属性ダメージ(小) / ターゲットランダムで4回繰り返す", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}}
            }
        },
    }}},
    {WeaponId::ARCH_3, {"パンプキンボウ", "pumpkin_bow", WeaponType::ARCH, 350, 350, {
        {"しんこきゅう", "自分のAPを+2する", "", 1,
            {
                {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {2, 2}}
            }
        },
        {"みだれうち", "敵単体に自属性ダメージ(小) / ターゲットランダムで4回繰り返す", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}}
            }
        },
        {"やのあらし", "敵全体に自属性ダメージ(大)", "", 4,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::SELF, {325, 400}}
            }
        },
    }}},
    {WeaponId::CANE_1, {"あめふりのつえ", "rain", WeaponType::CANE, 200, 200, {
        {"いのちのみず", "現在のＨＰが一番少ない味方単体のＨＰを回復(小)", "", 1,
            {
                {EffectType::HEAL, TargetType::PARTY_ONE, ElementType::WATER, {75, 100}}
            }
        },
        {"みずでっぽう", "敵単体に水属性ダメージ(大)", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WATER, {325, 400}}
            }
        },
        {"いやしのあめ", "味方全体のＨＰを回復(中)", "", 3,
            {
                {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::WATER, {100, 125}}
            }
        },
    }}},
    {WeaponId::CANE_2, {"ほしよみのつえ", "star", WeaponType::CANE, 200, 200, {
        {"しんこきゅう", "自分のAPを+2する", "", 1,
            {
                {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {2, 2}}
            }
        },
        {"ぐらびてぃ", "敵全体のAPを-1する / 時々さらにAPを-1する", "", 3,
            {
                {EffectType::AP_DOWN, TargetType::ENEMY_ALL, ElementType::SELF, {1, 1}},
                {EffectType::AP_DOWN, TargetType::ENEMY_ALL, ElementType::SELF, {0, 1}}
            }
        },
        {"いんせきおとし", "敵単体に無属性ダメージ(特大)", "", 5,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::NONE, {525, 625}}
            }
        },
    }}},
    {WeaponId::CANE_3, {"パンプキンロッド", "pumpkin_rod", WeaponType::CANE, 250, 450, {
        {"しんこきゅう", "自分のAPを+2する", "", 1,
            {
                {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {2, 2}}
            }
        },
        {"しんこきゅう", "自分のAPを+2する", "", 1,
            {
                {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {2, 2}}
            }
        },
        {"しんこきゅう", "自分のAPを+2する", "", 1,
            {
                {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {2, 2}}
            }
        },
    }}},
    {WeaponId::MUSIC_1, {"そよかぜのハープ", "wind_harp", WeaponType::MUSIC, 200, 200, {
        {"いやしのかぜ", "味方全体のＨＰを回復(小) / 味方全体のHPを2ターン継続回復する", "", 2,
            {
                {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::WIND, {45, 60}},
                {EffectType::REGENE, TargetType::PARTY_ALL, ElementType::WIND, {25, 2}},
            }
        },
        {"しんこきゅう", "自分のAPを+2する", "", 1,
            {
                {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {2, 2}}
            }
        },
        {"しんこきゅう", "自分のAPを+2する", "", 1,
            {
                {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {2, 2}}
            }
        },
    }}},
};

