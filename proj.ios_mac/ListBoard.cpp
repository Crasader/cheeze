#include "ListBoard.h"
#include "cocos/ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "SupportFunctions.h"

using namespace cocostudio;
using namespace cocos2d::ui;
using namespace cocos2d::experimental;

void ListBoard::init()
{
    _listView = _board->getChildByName<ListView*>("ListView");
    _listView->setBounceEnabled(true);
    _listView->setScrollBarEnabled(false);
    _board->setPosition(supportfunctions::middleCenter());
    _world->addChild(_board);
    hide();
}

void ListBoard::resetList()
{
    _listView->removeAllItems();
}

void ListBoard::refreshList()
{
    _listView->forceDoLayout();
}

void ListBoard::setTitle(const std::string& title)
{
    std::stringstream titleSS;
    titleSS << title;
    _board->getChildByName<TextBMFont*>("Title")->setString(titleSS.str());
}

void ListBoard::setList(Node* node)
{
    _listView->addChild(node);
}

void ListBoard::onClose(const Touchable::Callback& callback)
{
    onButtonPress("Close", callback);
}

void ListBoard::onButtonPress(const std::string& name, const Touchable::Callback& callback)
{
    auto button = _board->getChildByName<Button*>(name);
    onTouch(button, [&, callback](Ref* ref){
        callback(ref);
        hide();
    });
}
