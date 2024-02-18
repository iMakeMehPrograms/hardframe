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

    hf::opgl::mesh_data ldr = {{}, {}};
    hf::opgl::loadOBJ(ldr, "files/uvcube.obj");
    hf::opgl::mesh cube(ldr);
    hf::opgl::loadOBJ(ldr, "files/rocky_terrain.obj");
    hf::opgl::mesh terrain(ldr);

    hf::opgl::image stone_albedo("files/stonemix_eb_reg.png");
    hf::opgl::material stone = {stone_albedo};

    hf::opgl::shader flat("files/shaders/vert_testing2.glsl", "files/shaders/frag_testing2.glsl");
    hf::opgl::camera camera(45.0f, {{0,0,10}, hf::util::eulerToQuat({0,0,0}), {1, 1, 1}});
    camera.ortho = false;

    hf::opgl::object block = {{{0,0,0}, hf::util::eulerToQuat({15, 15, 15}), {1, 1, 1}}, cube, flat, stone};
    hf::opgl::object ground = {{{0,-3, 0}, hf::util::eulerToQuat({0,0,0}), {10, 5, 10}}, terrain, flat, stone};
    hf::opgl::renderer render = hf::opgl::renderer();
    render.colorSwitch(true);

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
                frame_relax = 2000;
            }
        }

        if(frame_relax != 0) {
            frame_relax -= 1;
        }

        hf::util::localizeToRotation(move_dir, camera.trans);
        camera.trans.pos += move_dir;
        hf::util::addRotationCompound(rot_dir, camera.trans);

        render.prepare(win, camera);

        render.renderObject(win, camera, ground);
        render.renderObject(win, camera, block);

        render.blit(win);
    }

    hf::util::addMessage({"Exiting loop.", hf::util::error_code::non_error, hf::util::log_level::verbose});

    return 0;
}