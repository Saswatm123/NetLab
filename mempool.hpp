#ifndef MEMPOOL_NETL
#define MEMPOOL_NETL

#include "stddef.h"
#include "stdio.h"

class mempool
{
public:
    mempool()
    {
        max_buffersize = 32; //32 read cycles = 32*4 bytes
        begin = malloc(max_buffersize * 4);
    }

    //by default assumes only one object will be made space for
    template<typename T>
    void* alloc(std::size_t repetitions = 1)
    {
        std::size_t bytes = sizeof(T) * repetitions;

        std::size_t read_groups = ( (bytes%4 == 0) ? bytes/4 : bytes/4 + 1 );

        check_overfill(read_groups);

        current_buffer_used += read_groups;

        return static_cast<void*>(static_cast<char*>(begin)+(current_buffer_used - read_groups)*4);
    }

    static ptrdiff_t ptr_dist(void* lhs, void* rhs)
    {
        return ((char*)lhs-(char*)rhs);
    }

    ~mempool()
    {
        free(begin);
    }

    void* get_begin()
    {
        return begin;
    }

private:
    void check_overfill(std::size_t read_groups_requested)
    {
        if(current_buffer_used + read_groups_requested > max_buffersize)
        {
            expand();
            check_overfill(read_groups_requested);
        }
    }

    void expand()
    {
        void* new_begin = malloc(max_buffersize * 4 * 2);

        std::memmove(new_begin, begin, current_buffer_used * 4);

        free(begin);

        max_buffersize *= 2;

        begin = new_begin;
    }

    void* begin;

    std::size_t current_buffer_used = 0;
    std::size_t max_buffersize;
};

#endif // MEMPOOL_NETL
