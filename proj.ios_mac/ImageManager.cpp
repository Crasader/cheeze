//
//  ImageManager.cpp
//  angel
//
//  Created by Atsushi Yoshida on 2016/06/30.
//
//

#include "ImageManager.h"


ImageView* ImageManager::create(const std::string& name)
{
    ImageView::TextureResType resType;
    if(SpriteFrameCache::getInstance()->getSpriteFrameByName(name)){
        resType = ImageView::TextureResType::PLIST;
    }else{
        resType = ImageView::TextureResType::LOCAL;
    }
    return ImageView::create(name, resType);
}

void ImageManager::loadTexture(ImageView* image, const std::string& name)
{
    image->loadTexture(name, ImageView::TextureResType::PLIST);
}