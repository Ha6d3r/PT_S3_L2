#include <iostream>
#include <fstream>
#include <task2.h>

int main() {

    Task2 task;
    std::ifstream file("C:\\Users\\Ha6Ki\\Documents\\PT_S3_L2\\test.txt");
    std::cout << task.answer(file);

    return 0;
}
