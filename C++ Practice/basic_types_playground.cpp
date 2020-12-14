#include <iostream>

int main(int argc, char *argv[])
//argc -> num of args
//argv -> input argument
{
    auto f = 1.23f; // 32 bit num
    auto d = 1.23;  // 64 bit num

    //note a double is the default.

    //we can use size of to find the size of types
    std::cout << sizeof(double) << " " << sizeof(float) << std::endl;

    // Logic Control

    // this is a block
    {
        auto hi = "in block scope";
    }

    auto b = false;
    int i = 2;

    //if/else
    if (!b)
    {
        std::cout << "b is false" << std::endl;
    }
    else
    {
        std::cout << "b is true" << std::endl;
    }

    //switch case
    switch (i)
    {
    case 0:
        std::cout << i << std::endl;
        break;
    default:
        std::cout << "hello" << std::endl;
    }
}