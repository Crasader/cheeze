//
//  PlayerBase.cpp
//  angel
//
//  Created by Atsushi Yoshida on 2016/05/22.
//
//

#include "PlayerBase.h"
#include "RestClient.h"
#include "CentralClient.h"
#include "Env.h"
#include "SupportFunctions.h"
#include <iomanip>
#include "BGMPlayer.h"

using namespace supportfunctions;

const std::vector<const std::string> PlayerBase::PERMANENT_KEYS = {ID, TOKEN};

void PlayerBase::load()
{
    setPlayData(CentralClient::getInstance()->loadPlayData());
    if(isNew()){
       reset();
    }
}

void PlayerBase::reset()
{
    auto& playData = getPlayData();
    const std::vector<std::string> permanentDatas = {getID(), getToken()};
    playData.clear();
    auto itrK = PERMANENT_KEYS.cbegin();
    auto itrV = permanentDatas.cbegin();
    for(; itrK != PERMANENT_KEYS.cend(); itrK ++){
        playData[*itrK] = *itrV;
        itrV++;
    }
    ValueMap map;
    auto mapKeys = {PROGRESS, GIFT, ITEMS, AUDIO};
    for(auto& k: mapKeys){
        playData[k] = map;
    }
}

void PlayerBase::addItem(const ItemId itemId, const int amount){
    auto& items = getItems();
    auto itemPtr = getItem(itemId);
    ValueMap item;
    if(itemPtr){
        item = *itemPtr;
        if(amount > 0){
            item[ITEM_DATA::AMOUNT] = item[ITEM_DATA::AMOUNT].asInt() + amount;
        }else{
            item[ITEM_DATA::CONSUME] = item[ITEM_DATA::CONSUME].asInt() - amount;
        }
    }else{
        item[ITEM_DATA::AMOUNT] = amount;
        item[ITEM_DATA::CONSUME] = 0;
    }
    items[std::to_string(static_cast<int>(itemId))] = item;
}

void PlayerBase::consumeItem(const ItemId itemId, const int consume){
    addItem(itemId, -consume);
}

void PlayerBase::save()
{
    CentralClient::getInstance()->savePlayData(getPlayData());
}


const std::string PlayerBase::getPlayerId()
{
    auto id = getID();
    if(id.empty()){
        return "-----";
    }
    std::stringstream idSS;
    auto token  = getToken();
    idSS << token.substr(0, PLAYER_ID_PREFIX_SIZE);
    auto userId = std::stoi(id);
    idSS << std::setfill('0') << std::setw(5) << userId;
    return idSS.str();
}

bool PlayerBase::createGift(const std::string& key, const ItemId itemId, const int amount, const std::string& message)
{
    auto& gifts = getGifts();
    if(gifts[key].getType() != Value::Type::NONE){
        return false;
    }
    ValueMap gift;
    gift[GIFT_DATA::ITEM_ID] = static_cast<int>(itemId);
    gift[GIFT_DATA::AMOUNT] = amount;
    gift[GIFT_DATA::MESSAGE] = message;
    gifts[key] = gift;
    return true;
}

bool PlayerBase::consumeGift(const std::string& key)
{
    auto& gifts = getGifts();
    if(gifts[key].getType() == Value::Type::NONE){
        return false;
    }
    auto& gift = gifts[key].asValueMap();
    if(gift[GIFT_DATA::CONSUMED_AT].getType() == Value::Type::NONE){
        auto itemId = static_cast<ItemId>(gift[GIFT_DATA::ITEM_ID].asInt());
        addItem(itemId, gift[GIFT_DATA::AMOUNT].asInt());
        gift[GIFT_DATA::CONSUMED_AT] = getTimeStr();
        return true;
    }
    return false;
}

void PlayerBase::setVolume(const int volume){
    getAudio()[AUDIO_DATA::BGM] = volume;
    BGMPlayer::setVolume(volume);
}

void PlayerBase::setVolumeSE(const int volume){
    getAudio()[AUDIO_DATA::SE] = volume;
    BGMPlayer::setVolumeSE(volume);
};

void PlayerBase::enqueCharge(const ItemId itemId, const int amount)
{
    if(amount == 0){
        return;
    }
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::microseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::microseconds>(epoch);
    long duration = value.count();
    auto k = std::to_string(duration);
    ValueMap map;
    map[CentralClient::AMOUNT] = amount;
    map[CentralClient::ITEM_ID] = static_cast<int>(itemId);
    getChargeQueue()[k] = map;
}
