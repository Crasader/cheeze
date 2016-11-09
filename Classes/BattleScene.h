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
    void onEnterTransitionDidFinish();
private:
    void setPartyMembers();
    void setEnemys();
    void playerAttack(const int count = 1);
    void enemyAttack();
    void nextTurn();
    const bool isWeakElement(const ElementType atkType, const ElementType defType);

    inline ListView* getPartyList() const { return _partyList; }
    ListView* _partyList;
    inline void setTouchable() { _untouchable->setVisible(false); };
    inline void setUntouchable() { _untouchable->setVisible(true); };
    Node* _untouchable;
    
    inline void showSkillBoard(const std::string name)
    {
        _skillBoard->setVisible(true);
        auto label = _skillBoard->getChildByName<TextBMFont*>("Label");
        label->setString(name);
    }
    inline void hideSkillBoard() { _skillBoard->setVisible(false); };
    Node* _skillBoard;
    inline void showMenuLayer() { _menuLayer->setVisible(true); };
    inline void hideMenuLayer() { _menuLayer->setVisible(false); };
    Node* _menuLayer;

    using Party = std::vector<std::shared_ptr<PartyUnit>>;
    inline const Party getParty() const { return _party; }
    Party _party;
    using Enemys = std::vector<std::shared_ptr<EnemyUnit>>;
    inline const Enemys getEnemys() const { return _enemys; }
    Enemys _enemys;
    int _targetPosition{0};

    const Party getAliveParty();
    const Enemys getAliveEnemys();
    const Party selectTargetParty(const TargetType targetType, const std::shared_ptr<PartyUnit> member);
    const Enemys selectTargetEnemys(const TargetType targetType);
    int _round{0};
};

#endif /* defined(__cheeze__BattleScene__) */
