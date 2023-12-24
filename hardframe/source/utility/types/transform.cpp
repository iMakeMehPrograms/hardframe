#include <hardframe/utility/spatial.hpp>
namespace hf {
    namespace util {
        
        transform::transform() : pos(glm::vec3(0,0,0)), rot(glm::vec3(30,0,0)), scale(glm::vec3(1,1,1)) {}
            
        transform::transform(glm::vec3 p, glm::vec3 r, glm::vec3 s) : pos(p), rot(r), scale(s) {}
    }
}