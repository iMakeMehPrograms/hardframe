#include<string>
#include<iostream>
#include<queue>

#pragma startup init()

namespace hf {
    namespace util {

        // Do not directly use this, use the functions
        std::queue<std::string> debug_list;

        bool use_default_output;
        bool console_output;

        void init() {
            use_default_output = true;
            console_output = false;
            debug_list = {};
        }

        void addMessage(std::string message);

        void defOutput(std::string message);

        std::string takeMessage();

        bool messageRemaining();
    }
}