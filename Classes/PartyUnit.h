//
//  PartyUnit.h
//  cheeze
//
//  Created by 上野 真史 on 2016/08/23.
//
//

#ifndef __cheeze__PartyUnit__
#define __cheeze__PartyUnit__

#include "cocos2d.h"
#include "BattleUnit.h"

class PartyUnit : public BattleUnit
{
public:
    PartyUnit(const int unitId, const int weaponId, Node* csb)
    : BattleUnit(unitId, weaponId, false, csb) {}
    virtual void appendTo(ListView* list, const int position, Node* avatar);
    virtual ~PartyUnit() = default;
    inline void updateHP(const int point) {
        BattleUnit::updateHP(point);
        setHP();
    };
    inline void updateTP(const int point = random(9, 12)) { _tp += point; if(_tp > 100) _tp = 100; if(_tp < 0) _tp = 0; setTP(); };
    void attack();
    void damaged(const int damage, const bool weak, const WeaponType weaponType);
    void healed(const int heal);
    void turnChange();
private:
    void init();
    void setThumbnail();
    void setHP();
    void setTP();
    void setCommands();
    void setCommand(const int number);
    void selectCommands(const int number = 0);
    inline const int getTP() const { return _tp; }
    int _tp { 0 };
    inline float getTpPercent(){
        float percent = 100.0f * _tp / 100.0f;
        return percent;
    }
    inline void setTouchable() { _untouchable->setVisible(false); };
    inline void setUntouchable() { _untouchable->setVisible(true); };
    ImageView* _untouchable;
};

#endif /* defined(__cheeze__PartyUnit__) */
