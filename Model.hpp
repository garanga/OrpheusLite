/*
 * Model.hpp
 *
 *  Created on: Jan 17, 2017
 *      Author: pavel
 */

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <string>
#include <vector>

class Body;
class Part;
class Material;
class ElementType;
class Mesh;
class StaticStep;

class Model
{
public:

    /*
    std::vector <Body*>       bodies;
    */
    std::vector <Part*>       parts;
    std::vector <Material*>   materials;
    std::vector <StaticStep*> steps;

    //! Specialized constructor
     Model(std::string);
    ~Model();

    /*
    //! A method for creating a Body object
    Body*
    createBody(std::string name);
    */

    //! A method for creating a Part object
    Part*
    createPart(std::string);

    //! A method for creating a Material object
    Material*
    createIsotropic(std::string, double, double);

    //! A method for creating a StaticStep object
    StaticStep*
    createStaticStep(std::string, double, double, double, double, double);

    void
    setMaterialToPart(std::string, std::string);

    std::string
    getName() const;

    /*
    Body*
    getBody(std::string);
    */

    Part*
    getPart(std::string);

    Material*
    getMatertial(std::string);

    StaticStep*
    getStatciStep(std::string);

private:

    std::string _name;

};

#endif /* MODEL_HPP_ */
