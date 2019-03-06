//
// Created by Nadiia KUCHYNA on 2019-01-28.
//

#ifndef NIBLER_ISPLAYER_H
#define NIBLER_ISPLAYER_H

enum    eSounds
{
    CLICK,
    MOVE,
    EAT,
    SUPER_EAT,
    WIN_SOUND,
    FAIL_SOUND,
    SOUNDS_NBR
};

enum eMusic
{
    MENU_MUSIC,
    GAME_MUSIC,
    MUSIC_NBR
};

class   ISPlayer
{
public:
    virtual void    playSound(eSounds type) = 0;
    virtual void    playMusic(eMusic type) = 0;

    virtual void    stopSound() = 0;
    virtual void    stopMusic() = 0;

    virtual ~ISPlayer() {}
};


#endif //NIBLER_ISPLAYER_H
