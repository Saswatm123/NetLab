#include "layer.hpp"

//crash here means layer compiled correctly

/** ------------------ LAYER<> DEFINITIONS BELOW ------------------ **/

template<>
layer<BaseLayer_t, PARTIAL_BASE>::layer()
:dimensionality(3)
{}

/** ------------------ LAYER<NONRECURRENT_T> DEFINITIONS BELOW ------------------ **/

layer<NonRecurrent_t, PARTIAL_BASE>::layer()
{}

/** ------------------ LAYER<RECURRENT_T> DEFINITIONS BELOW ------------------ **/
/** ------------------ LAYER<INPUTLAYER> DEFINITIONS BELOW ------------------ **/

layer<InputLayer, PARTIAL_BASE>::layer(std::size_t)
{}

/** ------------------ LAYER<CONVOLUTIONAL> DEFINITIONS BELOW ------------------ **/


/** ------------------ LAYER<OUTPUT> DEFINITIONS BELOW ------------------ **/

layer<Output, PARTIAL_BASE>::layer(std::size_t height, LayerMath* functor_ptr, LayerMath* d_functor_ptr)
:noexplicit::InheritSemiDense<layer<Output, PARTIAL_BASE> >(functor_ptr, d_functor_ptr)
{}

layer<Output, PARTIAL_BASE>::layer(const layer<Output, PARTIAL_BASE>& copy_from)
:  noexplicit::InheritSemiDense<layer<Output, PARTIAL_BASE> >(
        (new std::remove_reference<decltype(*(copy_from.  activation_func))>::type (*(copy_from.  activation_func)) ),
        (new std::remove_reference<decltype(*(copy_from.d_activation_func))>::type (*(copy_from.d_activation_func)) ) )
{
    name = copy_from.name;
}

///Turns custom user function into LayerMath-compliant functor and
///assigns to corresponding function.
layer<Output, PARTIAL_BASE>::layer(std::size_t height, per_unit_fptr fptr, per_unit_fptr d_fptr)
:noexplicit::InheritSemiDense<layer<Output, PARTIAL_BASE> >(PtrConvert::fun_to_LM(fptr), PtrConvert::fun_to_LM(d_fptr) )
{}

layer<Output, PARTIAL_BASE>::~layer()
{
    if(activation_func != nullptr)
    {
        delete activation_func;
    }
    if(d_activation_func != nullptr)
    {
        delete d_activation_func;
    }
}

/** ------------------ LAYER<DENSE> DEFINITIONS BELOW ------------------ **/

layer<dense, PARTIAL_BASE>::layer(std::size_t height, LayerMath* functor_ptr, LayerMath* d_functor_ptr)
:noexplicit::InheritSemiDense<layer<dense, PARTIAL_BASE> >(functor_ptr, d_functor_ptr)
{}

///Turns custom user function into LayerMath-compliant functor and
///assigns to corresponding function.
layer<dense, PARTIAL_BASE>::layer(std::size_t height, per_unit_fptr fptr, per_unit_fptr d_fptr)
:noexplicit::InheritSemiDense<layer<dense, PARTIAL_BASE> >(PtrConvert::fun_to_LM(fptr), PtrConvert::fun_to_LM(d_fptr) )
{}

layer<dense, PARTIAL_BASE>::layer(const layer<dense, PARTIAL_BASE>& copy_from)
:noexplicit::InheritSemiDense<layer<dense, PARTIAL_BASE> >(
        (new std::remove_reference<decltype(*(copy_from.  activation_func))>::type (*(copy_from.  activation_func)) ),
        (new std::remove_reference<decltype(*(copy_from.d_activation_func))>::type (*(copy_from.d_activation_func)) ) )
{
    name = copy_from.name;
}

///DELETE THIS CONSTRUCTOR LATER, JUST PLACEHOLDER
layer<dense, PARTIAL_BASE>::layer()
:noexplicit::InheritSemiDense<layer<dense, PARTIAL_BASE> >(
    (new SubLayerMath::SigmoidCalculation),
    (new SubLayerMath::d_SigmoidCalculation) )
{}

///DELETE THIS CONSTRUCTOR LATER, JUST PLACEHOLDER
layer<dense, PARTIAL_BASE>::layer(int)
:noexplicit::InheritSemiDense<layer<dense, PARTIAL_BASE> >(
    (new SubLayerMath::SigmoidCalculation),
    (new SubLayerMath::d_SigmoidCalculation) )
{}

layer<dense, PARTIAL_BASE>::layer(std::string deletethis)
:noexplicit::InheritSemiDense<layer<dense, PARTIAL_BASE> >(
    (new SubLayerMath::SigmoidCalculation),
    (new SubLayerMath::d_SigmoidCalculation) )
{
    name = deletethis;
}

layer<dense, PARTIAL_BASE>::~layer()
{
    if(activation_func != nullptr)
    {
        delete activation_func;
    }
    if(d_activation_func != nullptr)
    {
        delete d_activation_func;
    }
}
