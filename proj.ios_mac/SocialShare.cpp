//
//  SocialShare.cpp
//  angel
//
//  Created by Atsushi Yoshida on 2016/07/05.
//
//

#include "SocialShare.h"

//void SocialShare::setTweetButton(Widget* widget, const std::string& message, CCSocialShare::SocialManagerCompletionCallback callback)
//{
//    widget->setTouchEnabled(true);
//    widget->addTouchEventListener([message, callback](Ref*,Widget::TouchEventType e){
//        if(e == Widget::TouchEventType::ENDED){
//            Size size = Director::getInstance()->getWinSize();
//            RenderTexture* texture = RenderTexture::create((int)size.width, (int)size.height);
//            texture->setPosition(Point(size.width / 2, size.height / 2));
//            texture->begin();
//            Director::getInstance()->getRunningScene()->visit();
//            texture->end();
//            texture->saveToFile("screenshot.png",
//                                Image::Format::PNG,
//                                true,
//                                [message, callback](RenderTexture* rt, const std::string& path) {
//                                    CCSocialShare::SocialManager::postMessage(CCSocialShare::Service::TWITTER,
//                                                                              message.c_str(),
//                                                                              path.c_str(), callback);
//                                });
//        }
//    });
//}