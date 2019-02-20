#ifndef UI_LAYERNET_HPP_NETL
#define UI_LAYERNET_HPP_NETL

#include "IMPL_layernet.hpp"
#include "UI_LayerType_options.hpp"
#include "AFpack_collection.hpp"

#include "Eigen/Core"
#include "Eigen/Dense"
#include "Eigen/StdVector"

template<typename LayerType>
class layer
{
public:

};

namespace UI_common_generators
{
    //template arg is the IMPL mapping of the requested UI version
    template< template< template<typename> class > class IMPL_LayerType >
    class UI_common_Dense_DenseOutput
    {
    public:
        static IMPL_LayerType<AF_pack::ReLU_IMPL>
        ReLU(std::size_t height)
        {
            return IMPL_LayerType<AF_pack::ReLU_IMPL>(height);
        }

        static IMPL_LayerType<AF_pack::L_ReLU_IMPL>
        L_ReLU(std::size_t height, double slope)
        {
            return IMPL_LayerType<AF_pack::L_ReLU_IMPL>(height, slope);
        }

        static IMPL_LayerType<AF_pack::tanh_IMPL>
        tanh(std::size_t height)
        {
            return IMPL_LayerType<AF_pack::tanh_IMPL>(height);
        }

        static IMPL_LayerType<AF_pack::sigmoid_IMPL>
        sigmoid(std::size_t height)
        {
            return IMPL_LayerType<AF_pack::sigmoid_IMPL>(height);
        }

        static IMPL_LayerType<AF_pack::softmax_IMPL>
        softmax(std::size_t height)
        {
            return IMPL_LayerType<AF_pack::softmax_IMPL>(height);
        }
    };
}

//constructors handled by UI_common_Dense_DenseOutput
template<>
class layer<netl::Dense> : public UI_common_generators::
                                    UI_common_Dense_DenseOutput<ROOT_IMPL_layernet
                                                                    ::IMPL_Dense>
{};


//constructors handled by UI_common_Dense_DenseOutput, only
//identity transformation provided
template<>
class layer<netl::DenseOutput> : public UI_common_generators::
                                            UI_common_Dense_DenseOutput<ROOT_IMPL_layernet
                                                                            ::IMPL_DenseOutput>
{
public:
    static ROOT_IMPL_layernet::IMPL_DenseOutput<AF_pack::identity_IMPL>
    identity(std::size_t height)
    {
        return ROOT_IMPL_layernet::IMPL_DenseOutput<AF_pack::identity_IMPL>(height);
    }
};

template<>
class layer<netl::DenseInput>
{
public:
    layer(std::size_t height)
    {

    }
};

#endif // UI_LAYERNET_HPP_NETL
