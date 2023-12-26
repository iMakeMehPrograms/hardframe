#pragma once
namespace hf {
    namespace util {
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