//
// Created by Asier Pereiro Castro on 30/1/21.
//

#ifndef CHIP8_SCREEN_H
#define CHIP8_SCREEN_H

#include <SDL.h>
#include <iostream>
#include "configs.h"

class screen {

public:
    screen();
    ~screen();
    bool init(const std::string& name);
    bool init();
    void close();

private:
    SDL_Window*   _window   = nullptr;  
    SDL_Renderer* _renderer = nullptr;
    SDL_Texture*  _texture  = nullptr;

    bool _isclosed = false;

};


#endif //CHIP8_SCREEN_H
