/*
    Copyright (c) 2023, iMakeMehThings 
    You may redistribute, use, and modify this code unde the terms of the BSD 3-Clause license.
    The license text should be available in the file named LICENSE, or found here:
    https://github.com/iMakeMehPrograms/hardframe/tree/main?tab=BSD-3-Clause-1-ov-file
*/

#include <hardframe/utility/debug.hpp>
#include <fstream>

namespace hf {
    namespace util {

        std::queue<log> debug_list = {};

        bool use_default_output = true;
        bool console_output = false;

        bool logfile_output = false;
        std::string logfile_name = "error_log";

        std::string logLevelToString(log_level level) {
            switch(level) {
                case log_level::message:
                return "Message";

                case log_level::warning:
                return "Warning";

                case log_level::fatal:
                return "Fatal";

                case log_level::debug:
                return "Debug";

                case log_level::verbose:
                return "Verbose";

                case log_level::exit_level:
                return "Exit";
            }
        }

        void setupDebug(bool def_out, bool con_out, bool log_out, std::string log_name) {
            use_default_output = def_out;
            console_output = con_out;
            logfile_output = log_out;
            logfile_name = log_name;

            std::ofstream file;
            file.open(logfile_name + ".hflog", std::ofstream::out | std::ofstream::trunc);
            file.close();
        }

        void defOutput(log message) {
            if(console_output) std::cout << "LEVEL: " << logLevelToString(message.level) << " DATA: " << message.message << " CODE: " << message.error << std::endl;
            if(logfile_output) {
                std::ofstream file;
                file.open(logfile_name + ".hflog", std::ofstream::out | std::ofstream::app);
                if(file.is_open()) {
                    file << "LEVEL: " << logLevelToString(message.level) << " DATA: " << message.message << " CODE: " << message.error << std::endl;
                    file.close();
                } else {
                    logfile_output = false;
                    addMessage({"Logfile couldn't be opened!", error_code::file_failed_to_load, log_level::warning});
                }
            }
        }

        void safeExit() {
            addMessage({"Safe Exit called! Exiting.", util::error_code::exit_error, util::log_level::exit_level});
            exit(1);
        }

        void addMessage(log message) {
            debug_list.push(message);
            if(use_default_output) {
                defOutput(message);
            }
        }

        log takeMessage() {
            log out = debug_list.front();
            debug_list.pop();
            return out;
        }

        bool messageRemaining() {
            return !debug_list.empty();
        }

        std::string stringPlusCString(std::string str, const char * c_str) {
            std::string temp = str;
            std::string conv = c_str;
            temp.append(conv);
            return temp;
        }
    }
}