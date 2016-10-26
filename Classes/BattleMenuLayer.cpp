//
//  BattleMenuLayer.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/10/12.
//
//

#include "BattleMenuLayer.h"
#include "ImageManager.h"
#include "editor-support/cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

bool BattleMenuLayer::init()
{
    _csb = CSLoader::createNode("Csbs/Battle/MenuLayer.csb");
    addChild(getCsb());
    
    useTouchMaker(this);
    return true;
}
