//
//  MemberStatusBox.h
//  cheeze
//
//  Created by 上野 真史 on 2016/08/23.
//
//

#ifndef __cheeze__MemberStatusBox__
#define __cheeze__MemberStatusBox__

#include "cocos2d.h"
#include "Touchable.h"

class UnitData;
class WeaponData;
enum class WeaponId : int;
enum class WeaponType : int;

using namespace cocos2d;

class MemberStatusBox : private Touchable
{
public:
    virtual void appendTo(PageView* pageView, const int position);
    virtual ~MemberStatusBox() = default;
    void setAction(const std::string name, const Callback& action);
private:
    void init();
    void setStatus();
    void setWeapon();
    inline Node* getCsb(){ return _csb; };
    Node* _csb { nullptr };
    const UnitData& getUnitData() const;
    const WeaponData& getWeaponData() const;
    inline const int getPosition() const { return _position; }
    int _position { -1 };
    Node* _menuLabels { nullptr };
    Node* _basicLabels { nullptr };
    Node* _labels { nullptr };
    
    inline const int getCharacterId() const { return _characterId; }
    inline const WeaponId getWeaponId() const { return _weaponId; }
    int _characterId { 0 };
    WeaponId _weaponId { static_cast<WeaponId>(0) };
};

#endif /* defined(__cheeze__MemberStatusBox__) */
