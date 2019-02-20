#ifndef AFPACK_COLLECTION_HPP_NETL
#define AFPACK_COLLECTION_HPP_NETL

#include "Eigen/StdVector"
#include "Eigen/Dense"
#include "Eigen/Core"

//AFpacks are template packs in the chance that some AFs require
//internal access to root, and to keep signatures consistent they are
//all templates with useless access denoted by void
namespace AF_pack
{
    typedef Eigen::MatrixXd MatType;
    typedef Eigen::VectorXd VecType;
    typedef Eigen::aligned_allocator<MatType> MatAlloc;
    typedef Eigen::aligned_allocator<VecType> VecAlloc;

    template<typename = void>
    struct ReLU_IMPL
    {
        template<typename T>
        ReLU_IMPL(T){}

        struct ReLU_FWDitr
        {
            inline double apply_AF(double elemwise)
            {
                return std::max(static_cast<double>(0),elemwise);
            }
        };

        struct ReLU_BWDitr
        {
            inline double get_d_AF(double elemwise)
            {
                return elemwise > 0;
            }
        };
    };

    template<typename = void>
    struct sigmoid_IMPL
    {
        template<typename T>
        sigmoid_IMPL(T){}

        struct sigmoid_FWDitr
        {

        };

        struct sigmoid_BWDitr
        {

        };
    };

    template<typename = void>
    struct L_ReLU_IMPL
    {
        double slope = 0;

        struct L_ReLU_FWDitr
        {

        };

        struct L_ReLU_BWDitr
        {

        };

        template<typename T>
        L_ReLU_IMPL(double slope_, T)
        :slope(slope_)
        {}

        L_ReLU_IMPL() = delete;
    };

    template<typename RootType>
    struct softmax_IMPL
    {
        softmax_IMPL(RootType* ptr)
        :rootptr(ptr)
        {}

        RootType* rootptr;

        struct softmax_FWDitr
        {

        };

        struct softmax_BWDitr
        {

        };
    };

    template<typename = void>
    struct tanh_IMPL
    {
        template<typename T>
        tanh_IMPL(T){}

        struct tanh_FWDitr
        {

        };

        struct tanh_BWDitr
        {

        };
    };

    template<typename = void>
    struct identity_IMPL
    {
        template<typename T>
        identity_IMPL(T){}

        struct identity_FWDitr
        {
            inline double apply_AF(double A)
            {
                return A;
            }
        };

        struct identity_BWDitr
        {
            inline double get_d_AF(double A)
            {
                return 1;
            }
        };
    };
}

#endif // AFPACK_COLLECTION_HPP_NETL
