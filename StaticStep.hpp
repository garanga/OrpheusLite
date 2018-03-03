/*
 * StaticStep.hpp
 *
 *  Created on: Jan 27, 2017
 *      Author: pavel
 */

#ifndef STATICSTEP_HPP_
#define STATICSTEP_HPP_

#include "Step.hpp"

#include <string>
#include <vector>

class Constraint;
class DisplacementConstraint;
class Load;
class ConcentratedLoad;

namespace Symbol
{
    enum class DisplacementConstraint;
    enum class ConcentratedLoad;
}

class StaticStep  : public Step
{
public:

    double timeStart;
    double timeEnd;
    double timeIncrement;
    double loadFactorStart;
    double loadFactorEnd;

    std::vector<Constraint*> constraints;
    std::vector<Load*>       loads;

    // Specialized constructor
    StaticStep(std::string, double, double, double, double, double);
    ~StaticStep();

    void
    copyConstraints(StaticStep&);

    void
    copyLoads(StaticStep&);

    // A method creating a DisplacementConstraint object
    DisplacementConstraint*
    createDisplacementConstraint(std::string                   ,
                                 std::vector<int>              ,
                                 Symbol::DisplacementConstraint,
                                 double*                       );

    // A method creating a ConcentratedLoad object
    ConcentratedLoad*
    createConcentratedLoad(std::string             ,
                           std::vector<int>        ,
                           Symbol::ConcentratedLoad,
                           double*                 );
};

#endif /* STATICSTEP_HPP_ */
