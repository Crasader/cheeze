//
//  MemberListBox.h
//  cheeze
//
//  Created by 上野 真史 on 2016/08/23.
//
//

#ifndef __cheeze__MemberListBox__
#define __cheeze__MemberListBox__

#include "cocos2d.h"
#include "Touchable.h"

class UnitData;
class WeaponData;

using namespace cocos2d;

class MemberListBox : private Touchable
{
public:
    virtual void appendTo(ListView* list, const int position, ImageView* avatar);
    virtual ~MemberListBox() = default;
    inline const int getCommandNumber() const { return _command; }
    void attack();
    const int getAtk();
private:
    void init();
    void setHP();
    void setAP();
    void setTP();
    inline void addAP() { _ap++; };
    inline void addTP(const int point) { _tp += point; if(_tp > 100) _tp = 100; };
    void setCommands();
    void setCommand(const int number);
    void selectCommands(const int number = 0);
    
    inline ImageView* getAvatar(){ return _avatar; };
    ImageView* _avatar { nullptr };
    inline Node* getCsb(){ return _csb; };
    Node* _csb { nullptr };
    const UnitData& getUnitData() const;
    const WeaponData& getWeaponData() const;
    inline const int getPosition() const { return _position; }
    int _position { -1 };
    inline const int getHP() const { return _hp; }
    inline const int getHPMax() const { return _hpMax; }
    int _hp { 0 };
    int _hpMax { 0 };
    inline const int getAP() const { return _ap; }
    int _ap { 0 };
    inline const int getTP() const { return _tp; }
    int _tp { 0 };
    inline float getTpPercent(){
        float percent = 100.0f * _tp / 100.0f;
        return percent;
    }
    int _command { 0 };
};

#endif /* defined(__cheeze__MemberListBox__) */
