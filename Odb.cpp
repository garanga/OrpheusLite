//---------------------------------------------------------------------------
// Created on: 04.03.2017
// Author: Mikhail A. Volkov
// E-mail: Volkovmikhl@gmail.com
//---------------------------------------------------------------------------
#include "includes.hpp"

Odb::Odb()
{
    _dim                = -1;
    _nodesPerElement    = -1;
    _mesh               = nullptr;
    _nodes              = nullptr;
    _elements           = nullptr;
}

Odb::Odb(Mesh* mesh, int dim, int nodesPerElement)
{
    _dim               = dim;
    _nodesPerElement   = nodesPerElement;
    _mesh              = mesh;
    _nodes             = &(mesh->nodes);
    _elements          = &(mesh->elements);
}

Odb::~Odb()
{
    _mesh              = nullptr;
    _nodes             = nullptr;
    _elements          = nullptr;
}

std::map<std::string, std::vector<ODBFrame>>&
Odb::getFramesMap()
{
    return _framesMap;
}

void
Odb::setModelName(std::string name)
{
    _modelName = name;
}

void
Odb::setPartName(std::string name)
{
    _partName = name;
}

void
Odb::addFrame(std::string key, ODBFrame value)
{
    _framesMap[key].push_back(value);
}

void
Odb::addFrameVector(std::string key, std::vector<ODBFrame> value)
{
    _framesMap[key] = value;
}

bool Odb::saveToFile(std::ofstream& fout, std::string path)
{
    fout << (int)Symbol::FileCodes::MODELNAME;
    fout << "\n" << _modelName << std::endl;
    fout << (int)Symbol::FileCodes::PARTNAME;
    fout << "\n" << _partName  << std::endl;
    fout << (int)Symbol::FileCodes::DIMENSION;
    fout << "\n" << _dim << std::endl;
    fout << (int)Symbol::FileCodes::NODESPERELEMENT << "\n"
         << _nodesPerElement << std::endl;


    fout << (int)Symbol::FileCodes::NODES;
    fout << "\n" << _nodes->size() << "\n";
    double *tmp_coords;
    for (unsigned int i = 0; i < _nodes->size(); i++)
    {
        tmp_coords = _nodes->at(i)->getCoord();
        for (int j = 0; j < _dim; ++j)
            fout << tmp_coords[j] << " ";
        fout << std::endl;
    }
    tmp_coords = nullptr;

    fout << (int)Symbol::FileCodes::ELEMENTS;
    fout << "\n" << _elements->size() << "\n";
    int *tmp_connectivity;
    for (unsigned int i = 0; i < _elements->size(); i++)
    {
        tmp_connectivity = _elements->at(i)->getConnect();
        for (int j = 0; j < _nodesPerElement; ++j)
            fout << tmp_connectivity[j] << " ";
        fout << std::endl;
    }
    tmp_connectivity = nullptr;

    for (auto it = _framesMap.begin(); it != _framesMap.end(); ++it)
    {
        fout << (int)Symbol::FileCodes::STEP;
        fout << "\n" << it->first << std::endl;
        for (auto it_frame  = it->second.begin();
                  it_frame != it->second.end()  ; ++it_frame)
        {
            fout << (int)Symbol::FileCodes::FRAME << std::endl;
            it_frame->fileStreamWrite(fout, _dim);
        }
    }

    fout << (int)Symbol::FileCodes::ENDOFFILE;

    return true;
}
