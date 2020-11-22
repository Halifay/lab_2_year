#include <iostream>
#include <string>

namespace Hello
{
    std::string example_string = "Hello";
}

class A{
public:
    virtual void fun()=0;
};




int main() {
    using namespace Hello;
    std::cout << Hello::example_string << ", World!" << std::endl;
    std::cout << example_string << ", World!" << std::endl;

    std::string example_string = "Here I am!", second_string = "There we go!";
    example_string.length(); //example_string.size();
    example_string.capacity();

    example_string + second_string;
    return 0;
}
