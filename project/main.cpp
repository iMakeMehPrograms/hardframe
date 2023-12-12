#include <hardframe/utility/utility.hpp>
#include <iostream>

int main(int argc, char *argv[]) {

    float test = 2.0f;
    std::cout << "Hello World! " << hf::util::implicit_cast<int>(test) << std::endl;
    
    return 0;
}