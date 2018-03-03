/*
 * ConcentratedLoad.hpp
 *
 *  Created on: Feb 3, 2017
 *      Author: pavel
 */

#ifndef CONCENTRATEDLOAD_HPP_
#define CONCENTRATEDLOAD_HPP_

#include <string>
#include <vector>

#include "Load.hpp"

class ConcentratedLoad : public Load
{

public:
    // Specialized constructor
    ConcentratedLoad(std::string myName                           ,
                     std::vector<int> myRegion                    ,
                     Symbol::ConcentratedLoad myType,
                     double* myValue                              );
    // Virtual destructor
    virtual ~ConcentratedLoad();

};


#endif /* CONCENTRATEDLOAD_HPP_ */
