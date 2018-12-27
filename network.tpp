#ifndef NETWORK_TPP
#define NETWORK_TPP

#include "inner_type_calc.tpp"
#include "NetOptimizer.hpp"
#include "layer.hpp"

#include <iostream>

///ONLY NONWORKING PART IS THIS DOESNT HAVE ACCESS TO LAYER.CPP
template<typename LayerType>
void network::clip(layer<LayerType>& attach)
{
    #ifdef TRACE
        std::cout << "\nClip Lvalue";
    #endif //TRACE

    layer<LayerType>* insert = new layer<LayerType>(attach);

    insert -> set_prev(active);

    active->next = insert;

    active = insert;

    tail = active;
}

template<typename LayerType>
void network::clip(layer<LayerType>&& attach)
{
    #ifdef TRACE
        std::cout << "\nClip Rvalue";
    #endif //TRACE

    clip(attach);
}

#endif // NETWORK_TPP
