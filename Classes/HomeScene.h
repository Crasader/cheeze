//
//  HomeScene.h
//  cheeze
//
//  Created by 上野 真史 on 2016/06/09.
//
//

#ifndef __cheeze__HomeScene__
#define __cheeze__HomeScene__

#include "cocos2d.h"
#include "BaseScene.h"

class MemberStatusBox;

class HomeScene : public BaseScene<HomeScene>
{
public:
    HomeScene();
    virtual ~HomeScene();
    bool init();
    void onEnter();
//    void onEnterTransitionDidFinish();
private:
    void setPartyMembers();
    
    using Party = std::vector<std::shared_ptr<MemberStatusBox>>;
    inline const Party getParty() const { return _party; }
    Party _party;
    inline PageView* getPartyList() const { return _partyList; }
    PageView* _partyList;
};

#endif /* defined(__cheeze__HomeScene__) */
