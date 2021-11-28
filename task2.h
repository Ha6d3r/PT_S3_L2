#ifndef TASK2_H
#define TASK2_H

#include <fstream>
#include <sstream>
#include <string>

class Task2 {
    public:
        Task2();
        ~Task2();
        Task2(const Task2 & obj);

        unsigned int answer(std::ifstream & input);
};

#endif // TASK2_H
