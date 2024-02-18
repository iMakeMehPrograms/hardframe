/*
    Copyright (c) 2023, iMakeMehThings 
    You may redistribute, use, and modify this code unde the terms of the BSD 3-Clause license.
    The license text should be available in the file named LICENSE, or found here:
    https://github.com/iMakeMehPrograms/hardframe/tree/main?tab=BSD-3-Clause-1-ov-file
*/

#include <hardframe/utility/spatial.hpp>

namespace hf {
    namespace util {
        
        void localizeToRotation(glm::vec3 &vec, transform &trans) {
            vec = vec * trans.rot;
        }
        void localizeToPosition(glm::vec3 &vec, transform &trans) {
            vec = vec + trans.pos;
        }

        void setRotationAxis(float angle, glm::vec3 &axis, transform &trans) {
            trans.rot = trans.rot * glm::angleAxis(glm::radians(angle), axis);
        }
        void addRotationAxis(float angle, glm::vec3 &axis, transform &trans) {
            trans.rot = trans.rot * glm::angleAxis(glm::radians(angle), axis * trans.rot);
        }

        void setRotationCompound(glm::vec3 &euler, transform &trans) {
            trans.rot = trans.rot * glm::angleAxis(glm::radians(euler.x), glm::vec3(1.0f, 0.0f, 0.0f));
            trans.rot = trans.rot * glm::angleAxis(glm::radians(euler.y), glm::vec3(0.0, 1.0f, 0.0f));
            trans.rot = trans.rot * glm::angleAxis(glm::radians(euler.z), glm::vec3(0.0, 0.0f, 1.0f));
        }
        void addRotationCompound(glm::vec3 &euler, transform &trans) {
            trans.rot = trans.rot * glm::angleAxis(glm::radians(euler.x), glm::vec3(1.0f, 0.0f, 0.0f) * trans.rot);
            trans.rot = trans.rot * glm::angleAxis(glm::radians(euler.y), glm::vec3(0.0, 1.0f, 0.0f) * trans.rot);
            trans.rot = trans.rot * glm::angleAxis(glm::radians(euler.z), glm::vec3(0.0, 0.0f, 1.0f) * trans.rot);
        }

        glm::quat eulerToQuat(glm::vec3 euler) {
            return glm::quat(euler);
        }

    }
}