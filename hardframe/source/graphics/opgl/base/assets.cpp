/*
    Copyright (c) 2023, iMakeMehThings 
    You may redistribute, use, and modify this code unde the terms of the BSD 3-Clause license.
    The license text should be available in the file named LICENSE, or found here:
    https://github.com/iMakeMehPrograms/hardframe/tree/main?tab=BSD-3-Clause-1-ov-file
*/

#include<hardframe/graphics/opgl/base.hpp>

#define STB_IMAGE_IMPLEMENTATION // motherf*cker only works when it is included once 
#include <stb_image.h> // include guards and pragma don't work for some dumb*ss reason

namespace hf {
    namespace opgl {
        
        // Mesh Stuff
        mesh::mesh(mesh_data load) : vao(0), vbo(0), ebo(0) {
            data = {load.points, load.groups};

            float ldr_points[data.points.size()];
            unsigned int ldr_groups[data.groups.size()];

            for(size_t i = 0; i < data.points.size(); i++) {
                ldr_points[i] = load.points[i];
            }

            for(size_t i = 0; i < data.groups.size(); i++) {
                ldr_groups[i] = load.groups[i];
            }

            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ebo);

            glBindVertexArray(vao);

            // do the vbo
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(ldr_points), ldr_points, GL_STATIC_DRAW);

            // do the ebo
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ldr_groups), ldr_groups, GL_STATIC_DRAW);

            // Set the attributes
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);

            glEnableVertexAttribArray(0);
        }

        void loadOBJ(mesh_data& storage, std::string filename) {
            storage.points.clear();
            storage.groups.clear();
            std::ifstream file;
            file.open(filename);
            if(!file.is_open()) {
                exit(1);
            }

            std::string line;
            std::string mode;
            std::vector<std::vector<float>> points;
            std::vector<std::vector<float>> norms;
            std::vector<std::vector<float>> uvs;
            std::vector<std::string> tokens;
            std::string token;
            std::stringstream tokenizer;
            while(std::getline(file, line)) {
                // tokenize
                tokens.clear();
                token = "";
                if(line.length() <= 1) continue; // if nothing continue
                if(line[0] == '#') continue; // ignore comments entirely
             
                tokenizer = std::stringstream(line);
                while(getline(tokenizer, token, ' ')) {
                    tokens.push_back(token);
                }

                if(tokens[0].compare("#") == 0) continue;

                if(tokens[0].compare("v") == 0) {
                    points.push_back({std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]), 1.0f, 1.0f, 1.0f, 0.0f, 0.0f}); // Add a vert to the list with everything
                    continue;
                }   
                if(tokens[0].compare("vt") == 0) {
                    uvs.push_back({std::stof(tokens[1]), std::stof(tokens[2])});
                    continue;
                } 
                if(tokens[0].compare("vn") == 0) { 
                    norms.push_back({std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3])});
                    continue;
                }
                if(tokens[0].compare("f") == 0) {
                    std::vector<std::string> subtokens;
                    std::string subtoken;
                    std::stringstream subtokenizer;
                    for(size_t e = 0; e < 3; e++) {
                        subtokens.clear();
                        subtoken = "";
                        subtokenizer = std::stringstream(tokens[e + 1]);
                        while(getline(subtokenizer, subtoken, '/')) {
                            subtokens.push_back(subtoken);
                        }

                        int row = std::stoi(subtokens[0]) - 1;
                        storage.groups.push_back(row);

                        points[row][6] = uvs[std::stoi(subtokens[1]) - 1][0];
                        points[row][7] = uvs[std::stoi(subtokens[1]) - 1][1];
                        
                        points[row][3] = norms[std::stoi(subtokens[2]) - 1][0];
                        points[row][4] = norms[std::stoi(subtokens[2]) - 1][1];
                        points[row][5] = norms[std::stoi(subtokens[2]) - 1][2];
                    }
                }
            }
            for(size_t i = 0; i < points.size(); i++) {
                for(size_t e = 0; e < points[1].size(); e++) {
                    storage.points.push_back(points[i][e]);
                }
            }
        }

        // Shader
        shader::shader(std::string vn, std::string fn) {
            vert_name = vn;
            frag_name = fn;

            // file > ifstream > stringstream > string > c-string
            std::string ldr_vert_code;
            std::string ldr_frag_code;
            std::ifstream vert_file;
            std::ifstream frag_file;
            vert_file.open(vert_name);
            frag_file.open(frag_name);
            if(!vert_file.good() || !frag_file.good()) util::addMessage({"Couldn't open shader files!", util::error_code::shaders_not_found, util::log_level::fatal});
            std::stringstream vertStream;
            std::stringstream fragStream;
            vertStream << vert_file.rdbuf();
            fragStream << frag_file.rdbuf();
            vert_file.close();
            frag_file.close();
            ldr_vert_code = vertStream.str();
            ldr_frag_code = fragStream.str();
            const char* ldr_char_vert = ldr_vert_code.c_str();
            const char* ldr_char_frag = ldr_frag_code.c_str();

            unsigned int vertsh;
            unsigned int fragsh;
            int success;
            char log[512];

            // Compile the shaders
            vertsh = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertsh, 1, &ldr_char_vert, NULL);
            glCompileShader(vertsh);

            glGetShaderiv(vertsh, GL_COMPILE_STATUS, &success);
            if(!success) {
                glGetShaderInfoLog(vertsh, 512, NULL, log);
                util::addMessage({util::stringPlusCString("Vertex shader didn't compile!\n", log), util::error_code::shader_compile_issue, util::log_level::fatal});
            }

            fragsh = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragsh, 1, &ldr_char_frag, NULL);
            glCompileShader(fragsh);

            glGetShaderiv(fragsh, GL_COMPILE_STATUS, &success);
            if(!success) {
                glGetShaderInfoLog(fragsh, 512, NULL, log);
                util::addMessage({util::stringPlusCString("Fragment shader didn't compile!", log), util::error_code::shader_compile_issue, util::log_level::fatal});
            }              

            handle = glCreateProgram();
            glAttachShader(handle, vertsh); 
            glAttachShader(handle, fragsh);
            glLinkProgram(handle);

            glGetProgramiv(handle, GL_LINK_STATUS, &success);
            if(!success) {
                glGetProgramInfoLog(handle, 512, NULL, log);
                util::addMessage({util::stringPlusCString("Vertex+Fragment shader linking didn't work!", log), util::error_code::shader_linking_issue, util::log_level::fatal});
            }

            glDeleteShader(vertsh);
            glDeleteShader(fragsh);
        }

        image::image(std::string imn) {
            const char *file_name = imn.c_str();

            glGenTextures(1, &handle);
            glBindTexture(GL_TEXTURE_2D, handle);

            // Default texture settings. No real reason to change them
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            int w, h, c;

            stbi_set_flip_vertically_on_load(true);
            unsigned char *data = stbi_load(file_name, &w, &h, &c, 0);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

            width = util::implicit_cast<unsigned int>(w);
            height = util::implicit_cast<unsigned int>(h);
            channels = util::implicit_cast<unsigned int>(c);

            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
        }
    }
}