/*
 * DisplacementConstraint.cpp
 *
 *  Created on: Jan 30, 2017
 *      Author: pavel
 */

#include "DisplacementConstraint.hpp"
#include "includes.hpp"

DisplacementConstraint::DisplacementConstraint(std::string myName             ,
                                             std::vector<int> myRegion        ,
                           Symbol::DisplacementConstraint myType,
                                             double* myValue                  )
    : Constraint(myName, myRegion, myType, myValue)
{

}

DisplacementConstraint::~DisplacementConstraint()
{

}
