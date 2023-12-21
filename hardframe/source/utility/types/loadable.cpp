#include <hardframe/utility/loadable.hpp>
namespace hf {
    namespace util {

        // Construct. If it loads successfully return the load state
        loadable::loadable() {
            loaded = false;
        }

        // Check if loaded, can have extra checking code
        bool loadable::isLoaded() {
            return loaded;
        }

        bool loadable::load() {
            return isLoaded();
        }

    }
}