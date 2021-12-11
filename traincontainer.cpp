#include "traincontainer.h"

bool char_smaller(std::string left, std::string right) {
    unsigned int len;
    bool if_end;
    if (left.length() < right.length()) {
        len = left.length();
        if_end = true;
    } else {
        len = right.length();
        if_end = false;
    }
    for (unsigned int i = 0; i < len; ++i) {
        if (left[i] < right[i]) {
            return true;
        }
    }
    return if_end;
}

TrainContainer::TrainContainer() {
    size = 0;
    container = static_cast<Train**>(malloc(1));
}

TrainContainer::~TrainContainer() {

    for (unsigned int i = 0; i < size; ++i) delete container[i];

    free(container);
}

void TrainContainer::move(unsigned int pos) {
    for (unsigned int i = size; i > pos; i--) {
        *container[i] = *container[i-1];
    }
}

void TrainContainer::add(Train obj) {
    container = static_cast<Train**>(realloc(container, (size+1) * sizeof(Train *)));
    container[size] = new Train;

    bool obj_added = true;

    for (unsigned int i = 0; i < size; ++i) {
        if (char_smaller(obj.get_destination(),container[i]->get_destination())) {
            move(i);
            *container[i] = obj;
            obj_added = false;
            break;
        }
    }
    if (obj_added) *container[size] = obj;

    size++;
}

Train * TrainContainer::get(unsigned int id) {
    return container[id];
}

unsigned int TrainContainer::get_size() {
    return size;
}
