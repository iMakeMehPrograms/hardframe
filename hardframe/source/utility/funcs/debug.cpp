#include <hardframe/utility/debug.hpp>
namespace hf {
    namespace util {
        
        void defOutput(std::string message) {
            if(console_output) std::cout << message << std::endl;
        }

        void addMessage(std::string message) {
            debug_list.push(message);
            if(use_default_output) {
                defOutput(message);
            }
        }

        std::string takeMessage() {
            std::string out = debug_list.front();
            debug_list.pop();
            return out;
        }

        bool messageRemaining() {
            return !debug_list.empty();
        }
    }
}