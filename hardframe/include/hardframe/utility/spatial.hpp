/*
    Copyright (c) 2023, iMakeMehThings 
    You may redistribute, use, and modify this code unde the terms of the BSD 3-Clause license.
    The license text should be available in the file named LICENSE, or found here:
    https://github.com/iMakeMehPrograms/hardframe/tree/main?tab=BSD-3-Clause-1-ov-file
*/

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#pragma once

namespace hf {
    namespace util {

        struct transform {
            glm::vec3 pos;
            glm::vec3 rot;
            glm::vec3 scale;
        };

    }
}