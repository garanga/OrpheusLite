//---------------------------------------------------------------------------
// Created on: 05.03.2017.
// Author: Mikhail A. Volkov
// E-mail: Volkovmikhl@gmail.com
//---------------------------------------------------------------------------

#ifndef OUTPUTS_H_
#define OUTPUTS_H_

#include <map>
#include <vector>

namespace Symbol
{
    enum class Output;
}

inline bool operator <  (Symbol::Output& ,
                         Symbol::Output&);

inline bool operator == (Symbol::Output& ,
                         Symbol::Output&);

class FieldOutput
{
public:
    explicit FieldOutput() {}
    ~FieldOutput() {}


    std::map<Symbol::Output, std::vector<double> > data;
};

class ScalarOutput
{
public:
    std::map<::Symbol::Output, std::vector<double> > data;

    explicit ScalarOutput() {}
    ~ScalarOutput() {}

};

#endif /* OUTPUTS_H_ */
