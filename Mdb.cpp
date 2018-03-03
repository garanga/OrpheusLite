/*
 * Mdb.cpp
 *
 *  Created on: Jan 17, 2017
 *      Author: pavel
 */

#include "Mdb.hpp"

#include "includes.hpp"

#include <algorithm>
#include <iostream>

Mdb:: Mdb()
{
    std::cout << "An empty models database is created" << std::endl;
}

Mdb::~Mdb()
{
    for (auto it = _models.begin(); it < _models.end(); ++it)
        delete *it;
    for (auto it = _jobs.begin(); it < _jobs.end(); ++it)
        delete *it;
}

Model*
Mdb::getModel(int No) const
{
    return _models[No];
}

Model*
Mdb::getModel(std::string name) const
{
    auto it = std::find_if(_models.begin(),_models.end(),
              [&name](Model* model)
              {
                     return model->getName() == name;
              });
    return *it;
}

Job*
Mdb::getJob(int No) const
{
    return _jobs[No];
}

Job*
Mdb::getJob(std::string name) const
{
    auto it = std::find_if(_jobs.begin(),_jobs.end(),[name](Job* job)
              {
                     return job->getName() == name;
              });
    return *it;
}

Model*
Mdb::createModel(std::string name)
{
    Model* model = new Model(name);
    _models.push_back(model);
    return model;
}

Job*
Mdb::createJob(std::string name, Model* model)
{
    Job* job = new Job(name, model);
    _jobs.push_back(job);
    return job;
}



