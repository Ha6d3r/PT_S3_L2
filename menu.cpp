#include "menu.h"

menu::menu() {
    task = new Task2;
    container = new TrainContainer;
}

search menu::parse_search(std::string s) {
    unsigned int l = s.length();
    unsigned int pos;
    search s_struct;
    std::string range;
    bool one_is_invalid;
    std::size_t nextchar;

    s_struct = {false,"",false,false,0,0,false,false,false,false,false,false};

    for (unsigned int i = 0; i < l; ++i) {
        if (s[i] == 'n') {
            s_struct.use_name = true;
            s_struct.valid    = false;
            if (i != l-1) {
                if (s[i+1] == '\"') {
                    pos = 0;
                    for(unsigned int j = i+2; j < l; ++j) {
                        if (s[j] == '\"') {
                            pos = j;
                            break;
                        }
                    }

                    if (pos!=0 && pos-i > 2) {
                        s_struct.valid = true;
                        s_struct.name = s.substr(i+2,pos-i-2);
                        i = pos;
                    }
                }
            }
        }
        if (s[i] == 'r') {
            s_struct.use_range = true;
            s_struct.valid     = false;
            if (i != l-1) {

                if (s[i+1] == ']' || s[i+1] == '[' || s[i+1] == ')' || s[i+1] == '(') {
                    pos = 0;
                    for(unsigned int j = i+2; j < l; ++j) {
                        if (s[j] == ']' || s[j] == '[' || s[j] == ')' || s[j] == '(') {
                            pos = j;
                            break;
                        }
                    }

                    if (pos!=0 && pos-i > 4) {
                        range = s.substr(i+1,pos-i);


                        if (range[0] == ']') {
                            s_struct.less_A = true;
                            s_struct.eq_A   = true;
                        }
                        if (range[0] == '[') {
                            s_struct.greater_A = true;
                            s_struct.eq_A      = true;
                        }
                        if (range[0] == ')') {
                            s_struct.less_A = true;
                            s_struct.eq_A   = false;
                        }
                        if (range[0] == '(') {
                            s_struct.greater_A = true;
                            s_struct.eq_A      = false;
                        }

                        if (range[range.length()-1] == ']') {
                            s_struct.less_B = true;
                            s_struct.eq_B   = true;
                        }
                        if (range[range.length()-1] == '[') {
                            s_struct.greater_B = true;
                            s_struct.eq_B      = true;
                        }
                        if (range[range.length()-1] == ')') {
                            s_struct.less_B = true;
                            s_struct.eq_B   = false;
                        }
                        if (range[range.length()-1] == '(') {
                            s_struct.greater_B = true;
                            s_struct.eq_B      = false;
                        }

                        if (s_struct.eq_A || s_struct.eq_B || s_struct.greater_A || s_struct.less_A || s_struct.greater_B || s_struct.less_B) s_struct.valid = true;

                        one_is_invalid = true;
                        try {
                            s_struct.A = std::stoi(range.substr(1),&nextchar);
                            one_is_invalid = false;
                        } catch (std::invalid_argument) {
                            std::cout << "\033[31mInvalid argument\033[0m\n";
                        }

                        try {
                            s_struct.B = std::stoi(range.substr(nextchar+2));
                            one_is_invalid = false;
                        } catch (std::invalid_argument) {
                            one_is_invalid = true;
                            std::cout << "\033[31mInvalid argument\033[0m\n";
                        }

                        if (one_is_invalid) s_struct.valid = false;
                        i = pos;

                    }

                }

            }
        }
    }

    return s_struct;
}

bool menu::search_to_bool(search s, int data, std::string str) {
    return (s.name == str || !s.use_name) && (
            !s.use_range ||
            (   (data == s.A && s.eq_A) ||
                (data == s.B && s.eq_B) ||

                (data <  s.A && s.less_A) ||
                (data >  s.B && s.greater_B) ||
                (data > s.A && data < s.B && s.greater_A && s.less_B) ||
                (data >  s.A && s.greater_A && !s.less_B) ||
                (data <  s.B && s.less_B && !s.greater_A)
            )
    );
}

