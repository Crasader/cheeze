//
//  ItemListBoard.h
//  alchemy
//
//  Created by 上野 真史 on 2016/08/08.
//
//

#ifndef __alchemy__ItemListBoard__
#define __alchemy__ItemListBoard__

#include "ListBoard.h"

class ItemData;
enum class ItemType : int;

class ItemListBoard : public ListBoard
{
public:
    ItemListBoard(Node* node, Node* csb)
    : ListBoard(node, csb)
    {
        init();
    }
    virtual ~ItemListBoard() = default;
    void setItemList(const ItemType type);
private:
    void init();
    void setListBox(Node* node, ItemData data);
};

#endif /* __alchemy__ItemListBoard__ */
