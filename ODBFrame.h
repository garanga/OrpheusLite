//---------------------------------------------------------------------------
// Created on: 04.03.2017.
// Author: Mikhail A. Volkov
// E-mail: Volkovmikhl@gmail.com
//---------------------------------------------------------------------------

#ifndef ODBFRAME_H_
#define ODBFRAME_H_

#include "Outputs.h"

#include <iostream>
#include <fstream>
#include <string>

class ODBFrame
{
public:
    ODBFrame();
    ODBFrame(std::ifstream&, int, int, int, int);
   ~ODBFrame();

    void setFieldOutput(FieldOutput&);

    ScalarOutput& getScalarOutput();
    FieldOutput&  getFieldOutput();

    void printData(int);

    void fileStreamWrite(std::ofstream&, int);

private:
    ScalarOutput mScalars;
    FieldOutput  mFields;
};

#endif /* ODBFRAME_H_ */
