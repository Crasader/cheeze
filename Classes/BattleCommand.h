//
//  BattleCommand.h
//  cheeze
//
//  Created by 上野 真史 on 2016/08/25.
//
//

#ifndef __cheeze__BattleCommand__
#define __cheeze__BattleCommand__

#include "cocos2d.h"
#include "NonCopyable.h"
#include "UnitData.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class BattleCommand : private NonCopyable<BattleCommand>
{
public:
    BattleCommand(const CommandData command)
    : _command(command)
    {
        init();
    }
    virtual ~BattleCommand() = default;
    const std::string getName() const;
    const std::string getExplain() const;
    const int getAp() const;
    const std::vector<EffectData> getEffects() const;
private:
    void init();
    inline const CommandData& getCommandData() const { return _command; };
    CommandData _command;
};

#endif /* defined(__cheeze__BattleCommand__) */
