//
//  BattleScene.h
//  cheeze
//
//  Created by 上野 真史 on 2016/08/21.
//
//

#ifndef __cheeze__BattleScene__
#define __cheeze__BattleScene__

#include "cocos2d.h"
#include "BaseScene.h"

class PartyUnit;
class EnemyUnit;
enum class TargetType : int;
enum class ElementType : int;

class BattleScene : public BaseScene<BattleScene>
{
public:
    BattleScene();
    virtual ~BattleScene();
    bool init();
    void onEnter();
    //    void onEnterTransitionDidFinish();
private:
    void setPartyMembers();
    void setEnemys();
    void playerAttack();
    void enemyAttack();
    void nextTurn();
    const bool isWeakElement(const ElementType atkType, const ElementType defType);

    inline ListView* getPartyList() const { return _partyList; }
    ListView* _partyList;
    inline void setTouchable() { _untouchable->setVisible(false); };
    inline void setUntouchable() { _untouchable->setVisible(true); };
    Node* _untouchable;
    
    using Party = std::vector<std::shared_ptr<PartyUnit>>;
    inline const Party getParty() const { return _party; }
    Party _party;
    using Enemys = std::vector<std::shared_ptr<EnemyUnit>>;
    inline const Enemys getEnemys() const { return _enemys; }
    Enemys _enemys;

    const Party getAliveParty();
    const Enemys getAliveEnemys();
    const Party selectTargetParty(const TargetType targetType, const std::shared_ptr<PartyUnit> member);
    const Enemys selectTargetEnemys(const TargetType targetType);
};

#endif /* defined(__cheeze__BattleScene__) */
