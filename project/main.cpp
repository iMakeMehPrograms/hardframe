#include <hardframe/utility/utility.hpp>
#include <iostream>

int main(int argc, char *argv[]) {

    // Test the cast for a good non-lossy conversion
    int inte = 10;
    double doub = hf::util::implicit_cast<double>(inte);
    std::cout << "Integer: " << inte << " And as a double: " << doub << std::endl;
    // Test for a lossy one:
    doub = 10.1;
    inte = hf::util::implicit_cast<int>(doub);
    std::cout << "Integer: " << inte << " And as a double: " << doub << std::endl;
    
    return 0;
}