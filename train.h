#ifndef TRAIN_H
#define TRAIN_H

#include <string>
#include <timeandthings.h>

class Train {
    public:
        Train();
        Train(std::string destination, unsigned int id, unsigned int departure);
        ~Train();
        Train(const Train & obj);

        std::string  get_destination();
        void         set_destination(std::string dest);

        unsigned int get_id();
        void         set_id(unsigned int id);

        unsigned int get_departure();
        void         set_departure(std::string dep);

    private:
        std::string destination;
        unsigned int id;
        unsigned int departure;
};

#endif // TRAIN_H
