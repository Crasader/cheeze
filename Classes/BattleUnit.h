//
//  BattleUnit.h
//  cheeze
//
//  Created by 上野 真史 on 2016/08/25.
//
//

#ifndef __cheeze__BattleUnit__
#define __cheeze__BattleUnit__

#include "cocos2d.h"
#include "Touchable.h"
#include "editor-support/cocostudio/CocoStudio.h"

class UnitData;
class WeaponData;
class BattleCommand;
enum class WeaponType : int;
enum class ElementType : int;

using namespace cocos2d;
using namespace cocostudio;

class BattleUnit : public Touchable
{
public:
    BattleUnit(const int unitId, const int weaponId, const bool enemy, Node* csb)
    : _unitId(unitId)
    , _weaponId(weaponId)
    , _enemy(enemy)
    , _csb(csb)
    {}
    virtual ~BattleUnit() = default;
    void init();
    void attack();
    void damaged(const int damage, const bool weak, const WeaponType weaponType);
    void healed(const int heal);
    void turnChange();

    inline const bool isEnemy() const { return _enemy; };
    const int getAtk();
    const int getHPMax();
    const WeaponType getWeaponType();
    const ElementType getElementType();

    using BattleCommands = std::vector<std::shared_ptr<BattleCommand>>;
    inline const BattleCommands getBattleCommands() const { return _commands; }
    inline const std::shared_ptr<BattleCommand> getBattleCommand() { return _commands[getCommandNumber()]; };
    inline void addCommand(const std::shared_ptr<BattleCommand> command) { _commands.push_back(command); };
    inline void setCommandNumber(const int number) { _commandNumber = number; }
    inline const int getCommandNumber() const { return _commandNumber; }

    inline bool isDead() { return getHP() <= 0; };
    inline void updateHP(const int point) {
        _hp += point;
        if(_hp > getHPMax()) _hp = getHPMax();
        if(_hp < 0) _hp = 0;
        setHP();
    };
    inline void updateAP(const int point = 1) { _ap += point; if(_ap > getAPMax()) _ap = getAPMax(); setAP(); };
    inline const int getHP() const { return _hp; }
    inline const int getHPMax() const { return _hpMax; }
    inline const int getAP() const { return _ap; }
    inline const int getAPMax() const { return _apMax; }
    inline const int getUnitId() const { return _unitId; }
    inline const int getWeaponId() const { return _weaponId; }
    void setAvatar(Node* node);
    inline ImageView* getAvatar(){ return _avatar; };
    inline void setPosition(const int position) { _position = position; }
    inline const int getPosition() const { return _position; }
    inline Node* getCsb(){ return _csb; };
    const UnitData& getUnitData() const;
    const WeaponData& getWeaponData() const;
private:
    void setName();
    void setElementColor();
    void setHP();
    void setAP();
    const Vec2 getRandomPosition(const Node* node);
    void animationLabel(TextBMFont* label);
    
    ImageView* _avatar { nullptr };
    Node* _csb;

    int _unitId;
    int _weaponId;
    bool _enemy;
    int _position { 0 };

    inline float getHpPercent(){
        float percent = 100.0f * getHP() / getHPMax();
        if (getHP() > 0 && percent < 2.0f) {
            percent = 2.0f;
        }
        return percent;
    }
    int _hp { 0 };
    int _hpMax { 0 };

    int _ap { 0 };
    int _apMax { 0 };

    int _commandNumber { 0 };
    BattleCommands _commands;
};

#endif /* defined(__cheeze__BattleUnit__) */