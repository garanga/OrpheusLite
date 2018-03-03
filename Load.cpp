/*
 * Load.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: pavel
 */

#include "Load.hpp"

Load::Load(std::string                         myName  ,
        std::vector<int>                       myRegion,
        Symbol::ConcentratedLoad myType,
        double*                                myValue )
{
    mName  = myName;
    type   = myType;
    region = myRegion;
    value  = myValue;
}

Load::Load(const Load& load)
{
    mName  = load.mName;
    type   = load.type;
    region = std::vector<int>(load.region);

    value = new double[2];
    value[0] = load.value[0];
    value[1] = load.value[1];
}

Load::~Load()
{
    if (value != nullptr)
        delete [] value;
}


