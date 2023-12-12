#define PI 3.141592f
#define TAU 6.283184f

namespace hf {
    namespace util {

        // Casts
        
        template<typename T> T implicit_cast(T target) {
            return target;
        }

        // Spatial Structs

        class vec3 {
            public:
                float x, y, z;
            
            vec3(float sx, float sy, float sz);
            vec3();
        };

        class transform3 {
            public:
                vec3 pos;
                vec3 rot;
                vec3 scale;
            
            transform3();
        };

        class vec2 {
            public:
                float x, y;
            
            vec2(float sx, float sy);
            vec2();
        };

        class transform2 {
            public:
                vec2 pos;
                vec2 rot;
                vec2 scale;
            
            transform2();
        };

        class quater {
            public:
                float s, i, j, k;
        };

        // Loadable

        class loadable {
            private:
                bool loaded = false;

            public:
                bool isLoaded();
                bool load();

                loadable();
        };
    }
}