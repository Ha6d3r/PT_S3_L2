#ifndef MENU_H
#define MENU_H

#include <task2.h>
#include <traincontainer.h>
#include <iostream>
#include <conio.h>

typedef struct search {

    bool valid;

    std::string name;
    bool use_name;

    bool use_range;

    int A;
    int B;

    bool eq_A;
    bool eq_B;

    bool less_A;
    bool less_B;

    bool greater_A;
    bool greater_B;

    //s_struct = {false,"",false,false,0,0,false,false,false,false,false,false};

} search;

class menu {
    public:
        menu();

        void show();

        search parse_search(std::string s);
        bool   search_to_bool(search s, int data = 0, std::string str = "");

    private:
        Task2 * task;
        TrainContainer * container;

        std::string names[5] = {
            "Display",
            "Add",
            "Get",
            "Task2",
            "Exit"
        };

        int names_count = 5;
};

#endif // MENU_H
