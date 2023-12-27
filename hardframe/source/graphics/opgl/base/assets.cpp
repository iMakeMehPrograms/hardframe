#include<hardframe/graphics/opgl/base.hpp>
namespace hf {
    namespace opgl {
        
        // Mesh Stuff
        mesh::mesh(mesh_data load) {
            data = {load.points, load.groups};

            float ldr_points[data.points.size()];
            unsigned int ldr_groups[data.groups.size()];

            for(size_t i = 0; i < data.points.size(); i++) {

            }
        }
    }
}