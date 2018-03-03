/*
 * Element.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: pavel
 */

#include "Element.hpp"

#include "ElementLib/ElementType.hpp"

Element::Element()
    : _id(-1), _connectivity(nullptr), _type(nullptr)
{
}

Element::Element(int id, int* connectivity, ElementType* type)
    : _id(id), _connectivity(connectivity), _type(type)
{
}

Element::~Element()
{
    if (_connectivity != nullptr)
        delete [] _connectivity;
    /*
    if (_type != nullptr) Type deletes in Mesh
        delete _type;
    */
}

void
Element::setConnect(int* connectivity)
{
    if (_connectivity != nullptr)
        delete [] _connectivity;

    _connectivity = connectivity;
}

int
Element::getId() const
{
     return _id;
}

int*
Element::getConnect() const
{
     return _connectivity;
}

ElementType*
Element::getType() const
{
     return _type;
}
