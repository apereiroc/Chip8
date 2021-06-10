//
// Created by Asier Pereiro Castro on 30/1/21.
//

#include "screen.h"

screen::screen(): _window(nullptr), _renderer(nullptr), _texture(nullptr) 
{}

screen::~screen()
{
    // Don't worry if you forgot to close... I'll do it!
	if (!_isclosed)
        close();
}

bool screen::init(const std::string& name)
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
        return success;
    }
    
    // Create window
    _window = SDL_CreateWindow( (const char*) name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if ( _window == nullptr )
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
        return success;
    }
    

    return success;
}

bool screen::init()
{   
    return this->init("CHIP-8 EMULATOR");
}

void screen::close()
{
    // Free texture
    if (_texture != nullptr)
    {
        SDL_DestroyTexture( _texture );
        _texture = nullptr;
    }

    // Free renderer
    if (_renderer != nullptr)
    {
        SDL_DestroyRenderer( _renderer );
        _renderer = nullptr;
    }

    // Free window
    if (_window != nullptr)
    {
        SDL_DestroyWindow( _window );
        _window = nullptr;
    }

	// Clean up all initialised subsystems
	SDL_Quit();

    // Flip the flag to not close twice
    _isclosed = true;
}
