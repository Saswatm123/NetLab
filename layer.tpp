#ifndef LAYER_TPP
#define LAYER_TPP

template<typename...OptimizerList>
void layer<dense, PARTIAL_BASE>::prime_routine(const std::size_t batch_size,
                                 optimizer<OptimizerList...> oplist)
{

}


/** ------------------ noexplicit::InheritSemiDense DEFINITIONS BELOW ------------------ **/

template<typename T>
noexplicit::InheritSemiDense<T>::InheritSemiDense(const LayerMath* ActivFunc, const LayerMath* d_LayerMath)
: activation_func(ActivFunc),
d_activation_func(d_LayerMath)
{}

template<typename T>
T noexplicit::InheritSemiDense<T>::sigmoid(std::size_t height)
{
    return T(height,
            new SubLayerMath::SigmoidCalculation  ,
            new SubLayerMath::d_SigmoidCalculation);
}

template<typename T>
T noexplicit::InheritSemiDense<T>::fastsig(std::size_t height)
{
    return T(height,
            new SubLayerMath::FastSigCalculation  ,
            new SubLayerMath::d_SigmoidCalculation);
}

template<typename T>
T noexplicit::InheritSemiDense<T>::softmax(std::size_t height)
{
    return layer<Output, PARTIAL_BASE>(height,
                     new SubLayerMath::SoftmaxCalculation  ,
                     new SubLayerMath::d_SoftmaxCalculation);
}

template<typename T>
T noexplicit::InheritSemiDense<T>::tanh(std::size_t height)
{
    return T(height,
            new SubLayerMath::TanhCalculation  ,
            new SubLayerMath::d_TanhCalculation);
}

template<typename T>
T noexplicit::InheritSemiDense<T>::ReLU(std::size_t height)
{
    return T(height,
            new SubLayerMath::ReLUCalculation  ,
            new SubLayerMath::d_ReLUCalculation);
}

template<typename T>
T noexplicit::InheritSemiDense<T>::L_ReLU(std::size_t height, double alpha)
{
    return T(height,
            new SubLayerMath::L_ReLUCalculation  ,
            new SubLayerMath::d_L_ReLUCalculation);
}

template<typename T>
noexplicit::InheritSemiDense<T>::~InheritSemiDense()
{}

#endif // LAYER_TPP
