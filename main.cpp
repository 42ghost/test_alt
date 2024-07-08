#include <iostream>
#include <string>
#include "Comparator.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Not enougth args" << std::endl;
        exit(1);
    }

    Comparator c(argv[1], argv[2]);
    c.compare();
    c.save();
}