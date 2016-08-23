#ifndef SupportFunctions_h
#define SupportFunctions_h

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include <spine/SkeletonAnimation.h>
#include <chrono>
#include <sstream>
#include <typeinfo>
#include <regex>

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace spine;

namespace supportfunctions{
    static inline const Vec2 topCenter()
    {
        auto pos = Director::getInstance()->getVisibleOrigin();
        auto visibleSize = Director::getInstance()->getVisibleSize();
        return Vec2(pos.x + visibleSize.width / 2, pos.y + visibleSize.height);
    }
    static inline const Vec2 middleCenter()
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        return Vec2(visibleSize.width / 2, visibleSize.height / 2);
    }
    static inline const Vec2 bottomCenter()
    {
        auto pos = Director::getInstance()->getVisibleOrigin();
        auto visibleSize = Director::getInstance()->getVisibleSize();
        return Vec2(pos.x + visibleSize.width / 2, pos.y);
    }
    static inline const Vec2 topLeft()
    {
        auto pos = Director::getInstance()->getVisibleOrigin();
        auto visibleSize = Director::getInstance()->getVisibleSize();
        return Vec2(pos.x, pos.y + visibleSize.height);
    }
    static inline const Vec2 middleLeft()
    {
        auto pos = Director::getInstance()->getVisibleOrigin();
        auto visibleSize = Director::getInstance()->getVisibleSize();
        return Vec2(pos.x, visibleSize.height / 2);
    }
    static inline const Vec2 bottomLeft()
    {
        auto pos = Director::getInstance()->getVisibleOrigin();
        return Vec2(pos.x, pos.y);
    }
    
    
    static inline SkeletonAnimation* createSpineAnimation(const std::string& fname)
    {
        return SkeletonAnimation::createWithFile("Animations/" + fname + ".json", "Animations/" + fname + ".atlas");
    }

    static inline Button* createButton(const std::string& fname)
    {
         return Button::create("Images/" + fname + "_n.png", "Images/" + fname + "_p.png", "Images/" + fname + "_d.png");
    }

    template <typename SceneT, typename TransitionT>
    static void transition(float duration)
    {
        auto scene = SceneT::createScene();
        auto transition = TransitionT::create(duration, scene);
        Director::getInstance()->replaceScene(transition);
    }
    static inline const std::string getTimeStr(){
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        std::stringstream ss;
        ss << duration.count();
        return ss.str();
    }
    static const std::string escapeNL(std::string& s)
    {
        std::string nl = "\n";
        std::string escaped   = "\\n";
        std::string::size_type pos = s.find_first_of(nl, 0);
        while(std::string::npos != pos){
            s.replace(pos, nl.length(), escaped);
            pos = s.find_first_of(nl, pos);
        }
        return s;
    }
    static Layer* createMessageLayer(const std::string& msg)
    {
        auto layer = LayerColor::create(Color4B::BLACK);
        layer->setOpacity(128);
        auto blink = RepeatForever::create(Sequence::create(FadeOut::create(1.0f), FadeIn::create(1.0f), nullptr));
        auto label = TextBMFont::create(msg, "Fonts/BasicLabel.fnt");
        label->runAction(blink);
        label->setPosition(supportfunctions::middleCenter());
        layer->addChild(label);
        layer->setName("LoadingLayer");
        return layer;
    }
    template<typename T>
    const std::string getClassName()
    {
        const auto numPrefix = std::regex("^.*[0-9]+");
        const auto basename = std::string(typeid(T).name());
        const auto classname = std::regex_replace( basename, numPrefix, "") ;
        std::string name;
        if(basename.substr(0, 1) ==  "N"){
            name = classname.substr(0, classname.size() - 1);
        }else{
            name = classname;
        }
        return name;
    }
}

#endif /* SupportFunctions_h */
