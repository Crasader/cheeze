//
//  PartyUnit.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/08/23.
//
//

#include "PartyUnit.h"
#include "BattleUnit.h"
#include "UnitData.h"
#include "BattleCommand.h"

#include "ImageManager.h"
#include "BGMPlayer.h"


using BattleCommands = std::vector<std::shared_ptr<BattleCommand>>;

void PartyUnit::init()
{
    BattleUnit::init();
    
    auto& weapon = getWeaponData();
    for (auto& command : getUnitData().commands) {
        auto battleCommand = std::make_shared<BattleCommand>(command);
        addCommand(battleCommand);
    }
    auto burstCommand = std::make_shared<BattleCommand>(weaponBurstDatas.at(weapon.burstId));
    addCommand(burstCommand);
    
    setTP();
    setThumbnail();
    turnChange();
}

void PartyUnit::appendTo(ListView* list, const int position, Node* avatar)
{
    init();
    setAvatar(avatar);
    getAvatar()->setFlippedX(true);
    setPosition(position);

    list->addChild(getCsb());
}

void PartyUnit::setThumbnail()
{
    auto thumbnail = getCsb()->getChildByName<ImageView*>("Thumbnail");
    ImageManager::loadTexture(thumbnail, "Images/Character/" + getUnitData().code + ".png");
    auto bgThumbnail = getCsb()->getChildByName<ImageView*>("BgThumbnail");
    bgThumbnail->setColor(elementCodes.at(getUnitData().element).color);
}

void PartyUnit::setTP()
{
    auto currentTp = getTP();
    auto node = getCsb()->getChildByName("TP");
    auto tpLabel = node->getChildByName<TextBMFont*>("Label");
    tpLabel->setString("TP: " + std::to_string(currentTp) + "%");
    auto tpBar = node->getChildByName<LoadingBar*>("Bar");
    tpBar->setPercent(getTpPercent());
}

void PartyUnit::setCommands()
{
    selectCommands();
    for (auto num = 0; num < 5; num++) {
        setCommand(num);
    }
}

void PartyUnit::setCommand(const int number)
{
    auto commandButton = getCsb()->getChildByName<Button*>("Command_" + std::to_string(number));
    auto nameLabel = commandButton->getChildByName<TextBMFont*>("Name");
    auto needAPLabel = commandButton->getChildByName<TextBMFont*>("Label");

    auto needAP = 0;
    auto battleCommand = getBattleCommands()[number];
    nameLabel->setString(battleCommand->getName());
    needAP = battleCommand->getAp();
    if (number == 4) {
        needAPLabel->setString("TP:" + std::to_string(needAP) + "%");
        needAPLabel->setColor(Color3B(136, 255, 136));
        if (getTP() >= 100) {
            commandButton->setBright(true);
            commandButton->setEnabled(true);
        } else {
            commandButton->setBright(false);
            commandButton->setEnabled(false);
        }
    } else {
        needAPLabel->setString("AP:" + std::to_string(needAP));
        needAPLabel->setColor(Color3B(255, 136, 136));
        if (getAP() >= needAP) {
            commandButton->setBright(true);
            commandButton->setEnabled(true);
        } else {
            commandButton->setBright(false);
            commandButton->setEnabled(false);
        }
    }
    onTouch(commandButton, [&, number](Ref* ref){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
        selectCommands(number);
    });
}

void PartyUnit::selectCommands(const int number)
{
    setCommandNumber(number);
    for (auto num = 0; num < 5; num++) {
        auto command = getCsb()->getChildByName<Button*>("Command_" + std::to_string(num));
        if (getCommandNumber() == num) {
            command->setColor(Color3B(255, 238, 136));
        } else {
            command->setColor(Color3B::WHITE);
        }
    }
}

void PartyUnit::turnChange()
{
    if (isDead()) {
        getAvatar()->setVisible(false);
        setCommands();
        return;
    }
    updateAP();
    setCommands();
}
