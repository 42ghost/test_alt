#include <iostream>
#include <string>
#include "Comparator.h"

void lower(char* str){
    while (*str) {
        *str = std::tolower(*str);
        *str = *str;
        str++;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Not enougth args" << std::endl;
        exit(1);
    }
    lower(argv[1]); lower(argv[2]);
    std::cout << argv[1] << ' ' << argv[2];
    Comparator c(argv[1], argv[2]);
    c.compare();
    c.save();
}
