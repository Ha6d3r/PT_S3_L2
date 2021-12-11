#include "train.h"

Train::Train() {
    destination = "None";
    id = 0;
    departure = 0;
}

Train::~Train() {
}

Train::Train(const Train & obj) {
    this->destination = obj.destination;
    this->id = obj.id;
    this->departure = obj.departure;
}

Train::Train(std::string destination, unsigned int id, unsigned int departure) {
    this->destination = destination;
    this->id = id;
    this->departure = departure;
}

void Train::set_departure(std::string dep) {
    departure = str_to_seconds(dep);
}

void Train::set_destination(std::string dest) {
    destination = dest;
}

void Train::set_id(unsigned int id) {
    this->id = id;
}

std::string Train::get_destination() {
    return destination;
}

unsigned int Train::get_departure() {
    return departure;
}

unsigned int Train::get_id() {
    return id;
}
