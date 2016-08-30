//
//  EnemyUnit.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/08/24.
//
//

#include "EnemyUnit.h"
#include "UnitData.h"
#include "BattleCommand.h"

#include "ImageManager.h"
#include "BGMPlayer.h"

#include "editor-support/cocostudio/CocoStudio.h"
using namespace cocostudio;

void EnemyUnit::appendTo(Node* node, const int position)
{
    if (getUnitId() < 1) {
        getCsb()->setVisible(false);
        return;
    }
    setAvatar(node);
    setPosition(position);
    node->addChild(getCsb());
    init();
}

void EnemyUnit::init()
{
    BattleUnit::init();
    for (auto& command : getUnitData().commands) {
        auto battleCommand = std::make_shared<BattleCommand>(command);
        addCommand(battleCommand);
    }
    updateAP(0);
}

void EnemyUnit::turnChange()
{
    if (isDead()) {
        getAvatar()->setVisible(false);
        return;
    }
    if (getCommandNumber() == 0) {
        updateAP();
    }
    if (isSkill()) {
        setCommandNumber(1);
    } else {
        setCommandNumber(0);
    }
}
