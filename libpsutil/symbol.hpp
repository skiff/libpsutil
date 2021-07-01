#pragma once
#include "system/memory.hpp"

namespace libpsutil
{
    namespace symbol_helper
    {
        void* get_symbol(unsigned int address);
    }

    template<typename T> class symbol
    {
    public:
        operator T* ()
        {
            T* type = *reinterpret_cast<T*>(this->mp_object_);
            return (decltype(type))symbol_helper::get_symbol(this->mp_object_);
        }

        T* get()
        {
            return this->mp_object_;
        }

        int mp_object_;
    };
}