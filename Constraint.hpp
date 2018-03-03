/*
 * Constraint.hpp
 *
 *  Created on: Feb 1, 2017
 *      Author: pavel
 */

#ifndef CONSTRAINT_HPP_
#define CONSTRAINT_HPP_


#include <iostream>
#include <vector>

class Job;
namespace Symbol
{
    enum class DisplacementConstraint;
};

class Constraint
{
public:
    Constraint(std::string myName                                 ,
               std::vector<int> myRegion                          ,
               Symbol::DisplacementConstraint myType,
               double* myValue                                    );

    Constraint(const Constraint&);

    virtual ~Constraint();

    Symbol::DisplacementConstraint type;
    std::vector<int>                             region;
    double*                                      value; // Array

    friend class Job;

private:
    std::string mName;
};



#endif /* CONSTRAINT_HPP_ */
