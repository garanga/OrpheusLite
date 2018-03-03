/*
 * Step.hpp
 *
 *  Created on: Feb 9, 2017
 *      Author: pavel
 */

#ifndef STEP_HPP_
#define STEP_HPP_

#include <string>
#include <vector>

namespace Symbol
{
    enum class Output;
}

class Step
{
public:

    Step(std::string);
    virtual ~Step();

    void
    addOutputRequest(Symbol::Output);

    void
    addOutputRequest(std::vector<Symbol::Output>);

    std::string
    getName() const;

    std::vector<Symbol::Output>
    getOutputRequest() const;

private:

    std::string _name;
    std::vector<Symbol::Output> _outputRequest;
};


#endif /* STEP_HPP_ */
