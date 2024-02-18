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
#include <glm/gtx/quaternion.hpp>

#pragma once

namespace hf {
    namespace util {

        struct transform {
            glm::vec3 pos;
            glm::quat rot;
            glm::vec3 scale;
        };

        void localizeToRotation(glm::vec3 &vec, transform &trans);
        void localizeToPosition(glm::vec3 &vec, transform &trans);

        void setRotationAxis(float angle, glm::vec3 &axis, transform &trans);
        void addRotationAxis(float angle, glm::vec3 &axis, transform &trans);

        void setRotationCompound(glm::vec3 &euler, transform &trans);
        void addRotationCompound(glm::vec3 &euler, transform &trans);

        glm::quat eulerToQuat(glm::vec3 euler);

    }
}