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

class MemberListBox;
class Enemy;

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

    using Enemys = std::vector<std::shared_ptr<Enemy>>;
    inline const Enemys getEnemys() const { return _enemys; }
    Enemys _enemys;
    using Party = std::vector<std::shared_ptr<MemberListBox>>;
    inline const Party getParty() const { return _party; }
    Party _party;
    inline ListView* getPartyList() const { return _partyList; }
    ListView* _partyList;
};

#endif /* defined(__cheeze__BattleScene__) */
