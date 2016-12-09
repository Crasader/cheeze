//
//  ItemListBoard.cpp
//  alchemy
//
//  Created by 上野 真史 on 2016/08/08.
//
//

#include "ItemListBoard.h"
#include "ItemData.h"
#include "CommonData.h"
#include "ImageManager.h"
#include "BGMPlayer.h"
#include "SupportFunctions.h"
#include "editor-support/cocostudio/CocoStudio.h"

void ItemListBoard::init()
{
    onPressConfirm([&](const int orderId){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
        hide();
    });
    onClose([&](Ref* ref){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
    });

    auto board = getBoard();
    onTouch(board->getChildByName<Button*>("Medal"), [&](Ref* ref){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
        setItemList(ItemType::MEDAL);
    });
    onTouch(board->getChildByName<Button*>("Sweets"), [&](Ref* ref){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
        setItemList(ItemType::SWEETS);
    });
    onTouch(board->getChildByName<Button*>("Battle"), [&](Ref* ref){
        BGMPlayer::play2d("Sounds/se_ok.mp3");
        setItemList(ItemType::BATTLE);
    });
}

void ItemListBoard::setItemList(const ItemType type)
{
    std::vector<ItemId> orderedIds;
    for (auto item : itemDatas) {
        auto itemId = item.first;
        auto itemData = item.second;
        if (type == itemData.type) {
            orderedIds.push_back(itemId);
        }
    }
    std::sort(orderedIds.begin(), orderedIds.end());
    switch (type) {
        case ItemType::BATTLE :
            getBoard()->getChildByName<Text*>("Description")->setString("バトルで使用するアイテムの一覧です");
            break;
        case ItemType::SWEETS :
            getBoard()->getChildByName<Text*>("Description")->setString("おかしはキャラの成長に利用します");
            break;
        case ItemType::MEDAL :
            getBoard()->getChildByName<Text*>("Description")->setString("メダルは武器やアイテムと交換できます");
            break;
        default:
            break;
    }
    auto tmpl = CSLoader::createNode("Csbs/Home/ItemListBox.csb")->getChildByName<Widget*>("Template");
    tmpl->retain();
    setBoxTemplate(tmpl);
    render<ItemData, ItemId>(itemDatas, orderedIds, [&](Node* node, const ItemId orderId, const ItemData& data){
        setListBox(node, data);
    });
    tmpl->release();
}

void ItemListBoard::setListBox(Node* node, const ItemData data)
{
    auto image = node->getChildByName<ImageView*>("Image");
    auto path = "Images/UIParts/" + data.code + ".png";
    ImageManager::loadTexture(image, path);
    auto countLabel = node->getChildByName<TextBMFont*>("Count");
    countLabel->setString("×" + std::to_string(0));
//    countLabel->setColor(itemData.text_color);
    
    auto nameLabel = node->getChildByName<TextBMFont*>("Name");
    nameLabel->setString(data.name);
    auto description = node->getChildByName<Text*>("Description");
    description->setString(data.explain);
}
