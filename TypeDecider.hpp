#ifndef TYPEDECIDER_H
#define TYPEDECIDER_H

class LSTM            {}; //specialization for LSTM
class dense           {}; //specialization for dense
class convolutional   {}; //specialization for conv
class BaseLayer_t     {}; //for allowing default to be base
class ForwardingLayer {}; //specialization for perfect forwarding layer
class InputLayer      {}; //same as above
class Output          {}; //weights without nonlinearity
class Recurrent_t     {}; //holds functionality for LSTM, GRU, maybe RNN
class NonRecurrent_t  {}; //holds functionality for ~Recurrent

namespace ActivationType
{
    class ReLU;
    class L_ReLU;
    class sigmoid;
    class fastsig;
    class softmax;
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
