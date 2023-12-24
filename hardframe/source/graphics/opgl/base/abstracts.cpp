#include<hardframe/graphics/opgl/base.hpp>
namespace hf {
    namespace opgl {

        // Window
        bool window::isOpen() {
            return is_open;
        }

        void window::close() {
            SDL_DestroyWindow(sdl_win);
            sdl_win = NULL;
            is_open = false;
            SDL_Quit();
        }

        bool window::getEvent(SDL_Event *event) {
            return SDL_PollEvent( event );
        }

        SDL_Event window::getEvent() {
            SDL_Event event;
            SDL_PollEvent( &event );
            return event;
        }

        uint8_t window::open() {
            Uint32 flags = SDL_WINDOW_OPENGL;
            SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO);
            sdl_win = SDL_CreateWindow(sdl_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
            std::cout << " testo " << std::endl;

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // set to core version
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, rbits);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, gbits);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, bbits);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, dbits);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);

            context = SDL_GL_CreateContext(sdl_win);

            // GLEW Setup
            glewExperimental = GL_TRUE;
            GLenum error = glewInit();
            std::cout << glewGetErrorString(error) << std::endl;

            // GL Setup
            glEnable(GL_DEPTH_TEST);

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

            // Finally, make the screen black. glClearColor is already set soo...
            glClear(GL_COLOR_BUFFER_BIT);
            SDL_GL_SwapWindow(sdl_win);
            is_open = true;

            SDL_GL_MakeCurrent(sdl_win, context);
            return 0;
        }

        window::window(unsigned int w, unsigned int h, std::string nm) : sdl_name(nm.c_str()) {
            // Width and height
            width = w;
            height = h;

            // Default settings for the depths
            rbits = 8;
            gbits = 8;
            bbits = 8;
            dbits = 16;

            name = nm;
        }

        window::window(unsigned int rb, unsigned int gb, unsigned int bb, unsigned int db, unsigned int w, unsigned int h, std::string nm) : sdl_name(nm.c_str()) {
            // Width and height
            width = w;
            height = h;

            // Default settings for the depths
            rbits = rb;
            gbits = gb;
            bbits = bb;
            dbits = db;

            name = nm;
        }

        window::~window() {
            close();
        }



        // Camera
        
    }
}