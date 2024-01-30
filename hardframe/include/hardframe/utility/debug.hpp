/*
    Copyright (c) 2023, iMakeMehThings 
    You may redistribute, use, and modify this code unde the terms of the BSD 3-Clause license.
    The license text should be available in the file named LICENSE, or found here:
    https://github.com/iMakeMehPrograms/hardframe/tree/main?tab=BSD-3-Clause-1-ov-file
*/

#include<string>
#include<iostream>
#include<queue>

#pragma once

namespace hf {
    namespace util {

        enum error_code {
            // General
            non_error = 0,
            searching = 1,
            eldritch = 2,

            // Memory
            null_pointer = 64,
            no_space = 65,

            // Graphics
            // OpenGL
            sdl_window_fail = 126,
            sdl_init_fail = 127,

            glew_init_fail = 128,

            gl_invalid_operation = 129,
            gl_invalid_enum = 130,
            gl_invalid_value = 131,
            gl_stack_overflow = 132,
            gl_stack_undeflow = 133,
            gl_out_of_memory = 134,
            gl_invalid_framebuffer_op = 135,
            gl_context_lost = 136,
            gl_table_too_large = 137,

            sdl_gl_context_null = 138,

            shader_compile_issue = 139,
            shaders_not_found = 140,
            shader_linking_issue = 141,

            model_not_found = 142,
            model_parse_error = 143,

            // Files & Parsing
            file_not_found = 192,
            token_unknown = 193,
            file_failed_to_load = 194,
            no_data_loaded = 195,
            file_length_zero = 196,

            dl_not_found = 197,
            dl_error = 198,
            symbol_not_found = 199,
            symbol_error = 200,
            dl_failed_to_load = 201

        };

        enum log_level {
            message = 0,
            warning = 1,
            fatal = 2,
            debug = 3,
            verbose = 4
        };

        struct log {
            std::string message;
            error_code error;
            log_level level;
        };

        // Do not directly use this, use the functions
        extern std::queue<log> debug_list;

        extern bool use_default_output;
        extern bool console_output;
        extern bool logfile_output;

        extern std::string logfile_name;

        void setupDebug(bool def_out, bool con_out, bool log_out, std::string log_name);
        std::string logLevelToString(log_level level);

        void addMessage(log message);
        void defOutput(log message);
        log takeMessage();

        std::string stringPlusCString(std::string str, const char * c_str);

        bool messageRemaining();
    }
}