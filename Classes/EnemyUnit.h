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
    : BattleUnit(unitId, 0, true, csb) {}
    virtual void appendTo(Node* node, const int position);
    virtual ~EnemyUnit() = default;
    inline bool isSkill() { return getAP() >= getAPMax(); };
    void turnChange();
private:
    void init();
};

#endif /* defined(__cheeze__EnemyUnit__) */
