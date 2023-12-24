#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

namespace hf {
    namespace util {

        class transform {
            public:
            glm::vec3 pos;
            glm::vec3 rot;
            glm::vec3 scale;

            transform();
            transform(glm::vec3 p, glm::vec3 r, glm::vec3 s);
        };

    }
}