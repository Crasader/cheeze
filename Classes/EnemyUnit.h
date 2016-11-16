//
//  EnemyUnit.h
//  cheeze
//
//  Created by 上野 真史 on 2016/08/24.
//
//

#ifndef __cheeze__EnemyUnit__
#define __cheeze__EnemyUnit__

#include "cocos2d.h"
#include "BattleUnit.h"

class EnemyUnit : public BattleUnit
{
public:
    EnemyUnit(const int unitId, Node* csb)
    : BattleUnit(unitId, static_cast<WeaponId>(0), true, csb) {}
    virtual void appendTo(Node* node, const int position, const float scale = 0.5f);
    virtual ~EnemyUnit() = default;
    inline bool isSkill() { return getAP() >= getAPMax(); };
    void attack();
    void damaged(const int damage, const bool weak, const WeaponType weaponType);
    void healed(const int heal);
    void turnChange();
private:
    void init();
};

#endif /* defined(__cheeze__EnemyUnit__) */
