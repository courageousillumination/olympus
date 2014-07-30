#include <iostream>

#include "olympus.hpp"

void olympus::foo() {
    std::cout << "Hello world! Olympus " << OLYMPUS_VERSION_MAJOR << "." << OLYMPUS_VERSION_MINOR << std::endl;
}