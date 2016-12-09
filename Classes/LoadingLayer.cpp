//
//  LoadingLayer.cpp
//  angel
//
//  Created by Atsushi Yoshida on 2015/12/19.
//
//

#include "LoadingLayer.h"
#include "ImageManager.h"
#include "editor-support/cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

bool LoadingLayer::init()
{
    _csb = CSLoader::createNode("Csbs/LoadingLayer.csb");
    addChild(getCsb());
    
    auto seq = 0.3f;
    auto pos = Vec2(0, 0);
    auto height = 10.0f;
    auto times = 1;
    auto jumps = Sequence::create(CallFuncN::create([seq, pos, height, times](Ref* ref){
        auto jump = JumpBy::create(seq, pos, height, times);
        auto dot = static_cast<Node*>(ref)->getChildByName("Dot_1");
        dot->runAction(jump);
    }), DelayTime::create(seq),
                                  CallFuncN::create([seq, pos, height, times](Ref* ref){
        auto jump = JumpBy::create(seq, pos, height, times);
        auto dot = static_cast<Node*>(ref)->getChildByName("Dot_2");
        dot->runAction(jump);
    }), DelayTime::create(seq),
                                  CallFuncN::create([seq, pos, height, times](Ref* ref){
        auto jump = JumpBy::create(seq, pos, height, times);
        auto dot = static_cast<Node*>(ref)->getChildByName("Dot_3");
        dot->runAction(jump);
    }), DelayTime::create(seq * 2),
                                  nullptr);
    getCsb()->runAction(RepeatForever::create(jumps));
    
    auto gameOver = getCsb()->getChildByName("LabelGameOver");
    gameOver->setVisible(false);
    
    useTouchMaker(this);
    return true;
}

void LoadingLayer::gameOver()
{
    auto gameOver = getCsb()->getChildByName("LabelGameOver");
    gameOver->setVisible(true);
}
