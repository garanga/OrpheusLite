/*
 * Constraint.cpp
 *
 *  Created on: Feb 1, 2017
 *      Author: pavel
 */

#include "includes.hpp"

Constraint::Constraint(std::string myName                      ,
                       std::vector<int> myRegion               ,
                       Symbol::DisplacementConstraint myType,
                       double* myValue                         )
{
    mName  = myName;
    type   = myType;
    region = myRegion;
    value  = myValue;
}

Constraint::Constraint(const Constraint& constraint)
{
    mName  = constraint.mName;
    type   = constraint.type;
    region = std::vector<int>(constraint.region);

    value = new double[2];

    value[0] = constraint.value[0];
    value[1] = constraint.value[1];

}

Constraint::~Constraint()
{
    if (value != nullptr)
        delete [] value;
}