void menu::show() {
    int run = true;
    int pos = 0;

    std::string command;
    std::size_t next_char;
    int command_num;

    std::string dest;
    int id;
    int dep;

    std::string path;

    search search_params;


    while (run) {
        std::cout << save_pos;

        for (int i = 0; i < names_count; ++i) {
            if (i == pos)
                std::cout << "\033[30m\033[47m ";
            else
                std::cout << "\033[37m\033[40m ";

            std::cout << names[i] << " \033[0m   ";
        }

        switch (getch()) {
            case 77: {
                if (pos!=names_count-1) pos++;
                break;
            }
            case 75: {
                if (pos!=0) pos--;
                break;
            }
            case 72: {
                break;
            }
            case 80: {

                std::cout << "\033[2J\033[H";

                switch (pos) {
                    case 0: {

                        command_num = -1;
                        while (command_num == -1) {
                            std::cout << "\033[30m\033[47m TIME \033[0m (A for all or S for specific) -> ";
                            std::cin >> command;
                            if (command[0] != 'S' && command[0] != 'A') {
                                try {
                                    command_num = str_to_seconds(command);
                                }  catch (std::invalid_argument) {
                                    std::cout << "\033[31mInvalid argument\033[0m\n";
                                }
                            }

                            if (command[0] == 'A') command_num = 0;
                            if (command[0] == 'S') {
                                std::cout << "\n\033[30m\033[47m COMMAND \033[0m ";
                                std::cin >> command;

                                search_params = parse_search(command);
                                while(!search_params.valid) {
                                    std::cout << "\n\033[30m\033[47m COMMAND \033[0m ";
                                    std::cin >> command;
                                    search_params = parse_search(command);
                                }

                                command_num = -2;
                            }
                        }

                        unsigned int s = container->get_size();
                        Train * tmp;
                        if (s == 0) {
                            std::cout << "Empty";
                        } else {
                            id = 0;
                            for (unsigned int i = 0; i < s; ++i) {
                                tmp = container->get(i);

                                if (command_num > 0) {
                                    if (tmp->get_departure() < command_num) continue;
                                }
                                id++;

                                if (command_num < 0) {
                                    if (!search_to_bool(search_params, tmp->get_id(), tmp->get_destination())) continue;
                                }

                                std::cout << "---------------\n";
                                std::cout << tmp->get_destination() << '\n';
                                std::cout << tmp->get_id() << '\n';
                                std::cout << seconds_to_str(tmp->get_departure()) << '\n';
                                std::cout << "---------------" << std::endl;
                            }
                            if (id == 0) {
                                std::cout << "Empty";
                            }
                        }

                        while(getch() != 72);
                        break;
                    }

                    case 1: {

                        command = "";

                        std::cout << "\033[30m\033[47m DESTINATION \033[0m -> ";
                        std::cin >> command;

                        while (command.empty()) {
                            std::cout << "\033[30m\033[47m DESTINATION \033[0m -> ";
                            std::cin >> command;
                            std::cout << "\n";
                        }

                        dest = command;

                        command_num = -1;
                        while (command_num <= 0) {
                            std::cout << "\033[30m\033[47m ID \033[0m -> ";
                            std::cin >> command;
                            try {
                                command_num = std::stoi(command);
                            }  catch (std::invalid_argument) {
                                std::cout << "\033[31mInvalid argument\033[0m";
                            }
                        }

                        id = command_num;

                        command_num = -1;
                        while (command_num <= 0) {
                            std::cout << "\033[30m\033[47m DEPARTION \033[0m -> ";
                            std::cin >> command;
                            try {
                                command_num = str_to_seconds(command);
                            }  catch (std::invalid_argument) {
                                std::cout << "\033[31mInvalid argument\033[0m\n";
                            }
                        }

                        dep = command_num;

                        container->add(Train(dest,id,dep));

                        while(getch() != 72);
                        break;
                    }

                    case 2: {

                        command = "";

                        std::cout << "\033[30m\033[47m FILE PATH \033[0m (this directory or ABS with type) -> ";
                        std::cin >> command;

                        std::ifstream file(command);

                        while (!file.is_open()) {
                            std::cout << "\033[30m\033[47m FILE PATH \033[0m (this directory or ABS with type) -> ";
                            std::cin >> command;
                            file.open(command);
                        }

                        std::cout << task->answer(file) << std::endl;
                        file.close();

                        while(getch() != 72);
                        break;
                    }

                    case 3: {
                        run = false;
                        break;
                    }
                }

                std::cout << "\033[H\033[2J";

                break;
            }
        }

        std::cout << load_pos;
    }
}
