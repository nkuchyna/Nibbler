//
// Created by Nadiia KUCHYNA on 2019-01-15.
//
#include "DLibManager.h"
#include "ErrorException.h"

DLibManager::DLibManager(){
    this->init();
    this->load(SDL);
    this->load(SDL_MIXER);
}

DLibManager::DLibManager(eDLib type){
    this->init();
    this->load(type);
}

DLibManager::~DLibManager(){

}

DLibManager::DLibManager(const DLibManager &obj) {
    *this = obj;
}

DLibManager& DLibManager::operator=(const DLibManager &obj) {

    if (&obj != this)
    {
        this->_s_map_DLibPath.clear();
        this->_s_map_DLibPath.insert(obj._s_map_DLibPath.begin(), obj._s_map_DLibPath.end());
        if (this->_renderDLib)
            dlclose(this->_renderDLib);
        this->_renderDLib = obj._renderDLib;
        if (this->_sPlayerDLib)
            dlclose(this->_sPlayerDLib);
        this->_sPlayerDLib = obj._sPlayerDLib;
        this->_create_render = obj._create_render;
        this->_destroy_render = obj._destroy_render;
    }
    return (*this);
}

void    DLibManager::init() {

    _s_map_DLibPath[SDL] = "./DLIB1/DLIB1.so";
    _s_map_DLibPath[SFML] = "./DLIB2/DLIB2.so";
    _s_map_DLibPath[OPENGL] = "./DLIB3/DLIB3.so";
    _s_map_DLibPath[SDL_MIXER] = "./DLIB_SPLayer/DLIB_SPLayer.so";
}

void    DLibManager::load(eDLib type) {
   
    if (type == SDL || type == SFML || type == OPENGL) {
        this->_renderDLib = dlopen(_s_map_DLibPath[type].c_str(), RTLD_LAZY);
        if (!_renderDLib) {
            throw (ErrorException("Can not load Dlib from " + _s_map_DLibPath[type]));
        }
        this->_create_render = (create_t) dlsym(_renderDLib, "create");
        this->_dlsym_error = dlerror();
        if (this->_dlsym_error) {
            throw (ErrorException("Can not load function \"create\""));
        }
        this->_destroy_render = (destroy_t) dlsym(_renderDLib, "destroy");
        if (dlerror()) {
            throw (ErrorException("Can not load function \"destroy\""));
        }
    } else if (type == SDL_MIXER) {
        this->_sPlayerDLib = dlopen(_s_map_DLibPath[type].c_str(), RTLD_LAZY);
        if (!_sPlayerDLib) {
            throw (ErrorException("Can not load Dlib from " + _s_map_DLibPath[type]));
        }
        this->_create_splayer = (createSPlayer_t) dlsym(_sPlayerDLib, "create");
        if (dlerror()) {
            throw (ErrorException("Can not load function \"create\""));
        }
        this->_destroy_splayer = (destroySPlayer_t) dlsym(_sPlayerDLib, "destroy");
        if (dlerror()) {
            throw (ErrorException("Can not load function \"destroy\""));
        }
    }
}

void    DLibManager::reload(eDLib type) {

    dlclose(this->_renderDLib);
    this->load(type);
}

IRender*    DLibManager::createRender(){

    return(this->_create_render());
}

void        DLibManager::destroyRender(IRender* renderPtr){

    this->_destroy_render(renderPtr);
}

ISPlayer*   DLibManager::createSoundsPlayer() {

    return(this->_create_splayer());
}

void        DLibManager::destroySoundsPlayer(ISPlayer* sPlayerPtr) {

    this->_destroy_splayer(sPlayerPtr);
}

void        DLibManager::closeDLibs(){

   if (this->_renderDLib)
       dlclose(this->_renderDLib);
}