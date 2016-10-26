//
//  BattleMenuLayer.h
//  cheeze
//
//  Created by 上野 真史 on 2016/10/12.
//
//

#ifndef BattleMenuLayer_h
#define BattleMenuLayer_h

#include "cocos2d.h"
#include "Touchable.h"

USING_NS_CC;

class BattleMenuLayer : public Layer, private Touchable
{
public:
    bool init();
    CREATE_FUNC(BattleMenuLayer);
private:
    inline Node* getCsb(){ return _csb; };
    Node* _csb;
};

#endif /* BattleMenuLayer_h */
