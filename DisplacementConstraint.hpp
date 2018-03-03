/*
 * DisplacementConstraint.hpp
 *
 *  Created on: Jan 30, 2017
 *      Author: pavel
 */

#ifndef DISPLACEMENTCONSTRAINT_HPP_
#define DISPLACEMENTCONSTRAINT_HPP_

#include <string>
#include <vector>

#include "Constraint.hpp"

class DisplacementConstraint : public Constraint
{
public:
    DisplacementConstraint(std::string myName                                 ,
                           std::vector<int> myRegion                          ,
                           Symbol::DisplacementConstraint myType,
                           double* myValue                                   );
    virtual ~DisplacementConstraint();
};

#endif /* DISPLACEMENTCONSTRAINT_HPP_ */
