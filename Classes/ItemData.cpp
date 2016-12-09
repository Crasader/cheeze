//
//  ItemData.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/11/09.
//
//

#include "ItemData.h"

const std::unordered_map<ItemId, const ItemData> itemDatas = {
    {ItemId::GHOST_MEDAL, {"おばけメダル", "いろいろなアイテムと交換できる", "icon_coin",
        ItemType::MEDAL, {}, {} }},
    {ItemId::PUMPKIN_MEDAL, {"かぼちゃメダル", "カボチャ武器と交換できる", "icon_coin_pumpkin",
        ItemType::MEDAL, {}, {} }},

    {ItemId::SWEETS_DONUT, {"ドーナツ", "キャラクターの成長に利用する", "sweets_donut",
        ItemType::SWEETS, {}, {} }},
    {ItemId::SWEETS_CANDY_LOLLIPOP, {"ペロキャン", "キャラクターの成長に利用する", "sweets_candy_lollipop",
        ItemType::SWEETS, {}, {} }},
    {ItemId::SWEETS_CHOCOLATE, {"チョコレート", "キャラクターの成長に利用する", "sweets_chocolate",
        ItemType::SWEETS, {}, {} }},
    {ItemId::SWEETS_MACAROON_RED, {"マカロン(イチゴ)", "主にキラリの成長に利用する", "sweets_macaroon_red",
        ItemType::SWEETS, {}, {} }},
    {ItemId::SWEETS_MACAROON_GREEN, {"マカロン(ピスタチオ)", "主にヒラリの成長に利用する", "sweets_macaroon_green",
        ItemType::SWEETS, {}, {} }},
    {ItemId::SWEETS_MACAROON_BLUE, {"マカロン(ソーダ)", "主にサラリの成長に利用する", "sweets_macaroon_blue",
        ItemType::SWEETS, {}, {} }},
    //    {ItemId::SWEETS_COOKIE, {"クッキー", "キャラクターの成長に利用する", "sweets_cookie",
    //        ItemType::SWEETS, {}, {} }},
    //    {ItemId::SWEETS_CANDY, {"キャンディ", "キャラクターの成長に利用する", "sweets_candy",
    //        ItemType::SWEETS, {}, {} }},
    //    {ItemId::SWEETS_PUDDING, {"プリン", "キャラクターの成長に利用する", "sweets_pudding",
    //        ItemType::SWEETS, {}, {} }},
    //    {ItemId::SWEETS_CAKE, {"ケーキ", "キャラクターの成長に利用する", "sweets_cake",
    //        ItemType::SWEETS, {}, {} }},
    
    {ItemId::HEAL, {"かいふくやく", "一番多くのダメージを受けている味方単体のＨＰを回復", "item_potion_heal", ItemType::BATTLE,
        {{ItemId::GHOST_MEDAL, 100}},
        {
            {EffectType::HEAL, TargetType::PARTY_ONE, ElementType::SELF, {350, 450}}
        }
    }},
    {ItemId::HEAL_ALL, {"しんぴのひやく", "味方全体のＨＰを回復", "item_potion_heal_all", ItemType::BATTLE,
        {{ItemId::GHOST_MEDAL, 300}},
        {
            {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::SELF, {300, 400}}
        }
    }},
    {ItemId::RESURRECTION, {"たましいのれいやく", "味方全体を気絶から復活 / 味方全体のＨＰを回復", "item_potion_raise", ItemType::BATTLE,
        {{ItemId::GHOST_MEDAL, 1000}},
        {
            {EffectType::RESURRECTION, TargetType::PARTY_ALL, ElementType::SELF, {240, 250}}
        }
    }},
    {ItemId::AP_UP, {"しゅんそくのはね", "味方全体のAPを+1する", "item_ap_wing", ItemType::BATTLE,
        {{ItemId::GHOST_MEDAL, 250}},
        {
            {EffectType::AP_UP, TargetType::PARTY_ALL, ElementType::SELF, {1, 1}}
        }
    }},
//    {ItemId::MORE_DROP, {"こううんのよつば", "敵単体のドロップアイテム数を+1する", "item_lucky_clover", ItemType::BATTLE,
//        {{ItemId::GHOST_MEDAL, 2500}},
//        {
//            {EffectType::MORE_DROP, TargetType::ENEMY_ONE, ElementType::SELF, {1000, 1000}}
//        }
//    }},
};


