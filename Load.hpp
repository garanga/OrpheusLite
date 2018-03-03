/*
 * Load.hpp
 *
 *  Created on: Feb 3, 2017
 *      Author: pavel
 */

#ifndef LOAD_HPP_
#define LOAD_HPP_

#include <iostream>
#include <vector>

class Job;
namespace Symbol
{
    enum class ConcentratedLoad;
}

class Load
{
public:
    Load(std::string                            myName  ,
         std::vector<int>                       myRegion,
         Symbol::ConcentratedLoad myType  ,
         double*                                myValue );
    Load(const Load&);
    virtual ~Load();


    std::vector<int>                       region;
    Symbol::ConcentratedLoad type;
    double*                                value; // Array
    friend class Job;

private:
    std::string mName;
};



#endif /* LOAD_HPP_ */
