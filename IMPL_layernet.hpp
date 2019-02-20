#ifndef IMPL_LAYERNET_HPP_NETL
#define IMPL_LAYERNET_HPP_NETL

#include "Eigen/StdVector"
#include "Eigen/Dense"
#include "Eigen/Core"

#include "AFpack_collection.hpp"
#include "inner_type_calc.tpp"

class MainLayerBase
{
public:
    MainLayerBase* prev = nullptr;
    MainLayerBase* next = nullptr;
};

template<template<class> typename ActivationFunctionPackType, typename RootType>
class IMPL_common_Dense_DenseOutput : public ActivationFunctionPackType<RootType>,
                                      public MainLayerBase
{
protected:

    typedef Eigen::MatrixXd MatType;
    typedef Eigen::VectorXd VecType;
    typedef Eigen::aligned_allocator<MatType> MatAlloc;
    typedef Eigen::aligned_allocator<VecType> VecAlloc;

    IMPL_common_Dense_DenseOutput(std::size_t height, double AF_modifier, RootType* rootptr)
    :ActivationFunctionPackType<RootType>(AF_modifier, rootptr)
    {
        values.resize(height);
    }

    IMPL_common_Dense_DenseOutput(std::size_t height, RootType* rootptr)
    :ActivationFunctionPackType<RootType>(rootptr)
    {
        values.resize(height);
    }

    IMPL_common_Dense_DenseOutput() = delete;

    VecType values;
    MatType weights;
};

namespace ROOT_IMPL_layernet
{
    template<template<class> typename ActivationFunctionPackType>
    class IMPL_Dense : public IMPL_common_Dense_DenseOutput<ActivationFunctionPackType,
                                                            IMPL_Dense<ActivationFunctionPackType> >
    {
        typedef IMPL_common_Dense_DenseOutput<ActivationFunctionPackType,
                                              IMPL_Dense<ActivationFunctionPackType>
                                              > instruction_type;
        using instruction_type::MatType;
        using instruction_type::VecType;
        using instruction_type::MatAlloc;
        using instruction_type::VecAlloc;

    public:

        IMPL_Dense(std::size_t height)
        :instruction_type(height, this)
        {

        }

        IMPL_Dense(std::size_t height, double AF_modifier)
        :instruction_type(height, AF_modifier, this)
        {

        }

    private:

    };

    template<template<class> typename ActivationFunctionPackType>
    class IMPL_DenseOutput : public IMPL_common_Dense_DenseOutput<ActivationFunctionPackType,
                                                                  IMPL_DenseOutput<ActivationFunctionPackType> >
    {
        typedef IMPL_common_Dense_DenseOutput<ActivationFunctionPackType,
                                              IMPL_DenseOutput<ActivationFunctionPackType>
                                              > instruction_type;
        using instruction_type::MatType;
        using instruction_type::VecType;
        using instruction_type::MatAlloc;
        using instruction_type::VecAlloc;

    public:
        IMPL_DenseOutput(std::size_t height)
        :instruction_type(height, this)
        {

        }

        IMPL_DenseOutput(std::size_t height, double AF_modifier)
        :instruction_type(height, AF_modifier, this)
        {

        }
    };

    class IMPL_DenseInput : public MainLayerBase
    {
    public:

    };
}

#endif // IMPL_LAYERNET_HPP_NETL
