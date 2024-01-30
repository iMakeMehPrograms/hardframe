/*
    Copyright (c) 2023, iMakeMehThings 
    You may redistribute, use, and modify this code unde the terms of the BSD 3-Clause license.
    The license text should be available in the file named LICENSE, or found here:
    https://github.com/iMakeMehPrograms/hardframe/tree/main?tab=BSD-3-Clause-1-ov-file
*/

#pragma once

namespace hf {
    namespace util {
        // Loadable

        class loadable {
            protected:
                bool loaded = false;

            public:
                bool isLoaded();
                bool load();

                loadable();
        };
    }
}