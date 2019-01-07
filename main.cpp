//#define VERBOSE
#include <iostream>

#define TRACE

#include "network.hpp"

#include <map>
#include <functional>
#include <windows.h>

#include "Eigen/Core"
#include "Eigen/Dense"
#include "Eigen/Sparse"
#include "Eigen/StdVector"

#include <chrono>

#include <algorithm>
#include <random>

using namespace std;

template<bool...rest_of_string>
class bitstring
{
protected:
    void print_this_handler()
    {
        cout << " END";
    }
};

template<bool A, bool... rest_of_string>
class bitstring<A, rest_of_string...> : public bitstring<rest_of_string...>
{
public:
    static const bool value = A;

    bitstring(){}

    template<typename is_a_bitstring>
    bitstring(is_a_bitstring assign_as_base)
    :bitstring<rest_of_string...>(assign_as_base)
    {}

    bitstring<!A, rest_of_string...> change_bit()
    {
        return bitstring<!A, rest_of_string...>();
    }

    bitstring<rest_of_string...> get_next()
    {
        return static_cast<bitstring<rest_of_string...> >(*this);
    }

    void print_this()
    {
        cout << "\nPrinting Bitstring with " << sizeof...(rest_of_string) << " bits: ";
        print_this_handler();
    }
protected:

    void print_this_handler()
    {
        cout << A;
        bitstring<rest_of_string...>::print_this_handler();
    }
};

long double math1()
{
    long double a = 0;
    for(int aa = 0; aa<10000000; aa++)
    {
        a+=1/200;
    }

    return a;
}

long double math2()
{
    long double a = 0;
    for(int aa = 0; aa<10000000; aa++)
    {
        a+=1;
    }

    a/=200;

    return a;
}

double measure_ratios()
{
    typedef chrono::high_resolution_clock clocktype;

    typedef clocktype::time_point timetype;

    timetype t1, t2, t3, t4;

    double duration;

    double duration2;

    double ratioholder = 0;

    int b = 0;

    for(int a = 100; a<200; a++)
    {
        b = a;

        t1 = clocktype::now();
            math1();
        t2 = clocktype::now();

        #ifdef DEBUG
        cout << "\nITERATION " << a << " process 1 completed";
        #endif // DEBUG

        t3 = clocktype::now();
            math2();
        t4 = clocktype::now();

        #ifdef DEBUG
        cout << "\nITERATION " << a << " process 2 completed";
        #endif // DEBUG

        duration  = (chrono::duration_cast<chrono::microseconds>(t4 - t3).count() );

        duration2 = (chrono::duration_cast<chrono::microseconds>(t2 - t1).count() );

        ratioholder += (duration/duration2)/100;

        #ifdef DEBUG
        cout << "\nA is " << a;
        #endif // DEBUG
    }

    return ratioholder;
}

void print_loading_bar()
{
    cout << "\nTraining Setup started:";
    Sleep(1000);
    cout << "\nSetup completed, 1.000s\nInitial Error: " << 99.4121;

    string border = string()+char(186)+char(186);

    for(int epochs = 1; epochs <= 10; epochs++)
    {
        cout << endl << "\nEpoch " << epochs << ": Training:\t" << border << string(45, '-') << border;
        cout << string(47,'\b');
        for(int a = 0; a<45; a++)
        {
            cout << char(219);
            Sleep(50);
        }

        cout << border << "\tError: " << rand()%100;
    }
}

class shuffler
{
public:

    typedef Eigen::VectorXd VecType;
    typedef Eigen::MatrixXd MatType;
    typedef Eigen::aligned_allocator<VecType> VecAlloc;
    typedef Eigen::aligned_allocator<MatType> MatAlloc;

    MatType inp;
    MatType op;
    int batch_size;
    int epochs;

    vector<unsigned> IDvec;

    shuffler(MatType _inp, MatType _op, int _batch_size, int _epochs)
    :inp(_inp), op(_op), batch_size(_batch_size), epochs(_epochs)
    {
        for(int a = 0; a<_inp.cols(); a++)
        {
            IDvec.push_back(a);
        }

        for(auto a : IDvec)
        {
            cout << endl << a;
        }
    }

