#include <chrono>
#include <iomanip>
#include "Alerm.h"
//#include "Player.h"

using namespace std::chrono;

void Alerm::start(const std::string& name, TextBMFont* display)
{
    setName(name);
    setDisplay(display);
    auto now = system_clock::now();;
    auto epoch = now.time_since_epoch();
    _currentSec = epoch.count() * system_clock::period::num / system_clock::period::den;
//    _ringSec = Player::getInstance()->getTimer(name);
    schedule([&](float dt){
        if(_ringSec < 1){
            return;
        }
        _dt += dt;
        if(_dt >= 1.0f){
            auto t = static_cast<int>(_dt / 1.0f);
            _currentSec += t;
            _dt = 0;
        }
        auto display = getDisplay();
        if(display){
            auto rest = _ringSec - _currentSec;
            auto hour = rest / ONE_HOUR;
            rest -= ONE_HOUR * hour;
            auto min = rest / ONE_MINUTE;
            auto sec = rest - ONE_MINUTE * min;
            std::stringstream ss;
            ss << std::setfill('0') << std::setw(2) << hour;
            ss << ":";
            ss << std::setfill('0') << std::setw(2) << min;
            ss << ":";
            ss << std::setfill('0') << std::setw(2) << sec;
            display->setString(ss.str());
        }
        if(_currentSec >= _ringSec){
            _callback();
            _ringSec = 0;
            display->setString("00:00:00");
            saveRingSec();
        }
    }, name);
}

void Alerm::setSecFromNow(const int sec)
{
    _ringSec = _currentSec + sec;
    saveRingSec();
}

void Alerm::saveRingSec()
{
//    auto player = Player::getInstance();
//    player->setTimer(getName(), _ringSec);
//    player->save();
}