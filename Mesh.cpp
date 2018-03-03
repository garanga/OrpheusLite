/*
 * Mesh.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: pavel
 */

#include "Mesh.hpp"

#include <iostream>

#include "Node.hpp"
#include "Element.hpp"
#include "ElementEdge.hpp"
#include "Part.hpp"

Mesh::Mesh()
{
    std::cout << "Meeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeesh" << std::endl;
}

Mesh::~Mesh()
{
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
        delete *it;
    for (auto it = elements.begin(); it != elements.end(); ++it)
        delete *it;
    for (auto it = elementEdges.begin(); it != elementEdges.end(); ++it)
        delete *it;

}

Mesh::Mesh(Part* myPart, ElementType* myType)
{


    int cnt;
    Node* node;
    double* coord;
    Element* element;
    int* connectivity;

    double* sizes = myPart->getSizes();
    int* divisions = myPart->getDivisions();

    if (divisions[0]>divisions[1])
    {
        cnt = 0;
        for (int i=0; i<divisions[0]+1; ++i)
        {
            for (int j=0; j<divisions[1]+1; ++j)
            {
                coord = new double[2];
                coord[0] = -sizes[0]/2.0+sizes[0]/divisions[0]*i;
                coord[1] = -sizes[1]/2.0+sizes[1]/divisions[1]*j;
                node = new Node(cnt, coord);
                nodes.push_back(node);

                ++cnt;
                delete node;
                delete coord;

            }
        }

        cnt = 0;
        for (int i=0; i<divisions[0]; ++i)
        {
            for (int j=0; j<divisions[1]; ++j)
            {
                connectivity = new int[4];
                connectivity[0] = (divisions[1]+1)*(i  )+j   +1;
                connectivity[1] = (divisions[1]+1)*(i+1)+j   +1;
                connectivity[2] = (divisions[1]+1)*(i+1)+j+1 +1;
                connectivity[3] = (divisions[1]+1)*(i  )+j+1 +1;
                element = new Element(cnt, connectivity, myType);
                elements.push_back(element);

                ++cnt;
                delete element;
                delete connectivity;

            }
        }
    }
    else
    {
        cnt = 0;
        for (int i=0; i<divisions[1]+1; ++i)
        {
            for (int j=0; j<divisions[0]+1; ++j)
            {
                coord = new double[2];
                coord[0] = -sizes[0]/2.0+sizes[0]/divisions[0]*j;
                coord[1] = -sizes[1]/2.0+sizes[1]/divisions[1]*i;
                node = new Node(cnt, coord);
                nodes.push_back(node);

                ++cnt;
            }
        }


        cnt = 0;
        for (int i=0; i<divisions[1]; ++i)
        {
            for (int j=0; j<divisions[0]; ++j)
            {
                connectivity = new int[4];
                connectivity[0] = (divisions[0]+1)*(i  )+j  ;
                connectivity[1] = (divisions[0]+1)*(i  )+j+1;
                connectivity[2] = (divisions[0]+1)*(i+1)+j+1;
                connectivity[3] = (divisions[0]+1)*(i+1)+j  ;
                element = new Element(cnt, connectivity, myType);
                elements.push_back(element);

                ++cnt;
//                delete element;
//                delete connectivity;

            }
        }
    }

    std::cout << "The mesh is created on part '" << myPart->getName() << "'" << std::endl;
    std::cout << "Number of nodes: \t" << nodes.size() << std::endl;
    std::cout << "Number of elements: \t" << elements.size() << std::endl;

}