    void say()
    {
        for(int E = 0; E<epochs; E++)
        {
            cout << "\nEpoch " << E;
            for(int batchnum = 0; batchnum < int(inp.cols()/batch_size); batchnum++)
            {
                cout << "\nBatch " << batchnum << "\n";
                for(int index = 0; index < batch_size; index++)
                {
                    cout << "XXXXXXX\n";
                    cout << inp_training_regime[E][batchnum][index] << "---" << endl;
                    cout << op_training_regime[E][batchnum][index];
                    cout << "\nXXXXXXX\n";
                }
            }
        }
    }

    void make_set()
    {
        shuffle(begin(IDvec), end(IDvec), rng);

        int number_of_batches = int(inp.cols()/batch_size);

        for(int E = 0; E<epochs; E++)
        {
            inp_training_regime.push_back(vector<vector<VecType, VecAlloc> >() );
             op_training_regime.push_back(vector<vector<VecType, VecAlloc> >() );
            for(int batchnum = 0; batchnum < number_of_batches; batchnum++)
            {
                inp_training_regime[E].push_back(vector<VecType, VecAlloc>() );
                 op_training_regime[E].push_back(vector<VecType, VecAlloc>() );

                for(int index = 0; index<batch_size; index++)
                {
                    inp_training_regime[E][batchnum].push_back(inp.col(IDvec[batchnum * batch_size + index] ) );
                     op_training_regime[E][batchnum].push_back( op.col(IDvec[batchnum * batch_size + index] ) );
                }
            }

            shuffle(begin(IDvec), end(IDvec), rng);
        }
    }

private:

    vector<vector<vector<VecType, VecAlloc> > > inp_training_regime;
    vector<vector<vector<VecType, VecAlloc> > > op_training_regime;

    static std::default_random_engine rng;
};

std::default_random_engine shuffler::rng(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count() ) );

template<typename... A>
struct VTH;

void do_func(void (*callback)() )
{
    callback();
}

class left_
{
public:
    vector<int> data;

    int bignum = 10;

    int& getbignum()
    {
        return bignum;
    }

    left_()
    {
        bignum = 5;
        data = {1,2,3,4,5};
    }

    ~left_()
    {
        cout << "\nLeft destro";
    }
};

template<typename bottomtype>
class right_
{
public:
    vector<int> data_derive;

    int* num;

    int highdigit;

    right_()
    {
        static_cast<bottomtype&>(*this).readID();
        highdigit = static_cast<bottomtype&>(*this).basedigit;
    }

    ~right_()
    {
        cout << "\nDEST: ";
    }
};

class bottom : public right_<bottom>
{
public:

    int basedigit = 5;

    void readID()
    {
        cout << "\nID is " << ID;
    }

    int ID;

    static int IDcount;

    bottom()
    {
        ID = IDcount++;
    }
};

int bottom::IDcount = 0;

int main()
{
    bottom obj;

    cout << "\nEND DIGIT is " << obj.highdigit;

    cout << "\n-----------";

    cout << obj.highdigit << " " << obj.basedigit;

    /*
    cout << endl << obj.bignum << " " << *obj.num;
    obj.getbignum() += 10;
    cout << endl << obj.bignum << " " << *obj.num;
    */
/*
    for(auto a : obj.data_derive)
    {
        cout << endl << a;
    }

    typedef Eigen::SparseMatrix<double> SpMat;

    layer<dense> input = layer<dense>("first");

    network model(3);

    model.clip(input);

    layer<dense> seclayer = layer<dense>("second");

    model.clip(seclayer);

    model.clip(layer<dense>("third") );

    typedef Eigen::MatrixXd MatType;
    typedef Eigen::VectorXd VecType;

    MatType inp(4,100), op(4,100);

    model.train(inp, op, 10, 10, optimizer<op::LRD, op::Adam, op::L2>() );

/*
    MatType A(2,10), B(2,10);

    A << 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20;
    B << A.reverse();

    cout << endl << A << endl << endl << B;

    shuffler obj(A, B, 2, 5);

    obj.make_set();

    obj.say();*/

    string word("This is the word");

    auto callback  = [&](){cout << "\nCALLBACK"  << word;};
    auto callback2 = [&](){cout << "\nCALLBACK2" << word;};
    auto callback3 = [&](){cout << "\nCALLBACK3" << word;};

    auto lambda_pass = [](void* arg)
    {
        (*static_cast<decltype(callback)*>(arg) )();
    };

    void (*f1)(void*) = lambda_pass;

    f1(&callback);
}
