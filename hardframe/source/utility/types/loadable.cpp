/*
    Copyright (c) 2023, iMakeMehThings 
    You may redistribute, use, and modify this code unde the terms of the BSD 3-Clause license.
    The license text should be available in the file named LICENSE, or found here:
    https://github.com/iMakeMehPrograms/hardframe/tree/main?tab=BSD-3-Clause-1-ov-file
*/

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