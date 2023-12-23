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
                bool is_open = false;
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

                // Creates the window with default settings. W is for width, H for height, nm for name
                window(unsigned int w, unsigned int h, std::string nm);

                // Creates the window. The first 4 variables are rgb+z depths, the next 2 are width+height, last one is the name
                window(
                unsigned int rb,
                unsigned int gb,
                unsigned int bb,
                unsigned int db,
                unsigned int w,
                unsigned int h,
                std::string nm
                );

                ~window();

                uint8_t open();
                bool isOpen();
                void close();

                // Input. Get events has both a pass by copy and pass by reference. 
                bool getEvent(SDL_Event *event);
                SDL_Event getEvent();
                uint8_t getKeys();
        };
    }
}