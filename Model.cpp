/*
 * Model.cpp
 *
 *  Created on: Jan 17, 2017
 *      Author: pavel
 */

#include "Model.hpp"

#include "includes.hpp"

#include <iostream>

Model::Model(std::string name)
    : _name(name)
{
    std::cout << "A model is created" << std::endl;
    std::cout << "\t" << "Model name is " << name << std::endl;
}

Model::~Model()
{
    /*
    for (auto it = bodies.begin(); it < bodies.end(); ++it)
        delete *it;
    */
    for (auto it = parts.begin(); it != parts.end(); ++it)
        delete *it;
    for (auto it = materials.begin(); it != materials.end(); ++it)
        delete *it;
    for (auto it = steps.begin(); it != steps.end(); ++it)
        delete *it;
}

/*
Body*
Model::createBody(std::string name)
{
    Body* body = new Body(name);
    bodies.push_back(body);
    return body;
}
*/

Part*
Model::createPart(std::string name)
{
    Part* part = new Part(name);
    parts.push_back(part);
    return part;
}

Material*
Model::createIsotropic(std::string name, double young, double poisson)
{
    Isotropic* material = new Isotropic(name, young, poisson);
    materials.push_back(material);
    return material;
}

StaticStep*
Model::createStaticStep(std::string name,
                        double timeBegin,
                        double timeEnd,
                        double timeIncrement,
                        double loadFactorBegin,
                        double loadFactorEnd)
{
    StaticStep* step = new StaticStep(name, timeBegin, timeEnd, timeIncrement, loadFactorBegin, loadFactorEnd);
    steps.push_back(step);
    return step;
}

void
Model::setMaterialToPart(std::string materialName, std::string partName)
{
    auto materialIt = std::find_if(materials.begin(),materials.end(),
                      [&materialName](Material* material)
                      {
                          return material->getName() == materialName;
                      });

    auto partIt = std::find_if(parts.begin(),parts.end(),
                  [&partName](Part* part)
                  {
                      return part->getName() == partName;
                  });

    bool materialFlag = materialIt == materials.end();
    bool partFlag =  partIt == parts.end();

    if (materialFlag)
    {
        std::string message("Material with name <");
        message += materialName;
        message += "> not found";
        // in includes.hpp it is written that
        // namespace except = OrpheusException;
        throw except::Exception(Symbol::ExceptionType::NOMATERIAL,
                                message);
    }

    if (partFlag)
    {
        std::string message("Part with name <");
        message += partName;
        message += "> not found";
        throw except::Exception(Symbol::ExceptionType::NOPART,
                                message);
    }

    (*partIt)->setMaterial((*materialIt));

    std::cout << materialName << " is set to " << partName << std::endl;

}

std::string
Model::getName() const
{
    return _name;
}

/*
Body*
Model::getBody(std::string name)
{
    auto it = std::find_if(bodies.begin(),bodies.end(),
              [&name](Body* body)
              {
                  return body->getName() == name;
              });
    return *it;
}
*/

Part*
Model::getPart(std::string name)
{
    auto it = std::find_if(parts.begin(),parts.end(),
              [&name](Part* part)
              {
                  return part->getName() == name;
              });
    return *it;
}

StaticStep*
Model::getStatciStep(std::string name)
{
    auto it = std::find_if(steps.begin(),steps.end(),
              [&name](StaticStep* step)
              {
                  return step->getName() == name;
              });
    return *it;
}
