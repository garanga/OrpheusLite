/*
 * Part.hpp
 *
 *  Created on: Jan 17, 2017
 *      Author: pavel
 */

#ifndef PART_HPP_
#define PART_HPP_

#include <string>
#include <vector>

class  Material;
class  ElementType;
class Mesh;

namespace Symbol
{
    enum class ElementType;
};


class Part
{
public:

    Mesh* mesh;

     Part(std::string);
    ~Part();

    void
    setSizes(double*);

    void
    setDivisions(int*);

    void
    setMaterial(Material*);

    void
    setElementType(Symbol::ElementType, bool = false);


    //! A method for creating a mesh on part
    void
    createMesh(bool = true);


    void
    createMesh(ElementType*, bool = true);

    std::string
    getName() const;

    double*
    getSizes() const;

    int*
    getDivisions() const;

private:

    std::string  _name;
    Material*    _material;
    ElementType* _elementType;
    double*      _sizes;
    int*         _divisions;

};

#endif /* PART_HPP_ */
