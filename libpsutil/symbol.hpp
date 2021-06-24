#pragma once
#include "system/memory.hpp"

namespace libpsutil
{
    template<typename T> class symbol
    {
    private:
        static int opd_table[10][2];
        static int opd_table_id;

    public:
        operator T* ()
        {
            if (opd_table_id > 9) { opd_table_id = 0; }

            opd_table[opd_table_id][0] = this->mp_object_;
            opd_table[opd_table_id][1] = memory::get_game_toc();

            T* type = *reinterpret_cast<T*>(this->mp_object_);
            return (decltype(type))opd_table[opd_table_id++];
        }

        T* get()
        {
            return this->mp_object_;
        }

        int mp_object_;
    };

    template <typename T> int symbol<T>::opd_table[10][2];
    template <typename T> int symbol<T>::opd_table_id;
}