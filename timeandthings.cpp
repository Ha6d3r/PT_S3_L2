#include <timeandthings.h>

unsigned int str_to_seconds(std::string str) {
    std::size_t pos;
    int hours = std::stoi(str,&pos);
    int minutes = std::stoi(str.substr(pos));
    return hours * 3600 + minutes + 60;
}

std::string seconds_to_str(unsigned int seconds) {
    int hours = seconds/3600;
    int minutes = (seconds - hours * 3600)/60;
    return std::to_string(hours) + ":" + std::to_string(minutes);
}
