#ifndef __okeya__BaseScene__
#define __okeya__BaseScene__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "Touchable.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include <sstream>
#include <typeinfo>
#include <regex>
#include "SupportFunctions.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio;

template <typename T>
class BaseScene : public Layer, protected Touchable
{
public:
    virtual ~BaseScene() = default;
    static cocos2d::Scene* createScene()
    {
        auto scene = Scene::create();
        auto layer = T::create();
        scene->addChild(layer);
        return scene;
    }
    inline Node* getChildByName(const std::string& name)
    {
        return _csb->getChildByName(name);
    }
    inline Node* getChildByName(const std::string& name) const { return _csb->getChildByName(name); }
    template<typename NodePTR>
    NodePTR getChildByName(const std::string& name)
    {
        return _csb->getChildByName<NodePTR>(name);
    }
protected:
    inline Node* getCsb() const { return _csb; }
    
    static T* create()
    {
        T *pRet = new(std::nothrow) T();
        if (pRet && pRet->setCsb() && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
    
    bool setCsb(){
        const auto name = supportfunctions::getClassName<T>();
        std::stringstream ss;
        ss << "Csbs/";
        ss << name;
        ss << ".csb";
        const auto fname = ss.str();
        if(FileUtils::getInstance()->isFileExist(fname)){
            _csb = CSLoader::createNode(fname);
            this->addChild(_csb);
        }
        useTouchMaker(this);
        return true;
    }
private:
    Node* _csb{ nullptr };
};

template <typename T>
class PhysicsBaseScene : public BaseScene<T>
{
public:
    virtual ~PhysicsBaseScene() = default;
    static cocos2d::Scene* createScene()
    {
        auto scene = Scene::createWithPhysics();
        auto layer = T::create();
        scene->addChild(layer);
        return scene;
    }
};



#endif /* defined(__okeya__BaseScene__) */
