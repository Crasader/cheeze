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

class ItemListBoard : public ListBoard
{
public:
    ItemListBoard(Node* node, Node* csb)
    : ListBoard(node, csb)
    {
        init();
    }
    virtual ~ItemListBoard() = default;
    void show();
private:
    void init();
    void setItemList();
    void setListBox(Node* node, ItemData data);
};

#endif /* __alchemy__ItemListBoard__ */
