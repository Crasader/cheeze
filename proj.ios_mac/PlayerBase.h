//
//  PlayerBase.h
//  okeya
//
//  Created by Atsushi Yoshida on 2016/05/22.
//
//

#ifndef __okeya__PlayerBase__
#define __okeya__PlayerBase__

#include "cocos2d.h"
#include <bitset>
#include "SupportFunctions.h"

using namespace cocos2d;

enum class ItemId : int;
static constexpr auto ITEMS = "items";
namespace ITEM_DATA{
    static constexpr auto AMOUNT = "amount";
    static constexpr auto CONSUME = "consume";
}
static constexpr int PLAYER_ID_PREFIX_SIZE = 3;

namespace GIFT_DATA{
    static constexpr auto ITEM_ID = "itemId";
    static constexpr auto AMOUNT = "amount";
    static constexpr auto MESSAGE = "message";
    static constexpr auto CONSUMED_AT = "consumedAt";
}

static constexpr auto AUDIO = "audio";
namespace AUDIO_DATA{
    static constexpr auto ID = "audioId";
    static constexpr auto BGM = "bgmVolume";
    static constexpr auto SE = "seVolume";
}

class PlayerBase
{
public:    
    static constexpr auto TOKEN = "token";
    static constexpr auto GIFT = "gift";
    static constexpr auto ID = "id";
    static constexpr auto LOCAL_CHARGE_QUEUE = "consumeChargeQueue";
    static constexpr auto PROGRESS = "progress";
    static const std::vector<const std::string> PERMANENT_KEYS;
    static constexpr auto MAX_PROGRESS_BITS = 255;

    PlayerBase() = default;
    virtual ~PlayerBase() = default;

    void load();
    virtual void reset();
    inline bool hasToken(){ return getPlayData()[TOKEN].asString().size() > 0; };
    inline ValueMap& getPlayData(){ return _playData; }
    inline const ValueMap& getPlayData() const { return _playData; }
    inline ValueMap& getItems(){
        return getPlayData()[ITEMS].asValueMap();
    }
    inline ValueMap* getItem(const ItemId itemId)
    {
        auto k = std::to_string(static_cast<int>(itemId));
        auto& items = getItems();
        if(items[k].getType() == Value::Type::NONE){
            return nullptr;
        }else{
            return &items[k].asValueMap();
        }
    }
    inline const int getItemCount(const ItemId itemId)
    {
        auto itemPtr = getItem(itemId);
        if(itemPtr){
            auto& item = (*itemPtr);
            auto count = item[ITEM_DATA::AMOUNT].asInt() - item[ITEM_DATA::CONSUME].asInt();
            return count;
        }else{
            return 0;
        }
    }
    inline const int getItemTotalCount(const ItemId itemId)
    {
        auto itemPtr = getItem(itemId);
        if(itemPtr){
            auto& item = (*itemPtr);
            auto count = item[ITEM_DATA::AMOUNT].asInt();
            return count;
        }else{
            return 0;
        }
    }
    virtual void addItem(const ItemId itemId, const int amount);
    virtual void consumeItem(const ItemId itemId, const int consume);
    virtual bool createGift(const std::string& key, const ItemId itemId, const int amount, const std::string& message);
    virtual bool consumeGift(const std::string& key);
    void save();
    bool isNew(){ return getPlayData().size() <= PERMANENT_KEYS.size(); }
    inline const std::string getToken(){ return getPlayData()[TOKEN].asString(); }
    inline const std::string getID(){ return getPlayData()[ID].asString(); }
    inline void setIdToken(const std::string& idToken){
        const auto pos = idToken.find_first_of("-");
        auto& playData = getPlayData();
        playData[TOKEN] = idToken.substr(0, pos);
        playData[ID] = idToken.substr(pos + 1);
    }
    void setPlayData(const ValueMap& vmap){ _playData = vmap; }
    const std::string getPlayerId();
    inline ValueMap& getGifts(){ return getPlayData()[GIFT].asValueMap(); }
    inline ValueMap& getAudio(){ return getPlayData()[AUDIO].asValueMap(); }
    void setVolume(const int volume);
    void setVolumeSE(const int volume);
    inline void setAudioId(const int audioId){ getAudio()[AUDIO_DATA::ID] = audioId; };
    inline const int getVolume(){ return getAudio()[AUDIO_DATA::BGM].asInt(); }
    inline const int getVolumeSE(){ return getAudio()[AUDIO_DATA::SE].asInt(); }
    void enqueCharge(const ItemId itemId, const int amount);
    template <typename T>
    void setProgress(const T value)
    {
        auto& progressMap = getProgressMap();
        auto&& progress = getProgressBits<T>();
        progress.set(static_cast<int>(value));
        auto name = supportfunctions::getClassName<T>();
        progressMap[name] = progress.to_string();
    }
    template <typename T>
    bool isProgressed(const T value)
    {
        auto&& progress = getProgressBits<T>();
        return progress[static_cast<int>(value)];
    }
    inline ValueMap& getProgressMap(){ return getPlayData()[PROGRESS].asValueMap(); }
protected:
    template <typename T>
    std::bitset<MAX_PROGRESS_BITS> getProgressBits()
    {
        auto& progressMap = getProgressMap();
        auto name = supportfunctions::getClassName<T>();
        std::bitset<MAX_PROGRESS_BITS> progress;
        auto v = progressMap[name];
        if(v.getType() == Value::Type::STRING){
            progress = std::bitset<MAX_PROGRESS_BITS>(v.asString());
        }else{
            progress = std::bitset<MAX_PROGRESS_BITS>(0);
        }
        return progress;
    }
    ValueMap& getChargeQueue(){ return getPlayData()[LOCAL_CHARGE_QUEUE].asValueMap(); }
    ValueMap _playData { {} };
};

#endif /* defined(__okeya__PlayerBase__) */
