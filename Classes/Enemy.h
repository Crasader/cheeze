//
//  Enemy.h
//  cheeze
//
//  Created by 上野 真史 on 2016/08/24.
//
//

#ifndef __cheeze__Enemy__
#define __cheeze__Enemy__

#include "cocos2d.h"
#include "Touchable.h"

class EnemyData;

using namespace cocos2d;

class Enemy : private Touchable
{
public:
    virtual void appendTo(Node* node, const int position, const int enemyId);
    virtual ~Enemy() = default;
    void damaged(const int damage);
private:
    void init();
    void setHP();
    void setAP();
    inline void addAP() { _ap++; };
    inline Node* getCsb(){ return _csb; };
    Node* _csb { nullptr };
    const EnemyData& getEnemyData() const;
    inline const int getPosition() const { return _position; }
    int _position { -1 };
    inline const int getEnemyId() const { return _enemyId; }
    int _enemyId { 0 };
    inline const int getAP() const { return _ap; }
    inline const int getAPMax() const { return _apMax; }
    int _ap { 0 };
    int _apMax { 0 };
    inline const int getHP() const { return _hp; }
    inline const int getHPMax() const { return _hpMax; }
    int _hp { 0 };
    int _hpMax { 0 };
    inline float getHpPercent(){
        float percent = 100.0f * getHP() / getHPMax();
        if (_hp > 0 && percent < 2.0f) {
            percent = 2.0f;
        }
        return percent;
    }
};

#endif /* defined(__cheeze__Enemy__) */
