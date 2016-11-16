//
//  Player.h
//  cheeze
//
//  Created by 上野 真史 on 2016/11/15.
//
//

#ifndef Player_h
#define Player_h

#include "cocos2d.h"
#include "PlayerBase.h"

const int HOUR = 3600;
const int MINUTE = 60;

static constexpr auto RANK = "rank";
static constexpr auto TOTAL_BATTLE = "totalBattle";

static constexpr auto CHARACTERS = "characters";
namespace CHARACTER_DATA{
    static constexpr auto LEVEL = "level";
    static constexpr auto EQUIP_WEAPON_ID = "equipWeaponId";
}
static constexpr auto WEAPONS = "weapons";
namespace WEAPON_DATA{
    static constexpr auto LEVEL = "level";
    static constexpr auto CREATEED_AT = "created_at";
}
static constexpr auto DEFEAT_GHOSTS = "defeatGhosts";
namespace DEFEAT_GHOST_DATA{
    static constexpr auto COUNT = "count";
}

using namespace cocos2d;

class Player : public PlayerBase
{
public:
    static const std::unordered_map<ItemId, int> INITIAL_ITEMS;
    static const std::unordered_map<int, int> INITIAL_CHARACTERS;
    
    static Player* getInstance();
    
    Player() = default;
    virtual ~Player() = default;
    void load();
    void reset();
    
    inline int getRank(){ return getPlayData()[RANK].asInt(); }
    inline void setRank(const int rank){ getPlayData()[RANK] = rank; }
    inline int rankUp(){ setRank(getRank() + 1); return getRank(); }
    
    inline ValueMap& getCharacters(){ return getPlayData()[CHARACTERS].asValueMap(); }
    inline ValueMap* getCharacter(const int characterId)
    {
        auto k = std::to_string(characterId);
        auto& characters = getCharacters();
        if (characters[k].getType() == Value::Type::NONE) {
            return nullptr;
        } else {
            return &characters[k].asValueMap();
        }
    }
    inline void addCharacter(const int characterId, const int weaponId)
    {
        auto& characters = getCharacters();
        ValueMap character;
        character[CHARACTER_DATA::LEVEL] = 1;
        character[CHARACTER_DATA::EQUIP_WEAPON_ID] = weaponId;
        characters[std::to_string(characterId)] = character;
        save();
    }
    inline const int getCharacterLevel(const int characterId)
    {
        auto& character = *getCharacter(characterId);
        return character[CHARACTER_DATA::LEVEL].asInt();
    }
    inline const int getCharacterWeaponId(const int characterId)
    {
        auto& character = *getCharacter(characterId);
        return character[CHARACTER_DATA::EQUIP_WEAPON_ID].asInt();
    }
    inline void levelUpCharacter(const int characterId)
    {
        auto& character = *getCharacter(characterId);
        auto current = character[CHARACTER_DATA::LEVEL].asInt();
        character[CHARACTER_DATA::LEVEL] = current + 1;
        save();
    }
    inline void changeCharacterWeaponId(const int characterId, const int weaponId)
    {
        auto& character = *getCharacter(characterId);
        character[CHARACTER_DATA::EQUIP_WEAPON_ID] = weaponId;
        save();
    }

    inline ValueMap& getWeapons(){ return getPlayData()[WEAPONS].asValueMap(); }
    inline ValueMap* getWeapon(const int weaponId)
    {
        auto k = std::to_string(weaponId);
        auto& weapons = getWeapons();
        if (weapons[k].getType() == Value::Type::NONE) {
            return nullptr;
        } else {
            return &weapons[k].asValueMap();
        }
    }
    inline void addWeapon(const int weaponId)
    {
        auto& weapons = getWeapons();
        ValueMap weapon;
        weapon[WEAPON_DATA::LEVEL] = 1;
        weapons[std::to_string(weaponId)] = weapon;
        save();
    }
    inline const int getWeaponLevel(const int weaponId)
    {
        auto& weapon = *getWeapon(weaponId);
        auto level = weapon[WEAPON_DATA::LEVEL].asInt();
        return level;
    }
    inline void levelUpWeapon(const int weaponId)
    {
        auto& weapon = *getWeapon(weaponId);
        auto current = weapon[WEAPON_DATA::LEVEL].asInt();
        weapon[WEAPON_DATA::LEVEL] = current + 1;
        save();
    }

    inline const int getTotalBattleCount() { return getPlayData()[TOTAL_BATTLE].asInt(); }
    inline void increaseTotalBattleCount() {
        auto currentCount = getPlayData()[TOTAL_BATTLE].asInt();
        getPlayData()[TOTAL_BATTLE] = currentCount + 1;
        save();
    }
};

#endif /* Player_h */
