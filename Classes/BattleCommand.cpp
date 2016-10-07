//
//  BattleCommand.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/08/25.
//
//

#include "BattleCommand.h"
#include "UnitData.h"
#include "ImageManager.h"

void BattleCommand::init()
{
}

const std::string BattleCommand::getName() const
{
    return getCommandData().name;
}

const std::string BattleCommand::getExplain() const
{
    return getCommandData().explain;
}

const int BattleCommand::getAp() const
{
    return getCommandData().ap;
}

const std::vector<EffectData> BattleCommand::getEffects() const
{
    return getCommandData().effect_datas;
}
