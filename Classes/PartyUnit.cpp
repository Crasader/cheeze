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
    
    _untouchable = getCsb()->getChildByName<ImageView*>("Untouchable");
    setTouchable();

    auto attackCommand = std::make_shared<BattleCommand>(commandDatas.at(0));
    addCommand(attackCommand);
    auto& weaponData = getWeaponData();
    for (auto& commandId : weaponData.command_ids) {
        auto command = commandDatas.at(commandId);
        auto battleCommand = std::make_shared<BattleCommand>(command);
        addCommand(battleCommand);
    }
    auto burstCommand = std::make_shared<BattleCommand>(getUnitData().command_data);
    addCommand(burstCommand);
    setHP();
    setTP();
    setThumbnail();
}

void PartyUnit::appendTo(ListView* list, const int position, Node* avatar)
{
    setAvatar(avatar);
    getAvatar()->setScale(0.5f);
    getAvatar()->setFlippedX(false);
    setPosition(position);
    list->addChild(getCsb());
    init();
}

void PartyUnit::setThumbnail()
{
    auto thumbnail = getCsb()->getChildByName<ImageView*>("Thumbnail");
    ImageManager::loadTexture(thumbnail, "Images/Character/Normal/" + getUnitData().code + ".png");
}

void PartyUnit::setHP()
{
    BattleUnit::setHP();
    auto hpLabel = getCsb()->getChildByName<TextBMFont*>("LabelHP");
    std::stringstream hpSS;
    hpSS << " HP:";
    hpSS << getHP();
    hpSS << "/";
    hpSS << getHPMax();
    hpLabel->setString(hpSS.str());
}

void PartyUnit::setTP()
{
    auto currentTp = getTP();
    auto node = getCsb()->getChildByName("TP");
    auto tpBar = node->getChildByName<LoadingBar*>("Bar");
    tpBar->setPercent(getTpPercent());
    auto tpLabel = getCsb()->getChildByName<TextBMFont*>("LabelTP");
    tpLabel->setString("TP: " + std::to_string(currentTp) + "%");
}

void PartyUnit::setCommands()
{
    for (auto num = 0; num < 5; num++) {
        setCommand(num);
    }
    selectCommands();
}

