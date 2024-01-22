#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <hardframe/utility/spatial.hpp>
#include <hardframe/utility/debug.hpp>
#include <hardframe/utility/general.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <string>
#include <iostream>
#include <cstdlib>  
#include <fstream>
#include <sstream>

#pragma once

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

        // Camera
        class camera {
            public:
                // Settings
                float near;
                float far;
                float fov;

                // Scale is not used
                util::transform trans;

                // Build with defaults
                camera(float field, util::transform tr);

                // Just think
                camera(float nr, float fr, float field, util::transform tr);
        };

        struct mesh_data {
            std::vector<float> points;
            std::vector<unsigned int> groups;
        };

        // Loads a obj into the specified mesh_data 
        void loadOBJ(mesh_data& storage, std::string filename);

        // Vertex Array Object (yay!)
        class mesh {
            public:
                // Handles
                unsigned int vao;
                unsigned int vbo;
                unsigned int ebo;

                mesh_data data;

                mesh(mesh_data ldr_data);

                bool load(mesh_data ldr_data);
        };

        class shader {
            public:
                unsigned int handle;
                std::string vert_name;
                std::string frag_name;

                shader(std::string vn, std::string fn);
        };

        struct object {
            util::transform trans;
            mesh &mesh;
            shader &shade;
        };

        class renderer {
            private:
                bool wireframe = false;
                
                // Default true because in scenes without skyboxes or other things it looks better
                bool clear_color = true;
            public:
                glm::mat4 model;
                glm::mat4 view;
                glm::mat4 proj;

                // You know what you did. We all know.
                renderer();

                // Render an object
                void renderObject(window& win, camera& cam, object& obj);

                // Prepare to render a frame with a specific window and camera
                void prepare(window& win, camera& cam);

                // Push to window
                void blit(window& win);

                // Clears the depth buffer only, if you want to render things on top of another.
                void redepth();

                // Gets the model matrix from object
                void setModelMatrix(object& obj);

                // Gets the view matrix from the camera
                void setViewMatrix(camera& cam);

                // Gets the projection matrix from the camera
                void setProjMatrix(window& win, camera& cam);

                // Set wireframe mode
                void wireframeSwitch(bool value);

                // Set color-clearing mode
                void colorSwitch(bool value);
        };

    }
}