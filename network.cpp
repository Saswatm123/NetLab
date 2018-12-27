#include "network.hpp"

#include "LayerHook.hpp"

#include <algorithm>
#include <chrono>

#include <iostream>

std::default_random_engine network::rng(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count() ) );

network::network(int num)
:head(new layer<InputLayer>(num) ),
active(head)
{
    CostMap = { {"RMS" , { {0, SubNetworkMath::RMS_cost }, {1, SubNetworkMath::d_RMS_cost  } } },
                {"XENT", { {0, SubNetworkMath::XENT_cost}, {1, SubNetworkMath::d_XENT_cost } } }
                };
}

void network::set_cost(std::string marker)
{
      CostFunc = CostMap[marker][0];
    d_CostFunc = CostMap[marker][1];
}

void network::set_cost(double (*fptr  )(const Eigen::VectorXd&),
                       double (*d_fptr)(const Eigen::VectorXd&) )
{
      CostFunc   = fptr;
    d_CostFunc = d_fptr;
}

network::~network()
{
    layer<>* iterator = head;

    layer<>* next = head->next;

    while(next != nullptr)
    {
        delete iterator;
        iterator = next;
        next = next->next;
    }
    delete iterator;
}

network::LayerHook::LayerHook()
{}
