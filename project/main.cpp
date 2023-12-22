#include <hardframe/graphics/opgl/base.hpp>
#include <hardframe/utility/general.hpp>
#include <iostream>

int main(int argc, char *argv[]) {

    hf::opgl::window win(100, 100, "Tester", true);
    win.close();
    return 0;
}