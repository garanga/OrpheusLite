/*
 * Material.hpp
 *
 *  Created on: Jan 17, 2017
 *      Author: pavel
 */

#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include <string>

class Material
{
public:

    Material(std::string);
    virtual
    ~Material();

    std::string
    getName() const;

    virtual double
    getYoung() const = 0;

    virtual double
    getPoisson() const = 0;

protected:
    std::string _name;
};

#endif /* MATERIAL_HPP_ */
