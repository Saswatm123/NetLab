#ifndef NETOPTIMIZER_H
#define NETOPTIMIZER_H

#include "inner_type_calc.tpp"

template<typename...OptimizerList>
class optimizer
{
public:
    template<typename T>
    bool contains(){return is_in<T, OptimizerList...>::value;};
};

#endif // NETOPTIMIZER_H
