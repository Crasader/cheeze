//
//  LoadingLayer.h
//  angel
//
//  Created by Atsushi Yoshida on 2015/12/19.
//
//

#ifndef LoadingLayer_h
#define LoadingLayer_h

#include "cocos2d.h"
#include "Touchable.h"

USING_NS_CC;

class LoadingLayer : public Layer, private Touchable
{
public:
    bool init();
    CREATE_FUNC(LoadingLayer);
    void gameOver();
private:
    inline Node* getCsb(){ return _csb; };
    Node* _csb;
};

#endif /* LoadingLayer_h */