// ★1 = 小　 = 125 〜 150
// ★2 = 中　 = 275 〜 330
// ★3 = 大　 = 450 〜 540
// ★4 = 特大 = 650 〜 780
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
                {EffectType::DAMAGE, TargetType::SAME, ElementType::SELF, {250, 280}}
            }
        }
    }}},
    {WeaponId::SWORD_2, {"きしのつるぎ", "knight", WeaponType::SWORD, 250, 150, {
        {"じゅうじぎり", "敵単体に自属性ダメージ(小) / 2回繰り返す", "", 1,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {60, 75}},
                {EffectType::DAMAGE, TargetType::SAME, ElementType::SELF, {65, 75}}
            }
        },
        {"いやしのひかり", "味方全体のＨＰを回復(小)", "", 2,
            {
                {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::SELF, {125, 150}},
            }
        },
        {"みぞぎのあめ", "敵単体に水属性ダメージ(小) / 対象のAPを-1する / ターゲットランダムで3回繰り返す", "", 5,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WATER, {125, 150}},
                {EffectType::AP_DOWN, TargetType::SAME, ElementType::WATER, {1, 1}},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WATER, {125, 150}},
                {EffectType::AP_DOWN, TargetType::SAME, ElementType::WATER, {1, 1}},
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WATER, {125, 150}},
                {EffectType::AP_DOWN, TargetType::SAME, ElementType::WATER, {1, 1}}
            }
        },
    }}},
    {WeaponId::SWORD_3, {"とうぞくのけん", "thief", WeaponType::SWORD, 180, 220, {
        {"しんこきゅう", "自分のAPを+2する", "", 1,
            {
                {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {2, 2}}
            }
        },
        {"どろぼうぎり", "敵単体に自属性ダメージ(小) / 対象のAPを-1する / 自分のAPを+1する", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}},
                {EffectType::AP_DOWN, TargetType::SAME, ElementType::SELF, {1, 1}},
                {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {1, 1}},
            }
        },
        {"おたからねらい", "敵単体のアイテムドロップ数を+1する", "", 4,
            {
                {EffectType::MORE_DROP, TargetType::ENEMY_ONE, ElementType::SELF, {1, 1}},
            }
        },
    }}},
    {WeaponId::AX_1, {"パンプキンアクス", "pumpkin_ax", WeaponType::AX, 300, 400, {
        {"ぶんまわす", "敵全体に自属性ダメージ(小)", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::SELF, {125, 150}}
            }
        },
        {"らんぺーじ", "敵単体に自属性ダメージ(中) / 3回繰り返す", "", 4,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {200, 250}},
                {EffectType::DAMAGE, TargetType::SAME, ElementType::SELF, {200, 250}},
                {EffectType::DAMAGE, TargetType::SAME, ElementType::SELF, {250, 280}}
            }
        },
        {"かぼちゃばくだん", "敵全体に火属性ダメージ(特大) / 敵全体のAPを-1する", "", 5,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::FIRE, {650, 780}},
                {EffectType::AP_DOWN, TargetType::ENEMY_ALL, ElementType::FIRE, {1, 1}}
            }
        }
    }}},
    {WeaponId::LANCE_1, {"てんかいのやり", "valkyrie", WeaponType::LANCE, 280, 120, {
        {"にだんづき", "敵単体に自属性ダメージ(小) / 2回繰り返す", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}},
                {EffectType::DAMAGE, TargetType::SAME, ElementType::SELF, {125, 150}}
            }
        },
        {"こうぼういったい", "敵単体に自属性ダメージ(小) / 一番多くのダメージを受けている味方単体のＨＰを回復(小)", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}},
                {EffectType::HEAL, TargetType::PARTY_ONE, ElementType::WATER, {125, 150}}
            }
        },
        {"きせきのひかり", "味方全体を気絶から復活 / 味方全体のＨＰを回復(中)", "", 5,
            {
                {EffectType::RESURRECTION, TargetType::PARTY_ALL, ElementType::SELF, {275, 330}}
            }
        },
    }}},
    {WeaponId::ARCH_1, {"もりびとのゆみ", "forest", WeaponType::ARCH, 180, 220, {
        {"しんこきゅう", "自分のAPを+2する", "", 1,
            {
                {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {2, 2}}
            }
        },
        {"あしどめのや", "敵単体に自属性ダメージ(小) / 対象のAPを-1する", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::SELF, {125, 150}},
                {EffectType::AP_DOWN, TargetType::SAME, ElementType::SELF, {1, 1}},
            }
        },
        {"やのあらし", "敵全体に自属性ダメージ(中)", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::SELF, {275, 330}}
            }
        },
    }}},
    {WeaponId::ARCH_2, {"マスケットじゅう", "masket", WeaponType::ARCH,  160, 240, {
        {"しんこきゅう", "自分のAPを+2する", "", 1,
            {
                {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {2, 2}}
            }
        },
        {"ねらいうち", "残りHPが最も少ない敵単体に自属性ダメージ(中)", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE_MIN, ElementType::SELF, {275, 330}},
            }
        },
        {"くろすふぁいあ", "敵単体に火属性ダメージ(中) / 2回繰り返す", "", 4,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::FIRE, {275, 330}},
                {EffectType::DAMAGE, TargetType::SAME, ElementType::FIRE, {275, 330}}
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
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::SELF, {450, 540}}
            }
        },
    }}},
    {WeaponId::CANE_1, {"あめふりのつえ", "rain", WeaponType::CANE, 200, 200, {
        {"いのちのみず", "一番多くのダメージを受けている味方単体のＨＰを回復(小)", "", 1,
            {
                {EffectType::HEAL, TargetType::PARTY_ONE, ElementType::WATER, {125, 150}}
            }
        },
        {"みずでっぽう", "敵単体に水属性ダメージ(中)", "", 2,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::WATER, {275, 330}}
            }
        },
        {"いやしのあめ", "味方全体のＨＰを回復(中)", "", 3,
            {
                {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::WATER, {275, 330}}
            }
        },
    }}},
    {WeaponId::CANE_2, {"ほしよみのつえ", "star", WeaponType::CANE, 200, 200, {
        {"しんこきゅう", "自分のAPを+2する", "", 1,
            {
                {EffectType::AP_UP, TargetType::OWN, ElementType::SELF, {2, 2}}
            }
        },
        {"ぐらびてぃ", "敵全体に無属性ダメージ(小) / 敵全体のAPを-1する / 時々さらにAPを-1する", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::NONE, {125, 150}},
                {EffectType::AP_DOWN, TargetType::ENEMY_ALL, ElementType::NONE, {1, 1}},
                {EffectType::AP_DOWN, TargetType::ENEMY_ALL, ElementType::NONE, {0, 1}}
            }
        },
        {"いんせきおとし", "敵単体に無属性ダメージ(大) / 敵全体に無属性のダメージ(小) ", "", 5,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::NONE, {450, 540}},
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::NONE, {125, 150}}
            }
        },
    }}},
    {WeaponId::CANE_3, {"パンプキンロッド", "pumpkin_rod", WeaponType::CANE, 250, 450, {
        {"いのちのみず", "一番多くのダメージを受けている味方単体のＨＰを回復(小)", "", 1,
            {
                {EffectType::HEAL, TargetType::PARTY_ONE, ElementType::WATER, {125, 150}}
            }
        },
        {"いんせきおとし", "敵単体に無属性ダメージ(大) ", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ONE, ElementType::NONE, {450, 540}}
            }
        },
        {"かぼちゃばくだん", "敵全体に火属性ダメージ(特大) / 敵全体のAPを-1する", "", 5,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::FIRE, {650, 780}},
                {EffectType::AP_DOWN, TargetType::ENEMY_ALL, ElementType::FIRE, {1, 1}}
            }
        }
    }}},
    {WeaponId::MUSIC_1, {"かぜのハープ", "wind_harp", WeaponType::MUSIC, 200, 200, {
        {"そよかぜのうた", "味方全体のＨＰを回復(小)", "", 2,
            {
                {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::WIND, {125, 150}},
            }
        },
        {"こがらしのうた", "敵全体に風属性ダメージ(小) / 対象のAPを-1する", "", 3,
            {
                {EffectType::DAMAGE, TargetType::ENEMY_ALL, ElementType::WIND, {125, 150}},
                {EffectType::AP_DOWN, TargetType::ENEMY_ALL, ElementType::WIND, {1, 1}}
            }
        },
        {"はるかぜのうた", "味方全体のAPを+2する", "", 3,
            {
                {EffectType::AP_UP, TargetType::PARTY_ALL, ElementType::WIND, {2, 2}}
            }
        },
    }}},
};

