/*
 * Job.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: pavel
 */
#include "Job.hpp"

#include "includes.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


Job::Job(std::string name, Model* model)
    : _name(name), _model(model)
{
    std::cout << "The job '" << name << "' is created" << std::endl;
    _odb = new Odb;
}


Job::~Job()
{
    delete _odb;
}

std::string
Job::getName() const
{
    return _name;
}

Odb*
Job::getOdb() const
{
    return _odb;
}

void
Job::saveOdb()
{
    std::ofstream fout;
    std::string path = _name + "-Output" + ".txt";

    fout.open(path.c_str(), std::ios::out | std::ios::binary);
    fout.setf(std::ios::scientific | std::ios::showpos);

    for (auto it = _partODBs.begin(); it != _partODBs.end(); ++it)
        it->second.saveToFile(fout, path);

    fout.close();
}

void
Job::submit()
{
    LinearSolver* solver = new LinearSolver(_model, _partODBs);

    solver->solve();
}

