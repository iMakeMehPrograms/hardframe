/*
    Copyright (c) 2023, iMakeMehThings 
    You may redistribute, use, and modify this code unde the terms of the BSD 3-Clause license.
    The license text should be available in the file named LICENSE, or found here:
    https://github.com/iMakeMehPrograms/hardframe/tree/main?tab=BSD-3-Clause-1-ov-file
*/

#include <hardframe/graphics/opgl/base.hpp>
#include <hardframe/utility/debug.hpp>
#include <hardframe/utility/general.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
    hf::util::setupDebug(true, true, true, "files/error_log");

    hf::util::addMessage({"Initiating objects.", hf::util::error_code::non_error, hf::util::log_level::verbose});
    hf::opgl::window win(1000, 1000, "Tester");
    win.open();

    hf::util::error_code test = hf::util::error_code::non_error;

    hf::opgl::mesh_data ldr = {{}, {}};
    hf::opgl::loadOBJ(ldr, "files/uvcube.obj");
    hf::opgl::mesh tri(ldr);

    hf::opgl::shader flat("files/vert_testing.glsl", "files/frag_testing.glsl");

    hf::opgl::camera camera(90.0f, {{0,0,-100}, hf::util::eulerToQuat({0,0,0}), {1,1,1}});

    hf::opgl::object tri_obj0 = {{{0,0,-10}, hf::util::eulerToQuat({10,3,0}), {1,1,1}}, tri, flat};
    hf::opgl::object tri_obj1 = {{{5,2,-7}, hf::util::eulerToQuat({46,0,2}), {2,1,1}}, tri, flat};
    hf::opgl::object tri_obj2 = {{{9,1,-20}, hf::util::eulerToQuat({6,9,2}), {1,2,1}}, tri, flat};
    hf::opgl::object tri_obj3 = {{{8,8,-3}, hf::util::eulerToQuat({7,6,2}), {1,1,2}}, tri, flat};
    hf::opgl::object tri_obj4 = {{{6,0,-7}, hf::util::eulerToQuat({4,2,2}), {2,2,2}}, tri, flat};

    hf::opgl::renderer render = hf::opgl::renderer();

    hf::util::addMessage({"Entering loop.", hf::util::error_code::non_error, hf::util::log_level::verbose});

    SDL_Event e;

    const uint8_t* keymask;
    float rot_sens = 0.01f;
    float move_sens = 0.01f;

    glm::vec3 rot_dir(0.0f);
    glm::vec3 move_dir(0.0f);

    int frame_relax = 0;
    while(win.isOpen()) {
        while(win.getEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    win.close();
                break;
            }
            if(!win.isOpen()) break;
        }

        rot_dir = glm::vec3(0.0f);
        move_dir = glm::vec3(0.0f);

        keymask = SDL_GetKeyboardState(NULL);

        if(keymask[SDL_SCANCODE_ESCAPE]) {
            win.close();
            break;
        }

        if(keymask[SDL_SCANCODE_I]) {
            rot_dir.x += rot_sens;
        }
        if(keymask[SDL_SCANCODE_K]) {
            rot_dir.x -= rot_sens;
        }
        if(keymask[SDL_SCANCODE_J]) {
            rot_dir.y += rot_sens;
        }
        if(keymask[SDL_SCANCODE_L]) {
            rot_dir.y -= rot_sens;
        }

        if(keymask[SDL_SCANCODE_W]) {
            move_dir.y += move_sens;
        }
        if(keymask[SDL_SCANCODE_S]) {
            move_dir.y -= move_sens;
        }
        if(keymask[SDL_SCANCODE_A]) {
            move_dir.x += move_sens;
        }
        if(keymask[SDL_SCANCODE_D]) {
            move_dir.x -= move_sens;
        }

        if(keymask[SDL_SCANCODE_Q]) {
            move_dir.z += move_sens;
        }
        if(keymask[SDL_SCANCODE_E]) {
            move_dir.z -= move_sens;
        }

        if(keymask[SDL_SCANCODE_SPACE]) {
            if(frame_relax == 0) {
                hf::util::addMessage({glm::to_string(render.model), hf::util::error_code::non_error, hf::util::log_level::debug});
                frame_relax = 2000;
            }
        }

        if(frame_relax != 0) {
            frame_relax -= 1;
        }

        camera.trans.pos += move_dir;
        hf::util::addRotationCompound(rot_dir, camera.trans);

        render.prepare(win, camera);

        render.renderObject(win, camera, tri_obj0);
        render.renderObject(win, camera, tri_obj1);
        render.renderObject(win, camera, tri_obj2);
        render.renderObject(win, camera, tri_obj3);
        render.renderObject(win, camera, tri_obj4);

        render.blit(win);
    }

    hf::util::addMessage({"Exiting loop.", hf::util::error_code::non_error, hf::util::log_level::verbose});

    return 0;
}