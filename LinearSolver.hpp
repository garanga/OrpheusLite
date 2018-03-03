/*
 * LinearSolver.hpp
 *
 *  Created on: Jan 27, 2017
 *      Author: pavel
 */

#ifndef LINEARSOLVER_HPP_
#define LINEARSOLVER_HPP_


#include <string>
#include <map>

#include "Eigen/Sparse"
#include "Eigen/Dense"

class Model;
class Step;
class Constraint;
class Load;
class Odb;

class LinearSolver
{
public:

     explicit
     LinearSolver(Model*, std::map<std::string, Odb>&);
    ~LinearSolver();

    void
    solve();

private:

    Model*                        _model;
    std::map<std::string, Odb>&   _partODBMap;

    void
    applyConstraints(std::vector<Constraint*>&   ,
                     Eigen::SparseMatrix<double>&,
                     Eigen::VectorXd&            ,
                     const double&               );

    void
    applyLoads(std::vector<Load*>&,
               Eigen::VectorXd&,
               const double&);

    void
    fillOutput(Odb&, Eigen::VectorXd&, Step*);

    void
    update(Eigen::VectorXd& u,
           Eigen::MatrixXd& sigma,
           Eigen::VectorXd& force) const;

    Eigen::SparseMatrix<double>
    calcGlobK() const;

    void
    updateForce(Eigen::VectorXd &u, Eigen::VectorXd &force) const;

    void
    checkLoads(std::vector<Load*>&, std::string);

    void
    checkConstraints(std::vector<Constraint*>&, std::string);

};


#endif /* LINEARSOLVER_HPP_ */
