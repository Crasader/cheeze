#ifndef __okeya__BGMPlayer__
#define __okeya__BGMPlayer__

#include "audio/include/AudioEngine.h"
#include "cocos2d.h"

using namespace cocos2d;
using namespace cocos2d::experimental;

class BGMPlayer
{
public:
    static int play(const std::string& path);
    static int play2d(const std::string& path);
    static void play2du(const std::string& path);
    static void setVolume(const int volume);
    static void setVolumeSE(const int volume);
    inline static void setMute(bool b){ BGMPlayer::_mute = b; }
    inline static const float getVolume(){ return BGMPlayer::_volume; }
    inline static const float getVolumeSE(){ return BGMPlayer::_volumeSE; }
    static void stopAll();
    static void pauseAll(){ AudioEngine::pauseAll(); }
    static void resumeAll(){ AudioEngine::resumeAll(); }
private:
    static std::string _currentMusic;
    static int _currentAudioId;
    static int _volume;
    static int _volumeSE;
    static bool _mute;
    static std::string _prevSE;
};

#endif /* defined(__okeya__BGMPlayer__) */
