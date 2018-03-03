/*
 * Job.hpp
 *
 *  Created on: Jan 31, 2017
 *      Author: pavel
 */

#ifndef JOB_HPP_
#define JOB_HPP_

#include <string>
#include <map>

class Model;
class Odb;

class Job
{
public:

    Job(std::string, Model*);
   ~Job();

   std::string
   getName() const;

   Odb*
   getOdb() const;

   void
   saveOdb();

   void
   submit();

private:

    std::string                _name;
    Model*                     _model;
    Odb*                       _odb;
    std::map<std::string, Odb> _partODBs;
};


#endif /* JOB_HPP_ */
