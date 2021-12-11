#ifndef TRAINCONTAINER_H
#define TRAINCONTAINER_H

#include <train.h>

class TrainContainer {
    public:
        TrainContainer();
        ~TrainContainer();
        TrainContainer(const TrainContainer & obj);

        void    add(Train obj);
        Train * get(unsigned int id);

        unsigned int get_size();

    private:

        void move(unsigned int pos);

        unsigned int size;
        Train ** container;
};

#endif // TRAINCONTAINER_H
