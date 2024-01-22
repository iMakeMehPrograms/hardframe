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