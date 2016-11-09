//
//  ItemData.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/11/09.
//
//

#include "ItemData.h"

const std::unordered_map<ItemId, const ItemData> itemDatas = {
//    const std::string name;
//    const std::string explain;
//    const std::string code;
//    const std::vector<Money> prices;
//    const std::vector<EffectData> effect_datas;
    {ItemId::COIN, {"おばけコイン", "この世界の通貨として利用されている", "icon_coin", {}, {} } },
    {ItemId::PUMPKIN_COIN, {"かぼちゃコイン", "カボチャの王を討伐した証 / 特別な武器と交換できる", "icon_coin", {}, {} } },
    {ItemId::HEAL, {"かいふくやく", "味方単体のＨＰを回復", "item_potion_heal",
        {{ItemId::COIN, 100}},
        {
            {EffectType::HEAL, TargetType::PARTY_ONE, ElementType::SELF, {450, 550}}
        }
    }},
    {ItemId::HEAL_ALL, {"いやしのエキス", "味方全体のＨＰを回復", "item_potion_heal_all",
        {{ItemId::COIN, 300}},
        {
            {EffectType::HEAL, TargetType::PARTY_ALL, ElementType::SELF, {440, 520}}
        }
    }},
    {ItemId::RESURRECTION, {"きつけぐすり", "味方単体を気絶から復活させる", "item_potion_raise",
        {{ItemId::COIN, 1000}},
        {
            {EffectType::RESURRECTION, TargetType::PARTY_ONE, ElementType::SELF, {220, 260}}
        }
    }},
    {ItemId::AP_UP, {"しゅんそくのはね", "味方単体のAPを+1する", "item_ap_wing",
        {{ItemId::COIN, 150}},
        {
            {EffectType::AP_UP, TargetType::PARTY_ONE, ElementType::SELF, {1, 1}}
        }
    }},
    {ItemId::MORE_DROP, {"こううんのよつば", "敵単体のドロップアイテム数を+1する", "item_lucky_clover",
        {{ItemId::COIN, 2500}},
        {
            {EffectType::MORE_DROP, TargetType::ENEMY_ONE, ElementType::SELF, {1000, 1000}}
        }
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
    {10, {"パンプキンアクス", WeaponType::SWORD, 150, 150, {12, 16, 17} }},
    {11, {"パンプキンランス", WeaponType::ARCH,  350,  50, { 4,  5, 11} }},
    {12, {"パンプキンケーン", WeaponType::CANE,  200, 200, {13, 14, 15} }},
};

