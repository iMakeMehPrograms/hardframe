#include <hardframe/utility/utility.hpp>
namespace hf {
    namespace util {
        
        // 3D constructs
        vec3::vec3(float sx, float sy, float sz) {
            x = sx;
            y = sy;
            z = sz;
        }
        vec3::vec3() {
            x = 0;
            y = 0;
            z = 0;
        }

        transform3::transform3() {
            vec3 pos(0, 0, 0);
            vec3 rot(0, 0, 0);
            vec3 scale(1, 1, 1);
        }


        // 2D constructs
        vec2::vec2(float sx, float sy) {
            x = sx;
            y = sy;
        }
        vec2::vec2() {
            x = 0;
            y = 0;
        }

        transform2::transform2() {
            vec2 pos(0, 0);
            vec2 rot(0, 0);
            vec2 scale(1, 1);
        }
    }
}