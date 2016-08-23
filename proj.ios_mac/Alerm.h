#ifndef Alerm_hpp
#define Alerm_hpp

#include "cocos2d.h"
#include "CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class Alerm : public Node
{
public:
    static constexpr auto ONE_HOUR = 3600;
    static constexpr auto ONE_DAY = 24 * 3600;
    static constexpr auto ONE_MINUTE = 60;
    void start(const std::string& name, TextBMFont* display);
    void setSecFromNow(const int sec);
    void setCallback(std::function<void(void)> callback) { _callback = callback; }
    bool isWorking(){ return _ringSec > 0; }
    CREATE_FUNC(Alerm);
private:
    float _dt { 0.0f };
    TextBMFont* _display { nullptr };
    inline void setDisplay(TextBMFont* display) { _display = display; }
    inline TextBMFont* getDisplay() const { return _display; }
    long long _currentSec { 0 };
    long long _ringSec { 0 };
    std::function<void(void)> _callback { [](){} };
    void saveRingSec();
};


#endif /* Alerm_hpp */
