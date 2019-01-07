#ifndef NETWORK_H
#define NETWORK_H

#include "Eigen/Core"
#include "Eigen/Dense"
#include "TypeDecider.hpp"
#include "NetOptimizer.hpp"
#include "LayerMath.hpp"
#include "inner_type_calc.tpp"

#include <map>
#include <random>

template<typename LayerType     = BaseLayer_t,
         template<class> ActivFunc     = BaseAF_t,
         template<class> d_ActivFunc   = BaseAF_t,
         template<class,class,class>
         class AggregatorType   = BaseAggregator_t,
         typename UpdateRoutine = BaseLayer_t
         >
class layer;

class network
{
public:

    class network_impl_base
    {
        virtual ~network_impl_base(){}
    };

    template<typename...ArgPack>
    class network_impl : network_impl_base
    {
    public:
        network(int);

        ~network();

        VTH<ArgPack...> typelist;

        template<typename LayerType>
        inline void clip
        (layer<LayerType>&);

        template<typename LayerType>
        inline void clip
        (layer<LayerType>&&);

        //inp mat, op mat, batch size, optimizer
        template<typename...OptimizerList>
        void train(const Eigen::MatrixXd& input, const Eigen::MatrixXd& output,
                   std::size_t batch_size, std::size_t epochs,
                   optimizer<OptimizerList...> optim_list)
        {
            std::cout << "\nTraining started";
        }

        //Set cost function either by indicating by string or
        //passing in own cost/d_cost function

        inline void set_cost(std::string);

        inline void set_cost(double (*)(const Eigen::VectorXd&),
                             double (*)(const Eigen::VectorXd&) );

        class LayerHook
        {
        public:
            LayerHook();

        private:
            layer<>* hold;
        };

        LayerHook begin();

        LayerHook end();

        struct LRD
        {
            constexpr static double margin = .1;             //When below margin, LearningRate *= scale_LearningRate
            constexpr static double scale_margin = .75;      //When Learning Rate decreases, margin *= scale_margin
            constexpr static double scale_LearningRate = .85;//May add N-th order Learning Rate scaling
        };

        double LearningRate = .0005;
        double Beta1 = .9  ; //Adam First Order Estimation Coefficient
        double Beta2 = .999; //Adam Second Order Estimation Coefficient
        double mu = .9;      //Nesterov Momentum Attenuation Coefficient

        template<typename add_to_VTH>
        network<ArgPack..., add_to_VTH> add_layer(add_to_VTH obj)
        {

        }

    private:

        double (*CostFunc  )(const Eigen::VectorXd&);
        double (*d_CostFunc)(const Eigen::VectorXd&);

        //{"Cost Function Name"  : {0 : CF fptr, 1 : CF Derivative fptr} }
        std::map<std::string,
                 std::map<bool, double(*)(const Eigen::VectorXd&)>
                 > CostMap;

        layer<InputLayer>* const head;

        layer<>* tail;

        layer<>* active;

        static std::default_random_engine rng;
    };

    network_impl_base* model_impl;
};

#include "network.tpp"

#endif // NETWORK_H
