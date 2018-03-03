/*
 * Step.cpp
 *
 *  Created on: Feb 9, 2017
 *      Author: pavel
 */

#include "Step.hpp"

#include "includes.hpp"

#include <vector>

Step::Step(std::string name)
    : _name(name)
{
}

Step::~Step()
{
}

void
Step::addOutputRequest(Symbol::Output symbol)
{
    _outputRequest.push_back(symbol);
}

void
Step::addOutputRequest(std::vector<Symbol::Output> symbols)
{
    _outputRequest.insert(_outputRequest.end(), symbols.begin(), symbols.end());
}

std::string
Step::getName() const
{
    return _name;
}

std::vector<Symbol::Output>
Step::getOutputRequest() const
{
    return _outputRequest;
}


