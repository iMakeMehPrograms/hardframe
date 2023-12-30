#include <hardframe/graphics/opgl/base.hpp>
#include <hardframe/utility/debug.hpp>
#include <hardframe/utility/general.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
    hf::util::setupDebug(true, true, true, "files/error_log");

    hf::util::addMessage({"Initiating objects.", hf::util::error_code::non_error, hf::util::log_level::verbose});
    hf::opgl::window win(1000, 1000, "Tester");
    win.open();

    hf::opgl::mesh tri({
        {
            0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
            -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
        },
        {
            0, 1, 3,
            1, 2, 3
        }
    });

    hf::opgl::shader flat("files/vert_testing.glsl", "files/frag_testing.glsl");

    hf::opgl::camera cam(45.0f, {{0,0,0}, {0,0,0}, {1,1,1}});
    hf::opgl::object tri_obj = {{{0,0,0}, {0,0,0}, {1,1,1}}, tri, flat};
    hf::opgl::renderer render = hf::opgl::renderer();

    hf::util::addMessage({"Entering loop.", hf::util::error_code::non_error, hf::util::log_level::verbose});

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

        render.prepare();
        render.renderObject(win, cam, tri_obj);
        render.blit(win);
    }

    hf::util::addMessage({"Exiting loop.", hf::util::error_code::non_error, hf::util::log_level::verbose});

    return 0;
}