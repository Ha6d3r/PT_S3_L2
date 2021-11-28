#include "task2.h"
#include <iostream>

// this is even more useless
Task2::Task2() {
}

Task2::~Task2() {
}

Task2::Task2(const Task2 & obj) {
}

unsigned int Task2::answer(std::ifstream & input) {

    std::string word;
    unsigned int count = 0;

    for (std::string line; std::getline(input,line); ) {
        // this is uterly stupid
        std::stringstream string_stream(line);
        while (string_stream >> word) {
            if (word.length() < 5) count++;
        }
    }

    return count;
}
