#ifndef RAND_H
#define RAND_H
#include<random>
namespace
{
namespace PacmanRand
{
int rand(int beg, int end)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(beg, end);

    return dist6(rng);
}
int rand()
{
    return PacmanRand::rand(0, RAND_MAX);
}

};
};
#endif //RAND_H
