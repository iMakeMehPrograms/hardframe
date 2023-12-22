#include<string>
#include<iostream>
#include<queue>
namespace hf {
    namespace util {

        enum errors {

        };

        // Do not directly use this, use the functions
        std::queue<std::string> debug_list = {};

        bool use_default_output = true;
        bool console_output = false;

        void addMessage(std::string message);

        void defOutput(std::string message);

        std::string takeMessage();

        bool messageRemaining();
    }
}