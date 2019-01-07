#ifndef TYPEDECIDER_H
#define TYPEDECIDER_H

class LSTM            {}; //specialization for LSTM
class dense           {}; //specialization for dense
class convolutional   {}; //specialization for conv
class BaseLayer_t     {}; //for allowing default to be base
template<class,class,class>
class BaseAggregator_t{}; //Base Type for aggregator types
template<class>
class BaseAF_t        {}; //Base Type for Activation Function
class ForwardingLayer {}; //specialization for perfect forwarding layer
class InputLayer      {}; //same as above
class Output          {}; //weights without nonlinearity
class Recurrent_t     {}; //holds functionality for LSTM, GRU, maybe RNN
class NonRecurrent_t  {}; //holds functionality for ~Recurrent

namespace ActivationType
{
    template<typename ReadFrom>
    class ReLU;
    template<typename ReadFrom>
    class L_ReLU;
    template<typename ReadFrom>
    class sigmoid;
    template<typename ReadFrom>
    class fastsig;
    template<typename ReadFrom>
    class softmax;
    template<typename ReadFrom>
    class tanh;
}

namespace op
{
    class LRD     {};
    class nesterov{};
    class Adam    {};
    class AdaGrad {};
    class RMSprop {};
    class dropout {};
    class L1      {};
    class L2      {};
}

#endif // TYPEDECIDER_H
