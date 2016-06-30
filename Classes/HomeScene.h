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

class HomeScene : public BaseScene<HomeScene>
{
public:
    HomeScene();
    virtual ~HomeScene();
    bool init();
//    void onEnterTransitionDidFinish();
private:
};

#endif /* defined(__cheeze__HomeScene__) */
