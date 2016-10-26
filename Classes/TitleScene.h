//
//  TitleScene.hpp
//  cheeze
//
//  Created by 上野 真史 on 2016/08/21.
//
//

#ifndef __cheeze__TitleScene__
#define __cheeze__TitleScene__

#include "cocos2d.h"
#include "BaseScene.h"

class TitleScene : public BaseScene<TitleScene>
{
public:
    TitleScene();
    virtual ~TitleScene();
    bool init();
    void onEnter();
    void onEnterTransitionDidFinish();
private:
};

#endif /* defined(__cheeze__TitleScene__) */
