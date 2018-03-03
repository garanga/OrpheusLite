/*
 * ConcentratedLoad.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: pavel
 */

#include "ConcentratedLoad.hpp"

//#include "includes.hpp"

#include <iostream>

ConcentratedLoad::ConcentratedLoad(std::string myName         ,
                                   std::vector<int> myRegion  ,
                 Symbol::ConcentratedLoad myType,
                                   double* myValue            )
	: Load(myName, myRegion, myType, myValue)
{

}

ConcentratedLoad::~ConcentratedLoad()
{

}
