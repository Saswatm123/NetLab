#ifndef LAYERMATH_H
#define LAYERMATH_H

#include "Eigen/Core"
#include "Eigen/Dense"

#include <iostream>
#include "TypeDecider.hpp"
#include <cmath>

class LayerMath
{
public:
    virtual double calculate(){};
    virtual ~LayerMath(){};
};

namespace SubLayerMath
{
    ///Class template for generating functors
    ///out of user defined functions
    class UserDefCalculation : public LayerMath
    {
    public:

        UserDefCalculation(double(*calculator_func)(double) )
        :calculate(calculator_func)
        {}

        double(*calculate)(double);
    };

    class SigmoidCalculation : public LayerMath
    {
    public:
        inline double calculate(double input)
        {
            return 1/(1+exp(-input));
        }
    };

    class d_SigmoidCalculation : public LayerMath
    {
    public:
        double calculate(double input)
        {

        }
    };

    class FastSigCalculation : public LayerMath
    {
    public:
        double calculate(double input)
        {

        }
    };

    class ReLUCalculation : public LayerMath
    {
    public:
        double calculate(double input)
        {

        }
    };

    class d_ReLUCalculation : public LayerMath
    {
    public:
        double calculate(double input)
        {

        }
    };

    class L_ReLUCalculation : public LayerMath
    {
    public:
        double calculate(double input)
        {

        }
    };

    class d_L_ReLUCalculation : public LayerMath
    {
    public:
        double calculate(double input)
        {

        }
    };

    class SoftmaxCalculation : public LayerMath
    {
    public:
        double calculate(double input)
        {

        }
    };

    class d_SoftmaxCalculation : public LayerMath
    {
    public:
        double calculate(double input)
        {

        }
    };

    class TanhCalculation : public LayerMath
    {
    public:
        double calculate(double input)
        {

        }
    };

    class d_TanhCalculation : public LayerMath
    {
    public:
        double calculate(double input)
        {

        }
    };
}

namespace SubNetworkMath
{
    double RMS_cost(const Eigen::VectorXd& output);

    double d_RMS_cost(const Eigen::VectorXd& output);

    double XENT_cost(const Eigen::VectorXd& output);

    double d_XENT_cost(const Eigen::VectorXd& output);

    double XENT_softmax_cost(const Eigen::VectorXd& output);

    double d_XENT_softmax_cost(const Eigen::VectorXd& output);
}

class PtrConvert
{
public:
    ///returns layer compatible functor out of user defined function
    static inline
    LayerMath* fun_to_LM( double(*fptr)(double) )
    {
        return new SubLayerMath::UserDefCalculation(fptr);
    }
};

#endif // LAYERMATH_H
