#ifndef NETL_NETWORK_HPP
#define NETL_NETWORK_HPP

#include "inner_type_calc.tpp"
#include "UI_layernet.hpp" // just here for compilation testing, change this later

#include <iostream>

class network
{
public:

    template<typename LayerType>
    void clip(const LayerType&& add_to)
    {
        //replace with netalloc
        LayerType* newlayer = new LayerType(add_to);

        if(head == nullptr)
        {
            //temporarily problematic because DenseInput not base of MainLayerBase yet
            head   = newlayer;
            active = head;
        }
        else
        {
            active->next = newlayer;
            active->next->prev = active;
            active = newlayer;
        }
    }

    MainLayerBase* head = nullptr;
    MainLayerBase* tail = nullptr;

    MainLayerBase* active = head;

    ~network()
    {

    }

private:


};

#endif // NETL_NETWORK_HPP
