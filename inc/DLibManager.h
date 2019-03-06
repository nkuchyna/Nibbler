//
// Created by Nadiia KUCHYNA on 2019-01-15.
//
#ifndef NIBLER_DLIB_MANAGER_H
#define NIBLER_DLIB_MANAGER_H
#include "Nibbler.h"
#include "IRender.h"
#include "ISPlayer.h"
#include <dlfcn.h>


typedef IRender* (*create_t)();
typedef IRender* (*destroy_t)(IRender*);

typedef ISPlayer* (*createSPlayer_t)();
typedef ISPlayer* (*destroySPlayer_t)(ISPlayer*);

class   DLibManager {

public:
    DLibManager();
    ~DLibManager();
    DLibManager(const DLibManager &obj);
    DLibManager& operator=(const DLibManager &obj);

    DLibManager(eDLib type);

    IRender*        createRender();
    void            destroyRender(IRender* renderPtr);
    void            reload(eDLib type);

    ISPlayer*       createSoundsPlayer();
    void            destroySoundsPlayer(ISPlayer* sPlayerPtr);
    void                closeDLibs();

private:
    void        init();
    void        load(eDLib type);

    void        *_renderDLib;
    void        *_sPlayerDLib;

    const char*         _dlsym_error;
    create_t            _create_render;
    destroy_t           _destroy_render;
    createSPlayer_t     _create_splayer;
    destroySPlayer_t    _destroy_splayer;


    std::map<eDLib, std::string> _s_map_DLibPath;
};

#endif //NIBLER_DLIB_H
