/*
 * Isotropic.cpp
 *
 *  Created on: Jan 17, 2017
 *      Author: pavel
 */

#include "Isotropic.hpp"

#include <iostream>
#include <string>


Isotropic::Isotropic(std::string name, double young, double poisson)
    : Material(name),
      _young(young), _poisson(poisson)
{
    std::cout << "An isotropic material is created" << std::endl;
    std::cout << "\t" << "Material name is " << name << std::endl;
}

Isotropic::~Isotropic()
{

}

double Isotropic::getYoung() const
{
    return _young;
}

double Isotropic::getPoisson() const
{
    return _poisson;
}
