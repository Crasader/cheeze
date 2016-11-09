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

    std::vector<ItemId> orderedIds;
    for (auto item : itemDatas) {
        auto itemId = item.first;
        orderedIds.push_back(itemId);
    }
    std::sort(orderedIds.begin(), orderedIds.end());
    auto board = getBoard();
    auto tmpl = CSLoader::createNode("Csbs/Home/ItemListBox.csb")->getChildByName<Widget*>("Template");
    tmpl->retain();
    setBoxTemplate(tmpl);
    render<ItemData, ItemId>(itemDatas, orderedIds, [&](Node* node, const ItemId orderId, const ItemData& data){
        setListBox(node, data);
    });
    tmpl->release();
}

void ItemListBoard::show()
{
    ListBoard::show();
}

void ItemListBoard::setListBox(Node* node, const ItemData data)
{
    auto image = node->getChildByName<ImageView*>("Image");
    auto path = "Images/UIParts/" + data.code + ".png";
    ImageManager::loadTexture(image, path);
    auto countLabel = node->getChildByName<TextBMFont*>("Count");
//    countLabel->setString("×" + std::to_string(productData.amount));
//    countLabel->setColor(itemData.text_color);
    
//    auto& priceData = productData.price;
//    auto priceItemId = priceData.itemId;
//    auto& priceItemData = itemDatas.at(priceItemId);
//    auto priceIcon = node->getChildByName<ImageView*>("IconPrice");
//    auto pricePath = "Images/Item/" + priceItemData.code + ".png";
//    ImageManager::loadTexture(priceIcon, pricePath);
//    auto priceLabel = node->getChildByName<TextBMFont*>("LabelPrice");
//    auto priceHave = player->getItemCount(priceItemId);
//    priceLabel->setColor(priceItemData.text_color);
    
    auto nameLabel = node->getChildByName<TextBMFont*>("Name");
    nameLabel->setString(data.name);
//    if (_shopId == ShopId::CHARGE) {
//        nameLabel->setString(productData.name);
//        priceIcon->setColor(Color3B(255, 255, 255));
//        priceLabel->setString(std::to_string(priceData.amount));
//    } else {
//        if (isSellShop()) {
//            if (priceHave <= 0) {
//                priceLabel->setColor(Color3B(255, 136, 136));
//            }
//            if (player->getItemTotalCount(priceItemId)) {
//                nameLabel->setString(productData.name);
//                priceIcon->setColor(Color3B(255, 255, 255));
//                priceLabel->setString("×" + std::to_string(priceHave));
//            } else {
//                nameLabel->setString("????????");
//                priceIcon->setColor(Color3B(34, 34, 34));
//                priceLabel->setString("×" + std::to_string(priceHave));
//            }
//        } else {
//            nameLabel->setString(productData.name);
//            priceIcon->setColor(Color3B(255, 255, 255));
//            priceLabel->setString("×" + std::to_string(priceData.amount));
//        }
//    }
//    onTouch(node->getChildByName<ImageView*>("BgImage"), [&, productId](Ref* ref){
//        BGMPlayer::play2d("Sounds/se_ok.mp3");
//        if (isSellShop()) {
//            getSellBoard()->setSellProductData(productId);
//            getBuyBoard()->hide();
//        } else {
//            getSellBoard()->hide();
//            getBuyBoard()->setBuyProductData(productId);
//        }
//    });
}
