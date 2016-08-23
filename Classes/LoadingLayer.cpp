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
    
//    auto seq = 0.3f;
//    auto pos = Vec2(0, 0);
//    auto height = 10.0f;
//    auto times = 1;
//    auto jumps = Sequence::create(CallFuncN::create([seq, pos, height, times](Ref* ref){
//        auto jump = JumpBy::create(seq, pos, height, times);
//        auto dot = static_cast<Node*>(ref)->getChildByName("dot1");
//        dot->runAction(jump);
//    }), DelayTime::create(seq),
//                                  CallFuncN::create([seq, pos, height, times](Ref* ref){
//        auto jump = JumpBy::create(seq, pos, height, times);
//        auto dot = static_cast<Node*>(ref)->getChildByName("dot2");
//        dot->runAction(jump);
//    }), DelayTime::create(seq),
//                                  CallFuncN::create([seq, pos, height, times](Ref* ref){
//        auto jump = JumpBy::create(seq, pos, height, times);
//        auto dot = static_cast<Node*>(ref)->getChildByName("dot3");
//        dot->runAction(jump);
//    }), DelayTime::create(seq * 2),
//                                  nullptr);
//    getCsb()->runAction(RepeatForever::create(jumps));
//    auto image = getCsb()->getChildByName<ImageView*>("Image");
//    ImageManager::loadTexture(image, filePath.str());
//    auto scale1 = ScaleTo::create(0.15f, 1.0f, 1.2f);
//    auto scale2 = ScaleTo::create(0.15f, 1.1f, 1.2f);
//    auto scale3 = ScaleTo::create(0.15f, 1.1f, 1.0f);
//    auto scale4 = ScaleTo::create(0.15f, 1.0f, 1.0f);
//    auto scaleSeq = Sequence::create(scale1, scale2, scale3, scale4, nullptr);
//    auto imageSeq = Sequence::create(scaleSeq, scaleSeq, DelayTime::create(0.6f), nullptr);
//    auto action = RepeatForever::create(imageSeq);
//    image->runAction(RepeatForever::create(action));
    
    useTouchMaker(this);
    return true;
}
