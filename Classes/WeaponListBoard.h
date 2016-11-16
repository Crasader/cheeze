//
//  WeaponListBoard.h
//  cheeze
//
//  Created by 上野 真史 on 2016/11/10.
//
//

#ifndef __alchemy__WeaponListBoard__
#define __alchemy__WeaponListBoard__

#include "ListBoard.h"

class WeaponData;
enum class WeaponType : int;

class WeaponListBoard : public ListBoard
{
public:
    WeaponListBoard(Node* node, Node* csb)
    : ListBoard(node, csb)
    {
        init();
    }
    virtual ~WeaponListBoard() = default;
    void setWeaponList(const int characterId);
private:
    void init();
    void setListBox(Node* node, WeaponData data);
    int _characterId {0};
};

#endif /* __alchemy__WeaponListBoard__ */
