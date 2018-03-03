/*
 * Isotropic.hpp
 *
 *  Created on: Jan 17, 2017
 *      Author: pavel
 */

#ifndef ISOTROPIC_HPP_
#define ISOTROPIC_HPP_

#include "Material.hpp"

#include <string>

class Isotropic : public Material
{
public:

    Isotropic(std::string, double, double);
   ~Isotropic();

    double
    getYoung() const override;

    double
    getPoisson() const override;

private:

    double _young;
    double _poisson;
};

#endif /* ISOTROPIC_HPP_ */
