//
//  Enemy.cpp
//  cheeze
//
//  Created by 上野 真史 on 2016/08/24.
//
//

#include "Enemy.h"
#include "UnitData.h"

#include "ImageManager.h"
#include "BGMPlayer.h"

#include "editor-support/cocostudio/CocoStudio.h"
using namespace cocostudio;

void Enemy::appendTo(Node* node, const int position, const int enemyId)
{
    _enemyId = enemyId;
    _position = position;
    _csb = CSLoader::createNode("Csbs/Battle/Enemy.csb");
    auto image = getCsb()->getChildByName<ImageView*>("Image");
    image->removeFromParent();
    auto filePath = "Images/Monster/" + getEnemyData().code + ".png";
    auto avatar = ImageManager::create(filePath);
    avatar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    avatar->setLocalZOrder(0);
    getCsb()->addChild(avatar);
    
    if (getPosition() != 1) {
        getCsb()->setVisible(false);
        return;
    }
    
    addAP();
    
    setHP();
    setAP();

    node->removeAllChildren();
    node->addChild(getCsb());
}

void Enemy::setHP()
{
    auto& data = getEnemyData();
    _hp = _hpMax = data.hp;
    auto hpNode = getCsb()->getChildByName("HP");
    hpNode->setLocalZOrder(5);
    auto name = hpNode->getChildByName<Text*>("Name");
    name->setString(data.name);
    auto hpBar = hpNode->getChildByName<LoadingBar*>("Bar");
    hpBar->setPercent(getHpPercent());
}

void Enemy::setAP()
{
    auto& data = getEnemyData();
    _apMax = data.ap;
    auto apLabel = getCsb()->getChildByName<Text*>("APLabel");
    apLabel->setString("[AP:" + std::to_string(getAP()) + " / " + std::to_string(getAPMax()) + "]");
    for (auto i = 0; i < 4; i++) {
        auto ap = getCsb()->getChildByName<Button*>("AP_" + std::to_string(i + 1));
        ap->setBright(i < getAP());
    }
}

void Enemy::init()
{
    
}

const EnemyData& Enemy::getEnemyData() const
{
    return enemyUnitDatas.at(getEnemyId());
}

void Enemy::damaged(const int damage)
{
    auto particleAnimation = CallFunc::create([&](){
        std::stringstream fileName;
        fileName << "Particles/attack_";
        fileName << weaponCodes.at(WeaponType::AX).code;
        fileName << ".plist";
        if (FileUtils::getInstance()->isFileExist(fileName.str())) {
            auto particle = ParticleSystemQuad::create(fileName.str());
            particle->setPosition(Vec2(random(-40, 40), random(80, 160)));
            particle->setScale(1.0f);
            getCsb()->addChild(particle);
            auto callback = CallFuncN::create([&](Node* pParticle){
                static_cast<ParticleSystemQuad*>(pParticle)->setAutoRemoveOnFinish(true);
            });
            particle->runAction(callback);
        };
    });
    auto labelAnimation = CallFunc::create([&, damage]{
        // ダメージラベル
        auto pos = Vec2(random(-40, 40), random(80, 160));
        std::stringstream damageSS;
        damageSS << damage;
        auto damageLabel = TextBMFont::create(std::to_string(damage), "Fonts/DamageLabel.fnt");
        damageLabel->setScale(0.5f);
        damageLabel->setPosition(pos);
        getCsb()->addChild(damageLabel);
        auto jump   = JumpBy::create(0.3f, Point(0, 0), 30, 2);
        auto wait   = DelayTime::create(0.4f);
        auto finish = CallFuncN::create([&](Node* pLabel){
            pLabel->removeFromParent();
        });
        auto action = Sequence::create(jump, wait, finish, nullptr);
        damageLabel->runAction(action);
    });
    auto damageColor = CallFuncN::create([&](Node* pCharacter){
        // キャラの色替え
        pCharacter->setColor(Color3B(255, 68, 68));
    });
    auto hpBarDown = CallFunc::create([&](){
        setHP();
    });
    auto se = CallFunc::create([&]{
        BGMPlayer::play2d("Sounds/se_damage_human.mp3");
    });
    auto keepColor = DelayTime::create(0.1f);
    auto finish = CallFuncN::create([&](Node* pCharacter){
        pCharacter->setColor(Color3B(255, 255, 255));
    });
    auto action = Sequence::create(particleAnimation, labelAnimation, se, hpBarDown, damageColor, keepColor, finish, nullptr);
    getCsb()->runAction(action);
}
