/*
 * StaticStep.cpp
 *
 *  Created on: Jan 27, 2017
 *      Author: pavel
 */

#include "StaticStep.hpp"

#include "includes.hpp"

#include <string>


StaticStep::StaticStep(std::string name,
                       double timeStart, double timeEnd, double timeIncrement,
                       double loadFactorStart, double loadFactorEnd)
    : Step(name),
      timeStart(timeStart), timeEnd(timeEnd), timeIncrement(timeIncrement),
      loadFactorStart(loadFactorStart), loadFactorEnd(loadFactorEnd)
{

}

StaticStep::~StaticStep()
{
    for (auto it = loads.begin(); it != loads.end(); ++it)
        delete *it;
    for (auto it = constraints.begin(); it != constraints.end(); ++it)
        delete *it;
}

void
StaticStep::copyConstraints(StaticStep& step)
{
    Constraint* tmp;
    for (auto it  = step.constraints.begin();
              it != step.constraints.end(); ++it)
    {
        tmp = new Constraint(*(*it));
        constraints.push_back(tmp);
    }
    tmp = nullptr;
}

void
StaticStep::copyLoads(StaticStep& step)
{
    Load* tmp;
    for (auto it  = step.loads.begin();
              it != step.loads.end(); ++it)
    {
        tmp = new Load(*(*it));
        loads.push_back(tmp);
    }
    tmp = nullptr;
}

DisplacementConstraint*
StaticStep::createDisplacementConstraint(std::string                    name  ,
                                         std::vector<int>               region,
                                         Symbol::DisplacementConstraint type  ,
                                         double*                        value )
{
    auto displacementConstraint = new DisplacementConstraint(name  ,
                                                             region,
                                                             type  ,
                                                             value );
    constraints.push_back(displacementConstraint);
    return displacementConstraint;
}

ConcentratedLoad*
StaticStep::createConcentratedLoad(std::string              name  ,
                                   std::vector<int>         region,
                                   Symbol::ConcentratedLoad type  ,
                                   double*                  value )
{
    auto concentratedLoad = new ConcentratedLoad(name  ,
                                                 region,
                                                 type  ,
                                                 value );
    loads.push_back(concentratedLoad);
    return concentratedLoad;
}
