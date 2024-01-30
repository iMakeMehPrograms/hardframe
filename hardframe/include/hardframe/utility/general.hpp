/*
    Copyright (c) 2023, iMakeMehThings 
    You may redistribute, use, and modify this code unde the terms of the BSD 3-Clause license.
    The license text should be available in the file named LICENSE, or found here:
    https://github.com/iMakeMehPrograms/hardframe/tree/main?tab=BSD-3-Clause-1-ov-file
*/

#define PI 3.141592f
#define TAU 6.283184f

#pragma once

namespace hf {
    namespace util {

        template<typename T> T implicit_cast(T target) {
            return target;
        }

    }
}