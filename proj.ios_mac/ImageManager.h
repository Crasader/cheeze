//
//  ImageManager.h
//  okeya
//
//  Created by Atsushi Yoshida on 2016/06/30.
//
//

#ifndef __okeya__ImageManager__
#define __okeya__ImageManager__

#include "cocos2d.h"
#include "CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class ImageManager
{
public:
    static ImageView* create(const std::string& name);
    static void loadTexture(ImageView* image, const std::string& name);
private:
};

#endif /* defined(__okeya__ImageManager__) */