void PartyUnit::setCommand(const int number)
{
    auto commandButton = getCsb()->getChildByName<Button*>("Command_" + std::to_string(number));
    auto nameLabel = getCsb()->getChildByName<TextBMFont*>("NameCommand_" + std::to_string(number));
    auto needAPLabel = getCsb()->getChildByName<TextBMFont*>("APCommand_" + std::to_string(number));

    auto needAP = 0;
    auto battleCommand = getBattleCommands()[number];
    nameLabel->setString(battleCommand->getName());
    needAP = battleCommand->getAp();
    if (number == 4) {
        needAPLabel->setString("TP:" + std::to_string(needAP) + "%");
        needAPLabel->setColor(Color3B(136, 255, 136));
        if (getTP() >= 100 && !isDead()) {
            commandButton->setBright(true);
            commandButton->setEnabled(true);
        } else {
            commandButton->setBright(false);
            commandButton->setEnabled(false);
        }
    } else {
        needAPLabel->setString("AP:" + std::to_string(needAP));
        needAPLabel->setColor(Color3B(255, 136, 136));
        if (getAP() >= needAP && !isDead()) {
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
        auto commandButton = getCsb()->getChildByName<Button*>("Command_" + std::to_string(num));
        if (getCommandNumber() == num) {
            commandButton->setColor(Color3B(255, 238, 136));
        } else {
            if (commandButton->isBright()) {
                commandButton->setColor(Color3B::WHITE);
            } else {
                commandButton->setColor(Color3B(136, 136, 136));
            }
        }
    }
}

void PartyUnit::attack()
{
    auto start = CallFunc::create([&]{
        auto filePath = "Images/Character/Attack/" + getUnitData().code + ".png";
        ImageManager::loadTexture(getAvatar(), filePath);
    });
    auto jump = JumpBy::create(0.15f, Vec2(-60, 0), 30, 1);
    auto wait = DelayTime::create(0.4f);
    auto finish = CallFunc::create([&]{
        auto filePath = "Images/Character/Normal/" + getUnitData().code + ".png";
        ImageManager::loadTexture(getAvatar(), filePath);
    });
    auto action = Sequence::create(start, jump, wait, jump->reverse(), finish, nullptr);
    getAvatar()->runAction(action);
}

void PartyUnit::damaged(const int damage, const bool weak, const WeaponType weaponType)
{
    auto particleAnimation = CallFuncN::create([&, weaponType](Node* node){
        auto fileName = "Particles/attack_" + weaponCodes.at(weaponType).code + ".plist";
        if (FileUtils::getInstance()->isFileExist(fileName)) {
            auto particle = ParticleSystemQuad::create(fileName);
            particle->setPosition(getRandomPosition(node));
            particle->setRotationSkewY(-180.0f);
            particle->setScale(1.0f);
            node->getParent()->addChild(particle);
            particle->setAutoRemoveOnFinish(true);
        };
    });
    auto labelAnimation = CallFuncN::create([&, damage, weak](Node* node){
        auto damageLabel = TextBMFont::create(std::to_string(damage), "Fonts/DamageLabel.fnt");
        damageLabel->setPosition(getRandomPosition(node));
        damageLabel->setScale(0.5f);
        node->getParent()->addChild(damageLabel);
        animationLabel(damageLabel);
        if (weak) {
            auto weakLabel = TextBMFont::create("Weak Point!!", "Fonts/BasicLabel.fnt");
            weakLabel->setScale(1.0f);
            auto size = node->getContentSize();
            auto pos = Vec2(size.width / 4, size.height / 4);
            weakLabel->setPosition(pos);
            weakLabel->setColor(elementCodes.at(getUnitData().element).color);
            node->addChild(weakLabel);
            auto move   = MoveBy::create(0.5f, Point(0, 80));
            auto wait   = DelayTime::create(0.4f);
            auto finish = CallFuncN::create([&](Node* node){
                node->removeFromParent();
            });
            auto action = Sequence::create(move, wait, finish, nullptr);
            weakLabel->runAction(action);
        }
    });
    auto damageColor = CallFuncN::create([&](Node* node){
        node->setColor(Color3B(255, 68, 68));
    });
    auto hpBarDown = CallFunc::create([&, damage](){
        updateHP(-damage);
    });
    auto se = CallFunc::create([&]{
        BGMPlayer::play2d("Sounds/se_damage_human.mp3");
    });
    auto keepColor = DelayTime::create(0.1f);
    auto finish = CallFuncN::create([&](Node* node){
        node->setColor(Color3B(255, 255, 255));
    });
    auto action = Sequence::create(particleAnimation, labelAnimation, se, hpBarDown, damageColor, keepColor, finish, nullptr);
    getAvatar()->runAction(action);
}

void PartyUnit::healed(const int heal)
{
    auto particleAnimation = CallFuncN::create([&](Node* node){
        auto fileName = "Particles/heal_0.plist";
        if (FileUtils::getInstance()->isFileExist(fileName)) {
            auto particle = ParticleSystemQuad::create(fileName);
            particle->setPosition(getRandomPosition(node));
            particle->setRotationSkewY(-180.0f);
            particle->setScale(1.0f);
            node->getParent()->addChild(particle);
            particle->setAutoRemoveOnFinish(true);
        };
    });
    auto labelAnimation = CallFuncN::create([&, heal](Node* node){
        auto healLabel = TextBMFont::create(std::to_string(heal), "Fonts/HealLabel.fnt");
        healLabel->setPosition(getRandomPosition(node));
        healLabel->setScale(0.5f);
        node->getParent()->addChild(healLabel);
        animationLabel(healLabel);
    });
    auto healColor = CallFuncN::create([&](Node* node){
        node->setColor(Color3B(68, 255, 68));
    });
    auto hpBarUp = CallFunc::create([&, heal](){
        updateHP(heal);
    });
    auto se = CallFunc::create([&]{
        BGMPlayer::play2d("Sounds/se_heal.mp3");
    });
    auto keepColor = DelayTime::create(0.1f);
    auto finish = CallFuncN::create([&](Node* node){
        node->setColor(Color3B(255, 255, 255));
    });
    auto action = Sequence::create(particleAnimation, labelAnimation, se, hpBarUp, healColor, keepColor, finish, nullptr);
    getAvatar()->runAction(action);
}

void PartyUnit::turnChange()
{
    if (isDead()) {
        getAvatar()->setVisible(false);
        setUntouchable();
        setCommands();
        return;
    }
    updateAP();
    setCommands();
}
