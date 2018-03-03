/*
 * Node.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: pavel
 */

#ifndef NODE_CPP_
#define NODE_CPP_

#include "Node.hpp"

Node::Node()
    : _id(-1), _coord(nullptr)
{
}

Node::Node(int id, double* coord)
    : _id(id), _coord(coord)
{
}

Node::~Node()
{
    if (_coord != nullptr)
        delete [] _coord;
}

void
Node::setCoord(double* coord)
{
    if (_coord != nullptr)
        delete [] _coord;

    _coord = coord;
}

int
Node::getId() const
{
    return _id;
}

double*
Node::getCoord() const
{
    return _coord;
}

#endif /* NODE_CPP_ */
