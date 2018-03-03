/*
 * ElementType.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: pavel
 */

#include "ElementType.hpp"

#include <string>

ElementType::ElementType()
{
    mDimension = 0;
    mNodesNum  = 0;
}

ElementType::~ElementType()
{

}

std::string ElementType::getName() const
{
    return mName;
}

int ElementType::getNodesNum() const
{
    return mNodesNum;
}
