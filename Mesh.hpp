/*
 * Mesh.hpp
 *
 *  Created on: Jan 18, 2017
 *      Author: pavel
 */

#ifndef MESH_HPP_
#define MESH_HPP_


#include <vector>

class Node;
class Part;
class Element;
class ElementType;
class ElementEdge;

class Mesh
{
public:
    std::vector <Node*>        nodes;
    std::vector <Element*>     elements;
    std::vector <ElementEdge*> elementEdges;

    Mesh();
    Mesh(Part* myPart, ElementType* myType);
    ~Mesh();
};


#endif /* MESH_HPP_ */
