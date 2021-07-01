#include "symbol.hpp"

namespace libpsutil
{
    namespace symbol_helper
    {
        struct opd_s
        {
            unsigned int address;
            unsigned int toc;
        };

        std::vector<opd_s> symbol_table;
        void* get_symbol(unsigned int address)
        {
            for (auto i = 0; i < symbol_table.size(); i++)
            {
                opd_s* opd = &symbol_table[i];
                if (opd->address == address)
                    return opd;
            }

            symbol_table.push_back(opd_s());
            opd_s* opd = &symbol_table[symbol_table.size() - 1];
            opd->address = address;
            opd->toc = memory::get_game_toc();

            return opd;
        }
    }
}