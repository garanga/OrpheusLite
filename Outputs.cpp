//---------------------------------------------------------------------------
// Created on: 05.03.2017.
// Author: Mikhail A. Volkov
// E-mail: Volkovmikhl@gmail.com
//---------------------------------------------------------------------------

#include "Outputs.h"

//---Operator overloading for OutputSymbols-----------------------------------
inline bool operator < (Symbol::Output& lhv,
                        Symbol::Output& rhv)
{
    return (int)lhv < (int)rhv;
}

inline bool operator == (Symbol::Output& lhv,
                         Symbol::Output& rhv)
{
    return (int)lhv == (int)rhv;
}
//----------------------------------------------------------------------------
