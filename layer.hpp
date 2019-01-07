#ifndef LAYER_H
#define LAYER_H

#include <vector>

#include "TypeDecider.hpp"
#include "Eigen/Core"
#include "Eigen/Dense"
#include "Eigen/StdVector"

#include "LayerMath.hpp"
#include "NetOptimizer.hpp"

#include <iostream>

/**
*   Split into class tree with least repetition,
*   BaseLayer, [Recurrent_t, NonRecurrent_t], [...]
**/

#define PARTIAL_BASE BaseLayer_t,BaseLayer_t,BaseAggregator_t,BaseLayer_t
#define FULLBASE     BaseLayer_t, PARTIAL_BASE

//default argument is BaseLayer_t, prev declared in network.hpp

template<typename, typename, typename, template<class, class, class> class, typename>
class layer
{
    friend class network;
protected:
    typedef Eigen::MatrixXd MatType;
    typedef Eigen::VectorXd VecType;
    typedef Eigen::aligned_allocator<MatType> MatAlloc;
    typedef Eigen::aligned_allocator<VecType> VecAlloc;

    layer<FULLBASE>* next = nullptr;
    layer<FULLBASE>* prev = nullptr;

    const std::size_t dimensionality;

    std::string name;

public:
    layer();

    virtual ~layer(){}
};

template<>
class layer<Recurrent_t, PARTIAL_BASE> : public layer<FULLBASE>
{};

template<>
class layer<NonRecurrent_t, PARTIAL_BASE> : public layer<FULLBASE>
{
public:
    friend class network;

    layer();

    inline layer<FULLBASE>* get_prev(){return prev;};

    inline void set_prev(layer<FULLBASE>* set){prev = set;};

protected:
    using layer<FULLBASE>::MatType;
    using layer<FULLBASE>::VecType;
    using layer<FULLBASE>::MatAlloc;
    using layer<FULLBASE>::VecAlloc;
};

class UI_type{}; //designation without implementation

//explicitly specialize R/S and R/ASYNC
template<>
class layer<LSTM, PARTIAL_BASE> : public layer<Recurrent_t, PARTIAL_BASE>, public UI_type
{};

template<>
class layer<convolutional, PARTIAL_BASE> : public layer<NonRecurrent_t, PARTIAL_BASE>, public UI_type
{};

template<>
class layer<ForwardingLayer, PARTIAL_BASE> : public layer<NonRecurrent_t, PARTIAL_BASE>, public UI_type
{};

template<>
class layer<InputLayer, PARTIAL_BASE> : public layer<NonRecurrent_t, PARTIAL_BASE>
{
public:
    layer(std::size_t);


private:
    using layer<NonRecurrent_t, PARTIAL_BASE>::VecType;

    VecType inp;
};

namespace noexplicit
{
    //parent class for all dense-style layers with weights + activation (no LSTM/Input/FWD type layers)
    template<typename FullLayerID, typename LayerType, typename ActivFuncType, typename d_ActivFuncType,
             template<class, class, class> class AggregatorType,
             class UpdateRoutine>
    class InheritSemiDense : public layer<NonRecurrent_t, PARTIAL_BASE>
    {
    protected:

        const LayerMath*   activation_func = nullptr;
        const LayerMath* d_activation_func = nullptr;

        typedef double(*per_unit_fptr)(double);

        using layer<NonRecurrent_t, PARTIAL_BASE>::MatType;
        using layer<NonRecurrent_t, PARTIAL_BASE>::VecType;
        using layer<NonRecurrent_t, PARTIAL_BASE>::MatAlloc;
        using layer<NonRecurrent_t, PARTIAL_BASE>::VecAlloc;

        MatType Weights;

        VecType gradient  ;
        VecType output    ;
        VecType activation;

        InheritSemiDense(const LayerMath*, const LayerMath*);



    public:

        /**
        *   Series of factory functions, each of which select an
        *   activation function for the layer, as well as the derivative
        **/

        static layer<LayerType,
        sigmoid(std::size_t);

        static IsLayerType
        fastsig(std::size_t);

        static IsLayerType
        softmax(std::size_t);

        static IsLayerType
        tanh(std::size_t);

        static IsLayerType
        ReLU(std::size_t);

        static IsLayerType
        L_ReLU(std::size_t, double);

        virtual ~InheritSemiDense();
    };
}

template<>
class layer<Output, PARTIAL_BASE> : public noexplicit::InheritSemiDense<layer<Output, PARTIAL_BASE> >, public UI_type
{

    //contains dirty fwd + back
    std::vector<void(*)()> update_routine;

    template<typename...OptimizerList>
    void prime_routine(const std::size_t,
                       optimizer<OptimizerList...>);

    layer(std::size_t, LayerMath*, LayerMath*);

public:

    ///DELETE THIS LATER
    layer(std::string);

    ///Turns custom user function into LayerMath-compliant functor and
    ///assigns to corresponding function.
    layer(std::size_t height, per_unit_fptr, per_unit_fptr);

    layer(const layer<Output, PARTIAL_BASE>&);

    ///DELETE THIS CONSTRUCTOR LATER, JUST PLACEHOLDER
    layer();

    ///DELETE THIS CONSTRUCTOR LATER, JUST PLACEHOLDER
    layer(int);

    ~layer();
};

template<>
class layer<dense, PARTIAL_BASE> : public noexplicit::InheritSemiDense<layer<dense, PARTIAL_BASE> >, public UI_type
{
private:

    //contains dirty fwd + back
    std::vector<void(*)()> update_routine;

    template<typename...OptimizerList>
    void prime_routine(const std::size_t,
                       optimizer<OptimizerList...>);

    layer(std::size_t, LayerMath*, LayerMath*);
public:

    layer(std::string);

    /**
    *   Series of factory functions, each of which select an
    *   activation function for the layer, as well as the derivative
    **/

    ///Turns custom user function into LayerMath-compliant functor and
    ///assigns to corresponding function.
    layer(std::size_t height, per_unit_fptr, per_unit_fptr);

    //copy constructor
    layer(const layer<dense, PARTIAL_BASE>&);

    ///DELETE THIS CONSTRUCTOR LATER, JUST PLACEHOLDER
    layer();

    ///DELETE THIS CONSTRUCTOR LATER, JUST PLACEHOLDER
    layer(int);

    ~layer();
};

#include "layer.tpp"

#endif // LAYER_H
