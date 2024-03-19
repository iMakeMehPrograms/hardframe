/*
    Copyright (c) 2023, iMakeMehThings 
    You may redistribute, use, and modify this code unde the terms of the BSD 3-Clause license.
    The license text should be available in the file named LICENSE, or found here:
    https://github.com/iMakeMehPrograms/hardframe/tree/main?tab=BSD-3-Clause-1-ov-file
*/

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

            if(SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) < 0) {
                util::addMessage({"SDL initalization failed!", util::error_code::sdl_init_fail, util::log_level::fatal});
                util::safeExit();
            }

            sdl_win = SDL_CreateWindow(sdl_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
            if(sdl_win == NULL) {
                util::addMessage({"SDL window didn't open!", util::error_code::sdl_window_fail, util::log_level::fatal});
                util::safeExit();
            }

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // set to core version
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, rbits);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, gbits);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, bbits);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, dbits);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);

            context = SDL_GL_CreateContext(sdl_win);
            if(context == NULL) {
                util::addMessage({"SDL-GL context couldn't be made!", util::error_code::sdl_gl_context_null, util::log_level::fatal});
                util::safeExit();
            }

            // GLEW Setup
            glewExperimental = GL_TRUE;
            GLenum error = glewInit();
            if(error != GLEW_NO_ERROR) {
                util::addMessage({"GLEW initalization failed!", util::error_code::glew_init_fail, util::log_level::message});
                util::safeExit();
            }

            // GL Setup
            glEnable(GL_DEPTH_TEST);
            glFrontFace(GL_CCW);

            glCullFace(GL_BACK);
            glEnable(GL_CULL_FACE);

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
        camera::camera(float field, util::transform tr) : fov(field), trans(tr), near(0.1f), far(1024.0f), ortho(false) {};

        camera::camera(float nr, float fr, float field, util::transform tr)  : near(nr), far(fr), fov(field), trans(tr), ortho(false) {};

        // Renderer
        renderer::renderer() : model(1.0f), view(1.0f), proj(1.0f), wireframe(false), clear_color(true) {};

        void renderer::renderObject(window& win, camera& cam, object& obj) {
            glUseProgram(obj.shade.handle);
            glBindVertexArray(obj.mesh.vao);

            setModelMatrix(obj);

            glUniform1i(glGetUniformLocation(obj.shade.handle, "iAlbedo"), 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, obj.mat.albedo.handle);

            glUniformMatrix4fv(glGetUniformLocation(obj.shade.handle, "iModel"), 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(glGetUniformLocation(obj.shade.handle, "iView"), 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(glGetUniformLocation(obj.shade.handle, "iProj"), 1, GL_FALSE, glm::value_ptr(proj));

            glDrawElements(GL_TRIANGLES, obj.mesh.data.groups.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        void renderer::prepare(window& win, camera& cam) {
            glClear(GL_DEPTH_BUFFER_BIT);
            if(clear_color) glClear(GL_COLOR_BUFFER_BIT);
            setViewMatrix(cam);
            setProjMatrix(win, cam);
        }

        void renderer::blit(window& win) {
            SDL_GL_SwapWindow(win.sdl_win);
        }

        void renderer::redepth() {
            glClear(GL_DEPTH_BUFFER_BIT);
        }

        void renderer::setModelMatrix(object& obj) {
            model = glm::mat4(1.0f);

            model = glm::translate(model, obj.trans.pos);
            model = glm::mat4_cast(obj.trans.rot) * model;
            model = glm::scale(model, obj.trans.scale);
        }

        void renderer::setViewMatrix(camera& cam) {
            view = glm::mat4(1.0f);

            view = glm::translate(view, -cam.trans.pos);
            view = glm::mat4_cast(cam.trans.rot) * view;
            view = glm::scale(view, glm::vec3(1.0f/cam.trans.scale.x, 1.0f/cam.trans.scale.y, 1.0f/cam.trans.scale.z));
        }

        void renderer::setProjMatrix(window& win, camera& cam) {
            proj = glm::mat4(1.0f);

            if(!cam.ortho) {
                proj = glm::perspective(glm::radians(cam.fov), util::implicit_cast<float>(win.width)/util::implicit_cast<float>(win.height), cam.near, cam.far);
            } else {
                proj = glm::ortho(0.0f, util::implicit_cast<float>(win.width), 0.0f, util::implicit_cast<float>(win.height), cam.near, cam.far);
            }
        }

        void renderer::wireframeSwitch(bool value) {
            if(value) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            } else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }

        void renderer::colorSwitch(bool value) {
            clear_color = value;
        } 
    }
}