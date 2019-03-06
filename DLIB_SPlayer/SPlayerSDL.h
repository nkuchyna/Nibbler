//
// Created by Nadiia KUCHYNA on 2019-01-28.
//

#ifndef NIBLER_SPLAYERSDL_H
#define NIBLER_SPLAYERSDL_H
#include "ISPlayer.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <map>
#include <iostream>
#include "ErrorException.h"

class   SPlayerSDL : public ISPlayer {

public:
    SPlayerSDL();
    ~SPlayerSDL();
    SPlayerSDL(const SPlayerSDL &obj);
    SPlayerSDL& operator=(const SPlayerSDL &obj);

    void    playSound(eSounds type) override;
    void    playMusic(eMusic type) override;
    void    stopSound() override;
    void    stopMusic() override;

private:
    Mix_Chunk*      _soundArr[SOUNDS_NBR];
    Mix_Music*      _musicArr[MUSIC_NBR];
    ErrorException  myEsception;

    void    init();
    void    loadResources();
    void    clearResources();
};

#endif //NIBLER_SOUNDSPLAYER_H
