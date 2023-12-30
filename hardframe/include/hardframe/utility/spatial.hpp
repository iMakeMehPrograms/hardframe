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