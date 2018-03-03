//---------------------------------------------------------------------------
// Created on: 04.03.2017.
// Author: Mikhail A. Volkov
// E-mail: Volkovmikhl@gmail.com
//---------------------------------------------------------------------------

#ifndef ODB_HPP_
#define ODB_HPP_

enum class FileCodes;

#include "ODBFrame.h"

#include <iostream>
#include <string>
#include <vector>

// Sample declaration--------------------------------------------------------
class Node;
class Element;
class Model;
class Mesh;

//---------------------------------------------------------------------------


class Odb
{
public:

     explicit
     Odb();
     explicit
     Odb(Mesh*, int, int);
    ~Odb();

    std::map<std::string, std::vector<ODBFrame>>&
    getFramesMap();

    void
    setModelName(std::string);

    void
    setPartName(std::string);

    void
    addFrameVector(std::string, std::vector<ODBFrame>);

    void
    addFrame(std::string, ODBFrame);

    bool
    saveToFile(std::ofstream&, std::string);

private:

    Mesh* _mesh;
    int _dim;
    int _nodesPerElement;

    std::vector<Node*>*    _nodes;     // Clears in Mesh class
    std::vector<Element*>* _elements;  //

    std::string _modelName;
    std::string _partName;

    std::map<std::string, std::vector<ODBFrame>> _framesMap;
};

#endif /* ODB_HPP_ */
