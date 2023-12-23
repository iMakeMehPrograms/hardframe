#include <hardframe/graphics/opgl/base.hpp>
#include <hardframe/utility/general.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
    hf::opgl::window win(1000, 1000, "Tester");

    win.open();
    SDL_Event e;

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

    return 0;
}