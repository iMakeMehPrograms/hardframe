#include <hardframe/graphics/opgl/base.hpp>
#include <hardframe/utility/debug.hpp>
#include <hardframe/utility/general.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
    hf::util::setupDebug(true, true, true, "files/error_log");

    hf::util::addMessage({"Initiating objects.", hf::util::error_code::non_error, hf::util::log_level::verbose});
    hf::opgl::window win(1000, 1000, "Tester");

    win.open();
    SDL_Event e;

    hf::util::addMessage({"Entering loop.", hf::util::error_code::non_error, hf::util::log_level::verbose});

    while(win.isOpen()) {

        while(win.getEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    win.close();
                break;
            }
            if(!win.isOpen()) break;
        }
        
    }

    hf::util::addMessage({"Exiting loop.", hf::util::error_code::non_error, hf::util::log_level::verbose});

    return 0;
}