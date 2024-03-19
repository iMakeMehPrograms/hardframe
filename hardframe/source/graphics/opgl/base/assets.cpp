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

        // Loads the specified object from the OBJ file
        void loadSubOBJ(mesh_data& storage, std::string filename, std::string subobject) {
            std::ifstream file(filename);
            if(!file.is_open()) {
                util::addMessage({"OBJ file could not be found!", util::error_code::model_not_found, util::log_level::fatal});
                util::safeExit();
            }
            
            std::vector<glm::vec3> positions;
            std::vector<glm::vec3> normals;
            std::vector<glm::vec2> uv_coords;

            std::vector<std::vector<std::string>> position_face;
            std::vector<std::vector<int>> position_face_index;

            std::vector<std::vector<float>> verticies;
            std::vector<unsigned int> faces;

            std::stringstream tokenizer;
            std::vector<std::string> token_list;
            std::string token_ldr;
            std::string line;

            std::stringstream subtokenizer;
            std::vector<std::string> subtoken_list;
            std::string subtoken_ldr;
            int posnum, uvnum, nornum, newnum;
            bool foundmodel = (subobject.compare("") == 0);
            bool founduv = false;
            while(std::getline(file, line)) {
                token_list.clear();
                token_ldr = "";
                if(line.size() <= 1) continue;
                if(line[0] == '#') continue;

                tokenizer = std::stringstream(line);
                while(getline(tokenizer, token_ldr, ' ')) {
                    token_list.push_back(token_ldr);
                }

                if(token_list[0].compare("o") == 0) {
                    if(subobject.compare("") == 0) {
                        foundmodel = true;
                        continue;
                    }
                    if(token_list[1].compare(subobject) == 0) {
                        foundmodel = true; 
                    } else {
                        foundmodel = false;
                    }
                }

                if(!foundmodel) continue;

                if(token_list[0].compare("v") == 0) { // Add a position to the list
                    positions.push_back({std::stof(token_list[1]), std::stof(token_list[2]), std::stof(token_list[3])});
                    position_face.push_back({});
                    position_face_index.push_back({});
                    continue;
                }

                if(token_list[0].compare("vn") == 0) { // Add a normal to the list
                    normals.push_back({std::stof(token_list[1]), std::stof(token_list[2]), std::stof(token_list[3])});
                    continue;
                }

                if(token_list[0].compare("vt") == 0) { // Add a normal to the list
                    uv_coords.push_back({std::stof(token_list[1]), std::stof(token_list[2])});
                    continue;
                }

                if(token_list[0].compare("f") == 0) {
                    for(unsigned int i = 0; i < 3; i++) {
                        subtoken_list.clear();
                        subtoken_ldr = "";

                        subtokenizer = std::stringstream(token_list[i + 1]);
                        while(getline(subtokenizer, subtoken_ldr, '/')) {
                            subtoken_list.push_back(subtoken_ldr);
                        }

                        posnum = std::stoi(subtoken_list[0]) - 1;
                        uvnum = std::stoi(subtoken_list[1]) - 1;
                        nornum = std::stoi(subtoken_list[2]) - 1;

                        if(position_face[posnum].size() <= 0) {
                            verticies.push_back({positions[posnum].x, positions[posnum].y, positions[posnum].z, normals[nornum].x, normals[nornum].y, normals[nornum].z, uv_coords[uvnum].x, uv_coords[uvnum].y});
                            newnum = verticies.size() - 1;

                            faces.push_back(newnum);

                            position_face[posnum].push_back(token_list[i + 1]);
                            position_face_index[posnum].push_back(newnum);
                        } else {
                            founduv = false;
                            for(unsigned int e = 0; e < position_face[posnum].size(); e++) {
                                std::cout << position_face[posnum][e] << " | " << token_list[i + 1] << std::endl;
                                if(position_face[posnum][e].compare(token_list[i + 1])) {
                                    faces.push_back(position_face_index[posnum][e]);
                                    founduv = true;
                                    break;
                                }
                            }
                            if(!founduv) {
                                verticies.push_back({positions[posnum].x, positions[posnum].y, positions[posnum].z, normals[nornum].x, normals[nornum].y, normals[nornum].z, uv_coords[uvnum].x, uv_coords[uvnum].y});
                                newnum = verticies.size() - 1;

                                faces.push_back(newnum);

                                position_face[posnum].push_back(token_list[i + 1]);
                                position_face_index[posnum].push_back(newnum);
                            }
                        }
                    }
                }

            }
            for(unsigned int i = 0; i < verticies.size(); i++) {
                for(unsigned int e = 0; e < verticies[i].size(); e++) {
                    storage.points.push_back(verticies[i][e]);
                }
            }
            for(unsigned int i = 0; i < faces.size(); i++) {
                storage.groups.push_back(faces[i]);
            }
        }

        // Loads the whole OBJ file
        void loadOBJ(mesh_data& storage, std::string filename) {
            loadSubOBJ(storage, filename, "");
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

            if(!vert_file.good() || !frag_file.good()) {
                util::addMessage({"Couldn't find shader files!", util::error_code::shaders_not_found, util::log_level::fatal});
                util::safeExit();
            }

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
                util::safeExit();
            }

            fragsh = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragsh, 1, &ldr_char_frag, NULL);
            glCompileShader(fragsh);

            glGetShaderiv(fragsh, GL_COMPILE_STATUS, &success);
            if(!success) {
                glGetShaderInfoLog(fragsh, 512, NULL, log);
                util::addMessage({util::stringPlusCString("Fragment shader didn't compile!", log), util::error_code::shader_compile_issue, util::log_level::fatal});
                util::safeExit();
            }              

            handle = glCreateProgram();
            glAttachShader(handle, vertsh); 
            glAttachShader(handle, fragsh);
            glLinkProgram(handle);

            glGetProgramiv(handle, GL_LINK_STATUS, &success);
            if(!success) {
                glGetProgramInfoLog(handle, 512, NULL, log);
                util::addMessage({util::stringPlusCString("Vertex+Fragment shader linking didn't work!", log), util::error_code::shader_linking_issue, util::log_level::fatal});
                util::safeExit();
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
            if(data == nullptr) {
                util::addMessage({"Image not found!", util::error_code::image_not_found, util::log_level::fatal});
                util::safeExit();
            }

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

            width = util::implicit_cast<unsigned int>(w);
            height = util::implicit_cast<unsigned int>(h);
            channels = util::implicit_cast<unsigned int>(c);

            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
        }
    }
}