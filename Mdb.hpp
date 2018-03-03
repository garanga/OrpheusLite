/*
 * Mdb.hpp
 *
 *  Created on: Jan 17, 2017
 *      Author: pavel
 */

#ifndef MDB_HPP_
#define MDB_HPP_

#include <string>
#include <vector>

class Model;
class Job;

class Mdb
{
public:

    Mdb();
   ~Mdb();

    Model*
    getModel(int) const;

    Model*
    getModel(std::string) const;

    Job*
    getJob(int) const;

    Job*
    getJob(std::string) const;

    Model*
    createModel(std::string);

    Job*
    createJob(std::string, Model*);

private:

    std::vector<Model*> _models;
    std::vector<Job*>   _jobs;

};

#endif /* MDB_HPP_ */
