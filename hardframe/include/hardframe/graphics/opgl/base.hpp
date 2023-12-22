#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

//#include <hardframe/utility/debug.hpp>
#include <string>
#include <iostream>
#include <cstdlib>  

namespace hf {
    namespace opgl {

        // Window
        class window {
            private:
                bool open = false;
                const char* sdl_name;

            public:
                // SDL Variables
                SDL_Window* sdl_win;
                SDL_GLContext context;

                std::string name;

                // Color+Z Depth Variables
                unsigned int rbits;
                unsigned int gbits;
                unsigned int bbits;
                unsigned int dbits;

                // Window Variables
                unsigned int width;
                unsigned int height;

                // Creates the window with default settings. W is for width, H for height, and IM if you want to immediately open the context and window or if you want to delay the initialization (true is immediate).
                window(unsigned int w, unsigned int h, std::string nm, bool im);

                // Creates the window. The first 4 variables are rgb+z depths, the next 2 are width+height, and the last one is if you want to immediately initialize the window or not (true is immediate).
                window(
                unsigned int rb,
                unsigned int gb,
                unsigned int bb,
                unsigned int db,
                unsigned int w,
                unsigned int h,
                std::string nm,
                bool im
                );

                ~window();

                uint8_t init();

                bool isOpen();

                void close();

                SDL_Event getEvent();
                uint8_t getKeys();
        };
    }
}