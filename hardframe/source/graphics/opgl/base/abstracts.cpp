#include<hardframe/graphics/opgl/base.hpp>
namespace hf {
    namespace opgl {
        // Window

        bool window::isInit() {
            return open;
        }

        uint8_t window::init() {
            return 0;
        }

        window::window(unsigned int w, unsigned int h, bool im) {
            // Width and height
            width = w;
            height = h;

            // Default settings for the depths
            rbits = 8;
            gbits = 8;
            bbits = 8;
            dbits = 16;

            if(im) {
                init();
            }
        }

        window::window(unsigned int rb, unsigned int gb, unsigned int bb, unsigned int db, unsigned int w, unsigned int h, bool im) {
            // Width and height
            width = w;
            height = h;

            // Default settings for the depths
            rbits = rb;
            gbits = gb;
            bbits = bb;
            dbits = db;

            if(im) {
                init();
            }
        }
    }
}