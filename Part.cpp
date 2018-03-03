/*
 * Part.cpp
 *
 *  Created on: Jan 17, 2017
 *      Author: pavel
 */

#include "Part.hpp"

#include "includes.hpp"

#include <iostream>
#include <fstream>

Part::Part(std::string name)
    : _name(name)
{

    std::cout << "A part is created" << std::endl;
    std::cout << "\t" << "Part name is " << name << std::endl;

    mesh         = nullptr;

    _material    = nullptr;
    _elementType = nullptr;
    _sizes       = nullptr;
    _divisions   = nullptr;

}

Part::~Part()
{
    if (mesh != nullptr)
        delete mesh;
    if (_elementType != nullptr)
        delete _elementType;
    if (_sizes != nullptr)
        delete [] _sizes;
    if (_divisions != nullptr)
        delete [] _divisions;
}

void
Part::setSizes(double* sizes)
{
    _sizes = sizes;
}

void
Part::setDivisions(int* divisions)
{
    _divisions = divisions;
}

void
Part::setMaterial(Material* material)
{
    _material = material;
}

void
Part::setElementType(Symbol::ElementType elementType,
                     bool isPlaneStrain)
{
    if (_material == nullptr)
    {
        // in includes.hpp it is written that
        // namespace except = OrpheusException;
        throw except::Exception(Symbol::ExceptionType::NOMATERIAL,
                                "No material specified");
    }

    switch(static_cast<int>(elementType))
    {
        case static_cast<int>(Symbol::ElementType::P4) :
        {
            _elementType = new P4(_material, isPlaneStrain);
            break;
        }
        default:
        {
            throw except::Exception(Symbol::ExceptionType::UNKNELEMTYPE,
                                    "Unknown element type");
            break;
        }
    }

}


void
Part::createMesh(bool writeMesh)
{
    createMesh(_elementType, writeMesh);
}


void
Part::createMesh(ElementType* type, bool writeMesh)
{
    mesh = new Mesh;

    if (_elementType == nullptr)
    {
        throw except::Exception(Symbol::ExceptionType::NOELEMTYPE,
                                "Element type not specified");
    }

    if (_sizes == nullptr)
    {
        std::string message("Sizes of part <");
        message += _name;
        message += "> doens't set!";
        throw except::Exception(Symbol::ExceptionType::NOSIZES,
                                message);
    }

    if (_divisions == nullptr)
    {
        std::string message("Divisions of part <");
        message += _name;
        message += "> doens't set!";
        throw except::Exception(Symbol::ExceptionType::NODIVISIONS,
                                message);
    }

    int cnt = 0;

    if (_divisions[0] > _divisions[1])
    {
        for (int i=0; i<_divisions[0]+1; ++i)
        {
            for (int j=0; j<_divisions[1]+1; ++j)
            {
                double* coord = new double[2];
                coord[0] = -_sizes[0]/2.0+_sizes[0]/_divisions[0]*i;
                coord[1] = -_sizes[1]/2.0+_sizes[1]/_divisions[1]*j;
                Node* node = new Node(cnt, coord);
                mesh->nodes.push_back(node);
                coord = nullptr;
                ++cnt;
            }
        }

        cnt = 0;
        for (int i=0; i<_divisions[0]; ++i)
        {
            for (int j=0; j<_divisions[1]; ++j)
            {
                int* connectivity = new int[4];
                connectivity[0] = (_divisions[1]+1)*(i  )+j  ;
                connectivity[1] = (_divisions[1]+1)*(i+1)+j  ;
                connectivity[2] = (_divisions[1]+1)*(i+1)+j+1;
                connectivity[3] = (_divisions[1]+1)*(i  )+j+1;
                Element* element = new Element(cnt, connectivity, type);
                mesh->elements.push_back(element);
                connectivity = nullptr;
                ++cnt;
            }
        }
    }
    else
    {
        for (int i=0; i<_divisions[1]+1; ++i)
        {
            for (int j=0; j<_divisions[0]+1; ++j)
            {
                double* coord = new double[2];
                coord[0] = -_sizes[0]/2.0+_sizes[0]/_divisions[0]*j;
                coord[1] = -_sizes[1]/2.0+_sizes[1]/_divisions[1]*i;
                Node* node = new Node(cnt, coord);
                mesh->nodes.push_back(node);
                coord = nullptr;
                ++cnt;
            }
        }

        cnt = 0;
        for (int i=0; i<_divisions[1]; ++i)
        {
            for (int j=0; j<_divisions[0]; ++j)
            {
                int* connectivity = new int[4];
                connectivity[0] = (_divisions[0]+1)*(i  )+j  ;
                connectivity[1] = (_divisions[0]+1)*(i  )+j+1;
                connectivity[2] = (_divisions[0]+1)*(i+1)+j+1;
                connectivity[3] = (_divisions[0]+1)*(i+1)+j  ;
                Element* element = new Element(cnt, connectivity, type);
                mesh->elements.push_back(element);
                connectivity = nullptr;
                ++cnt;
            }
        }
    }

    std::cout << "A mesh is created on part '" << _name << "'" << std::endl;
    std::cout << "\t" << "Number of nodes: \t" << mesh->nodes.size() << std::endl;
    std::cout << "\t" << "Number of elements: \t" << mesh->elements.size() <<std::endl;

    if (writeMesh)
    {
        std::ofstream ofile1("nodes");
        ofile1.precision(4);
        ofile1.setf(std::ios::scientific);
        ofile1.setf(std::ios::showpos);

        ofile1 << mesh->nodes.size() << std::endl;

        for (auto it = mesh->nodes.begin(); it < mesh->nodes.end(); it++)
        {
            double* coord = (*it)->getCoord();
            ofile1 << coord[0] << "\t" << coord[1] << std::endl;
        }

        ofile1.close();

        std::ofstream ofile2("elements");

        ofile2 << mesh->elements.size() << std::endl;

        for (auto it = mesh->elements.begin(); it < mesh->elements.end(); it++)
        {
            int* connect = (*it)->getConnect();
            ofile2 << connect[0] << "\t"
                   << connect[1] << "\t"
                   << connect[2] << "\t"
                   << connect[3] << std::endl;
        }

        ofile2.close();
    }
}

std::string
Part::getName() const
{
    return _name;
}

double*
Part::getSizes() const
{
    if (_sizes == nullptr)
    {
        std::string message("Sizes of part <");
        message += _name;
        message += "> doens't set!";
        throw except::Exception(Symbol::ExceptionType::NOSIZES,
                                message);
    }
    return _sizes;
}

int*
Part::getDivisions() const
{
    if (_divisions == nullptr)
    {
        std::string message("Divisions of part <");
        message += _name;
        message += "> doens't set!";
        throw except::Exception(Symbol::ExceptionType::NODIVISIONS,
                                message);
    }
    return _divisions;
}
