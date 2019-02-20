#include <iostream>
#include <vector>

#include "network.hpp"
#include "inner_type_calc.tpp"
#include "mempool.hpp"

using namespace std;
/*
struct A
{
    int num;
    string name;

    A(int n, string s)
    {
        num = n;
        name = s;
    }
};*/

struct A
{
    static mempool netalloc;
};

mempool A::netalloc;

struct B
{
    int num;
};

template<typename T>
void read_addr(void* ptr)
{
    cout << "\n--------------------------------\n";
    int counter = 0;
    for(void* itr = ptr; itr != ptr+sizeof(T)*200; itr = itr + 1)
    {
        cout << endl << itr;
        if(counter%sizeof(T) == 0)
        {
            cout << "\tNum is " << static_cast<T*>(itr)->num;
        }
        counter++;
    }
    cout << "\n--------------------------------\n";
}

template<typename T>
void set_addr(void* const ptr)
{
    cout << "\nSETADDR";
    int counter = 0;

    for(void* itr = ptr; itr != ptr + sizeof(T)*200; itr += sizeof(T))
    {
        *static_cast<T*>(itr) = B{counter};
        counter++;
    }
}

struct tester
{
    int a;
    int b;
};

int main()
{
    /*
    void* ptr = A::netalloc.alloc<B>(200);

    read_addr<B>(ptr);
    set_addr<B>(ptr);
    read_addr<B>(ptr);

    void* ptr2 = A::netalloc.alloc<B>(200);

    read_addr<B>(ptr2 - sizeof(int)*200 );*/

    network model;

    //model.clip(layer<netl::DenseInput>(12) );

    model.clip(layer<netl::Dense>::ReLU(20) );

    model.clip(layer<netl::DenseOutput>::softmax(12) );

    model.clip(layer<netl::DenseOutput>::identity(10) );

    cout << "\nHello world!" << endl;
}

/*
    void* a = malloc(sizeof(A) * 3);

    A* ptr1 = new(a) A(1,"this is a name");

    A* ptr2 = new(a + sizeof(A) ) A(2, "This is the second name");

    A* ptr3 = new(a + 2*sizeof(A) ) A(3, "This is a third name");

    free(a);*/
