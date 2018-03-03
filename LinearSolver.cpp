/*
 * LinearSolver.cpp
 *
 *  Created on: Jan 27, 2017
 *      Author: pavel
 */

#include "LinearSolver.hpp"

#include "includes.hpp"

using namespace Eigen;

typedef Triplet<double> T;

LinearSolver::LinearSolver(Model* model, std::map<std::string, Odb>& odbMap)
    : _model(model), _partODBMap(odbMap)
{
}

LinearSolver::~LinearSolver()
{

}

void LinearSolver::solve()
{
    ////////////////
    // Input data //
    ////////////////

    // For now it is only one part exists
    Mesh* mesh     = _model->parts[0]->mesh;
    int   numNodes = _model->parts[0]->mesh->nodes.size();



    /////////////////////////////////////////////////////////////
    if (mesh == nullptr)                                       //
    {                                                          //
        std::string message("Part <");                         //
        message += _model->parts[0]->getName();                //
        message += "> not meshed";                             //
        throw except::Exception(Symbol::ExceptionType::NOMESH, //
                                message);                      //
    }                                                          //
    /////////////////////////////////////////////////////////////



    VectorXd u     = VectorXd::Zero(2*numNodes);
    VectorXd force = VectorXd::Zero(2*numNodes);

    // Create ODB and set-up for current part
    Odb odb(mesh,2,4);

    odb.setModelName(_model->getName());
    odb.setPartName (_model->parts[0]->getName());



    //////////////////////////////////////////////////////////////
    if (_model->steps.size() == 0)                              //
    {                                                           //
        throw except::Exception(Symbol::ExceptionType::NOSTEPS, //
                                "No steps initialized");        //
    }                                                           //
    //////////////////////////////////////////////////////////////



    // Initializing the first step
    auto step = (_model->steps).begin();


    ///////////////////////////////////////////////////////////////
    checkLoads      ((*step)->loads      , (*step)->getName());  //
    checkConstraints((*step)->constraints, (*step)->getName());  //
    ///////////////////////////////////////////////////////////////


    std::cout << "//////////////////////////////////////////////////" << "\n";
    std::cout << "// The step " << (*step)->getName() << " is initialized";
    std::cout << "\n" << "//////////////////////////////////////////////////";
    std::cout << std::endl;

    double timeStart       = (*step)->timeStart;      // Starting time
    double timeEnd         = (*step)->timeEnd;        // Ending time
    double timeIncrement   = (*step)->timeIncrement;  // Time increment
    double loadFactorStart = (*step)->loadFactorStart;// Starting load factor
    double loadFactorEnd   = (*step)->loadFactorEnd;  // Ending load factor

    double stepTime        = timeEnd-timeStart;       // Time interval for the load step

    std::cout << "Starting time: "        << timeStart       << std::endl;
    std::cout << "Ending time: "          << timeEnd         << std::endl;
    std::cout << "Time increment: "       << timeIncrement   << std::endl;
    std::cout << "Starting load factor: " << loadFactorStart << std::endl;
    std::cout << "Ending load factor: "   << loadFactorEnd   << std::endl;

    double time = timeStart;  // Current time

    /////////////////////////
    // Load increment loop //
    /////////////////////////

    int flag10 = 1; // Open the door to the load increment loop

    while (flag10 == 1) // Correct type conversion or expression
    {
        flag10 = 0; // Close the door to the load increment loop

        time += timeIncrement;  // Increase time

        if ((time-timeEnd)>1.0e-10) /* Using chosen time increment we are jump over the ending time of the load step */
        {
            if ((timeIncrement-(time-timeEnd))>1.0e-10)    /* variant1: on the previous iteration we were far from the ending time */
            {
                timeIncrement -= time-timeEnd;            // Choosing correct time increment
                time = timeEnd;                            //
            }
            else                                        /* variant2: on the previous iteration we are near with the ending time */
            {
                ++step;                                    // Progressing to the next load step



                if (step==(_model->steps).end())        /* The previous load step was last load step */
                {
                    flag10 = 0;                            // Close the door to the load increment loop                                                    ??????? It is already closed
                    break;                                // Leave the bisection loop. Since the door to the load increment loop is closed this will lead to ending of the load loop also
                }
                else                                                    // Next load step
                {
                    checkLoads((*step)->loads, (*step)->getName());
                    checkConstraints((*step)->constraints, (*step)->getName());

                    std::cout << "//////////////////////////////////////////////////" << std::endl;
                    std::cout << "// The step " << (*step)->getName() << " is initialized" << std::endl;
                    std::cout << "//////////////////////////////////////////////////" << std::endl;

                    time -= timeIncrement;

                    timeStart = (*step)->timeStart; // Update starting time
                    timeEnd   = (*step)->timeEnd;   // Update ending time
                    stepTime  = timeEnd-timeStart;  // Update time interval for the load step

                    timeIncrement   = (*step)->timeIncrement; // Update time increment

                    loadFactorStart = (*step)->loadFactorStart; // Update starting load factor
                    loadFactorEnd   = (*step)->loadFactorEnd;   // Update ending load factor

                    time += timeIncrement;                            // Current time
                }
            }
        }

        // Load factor and (displacements variation) factor
        static double loadIncrement   = (time-timeStart)/stepTime;
        static double loadFactorRange = loadFactorEnd-loadFactorStart;

        loadIncrement *= loadFactorRange;

        static double loadFactor = loadFactorStart + loadIncrement;
        static double dispFactor = timeIncrement/stepTime*loadFactorRange;

        std::cout << "load factor: " << loadFactor << std::endl;
        std::cout << "displacements variation factor: "<< dispFactor<<std::endl;

        VectorXd du = VectorXd::Zero(2*numNodes);

        // Initialize global stiffness K and residual vector F
        SparseMatrix<double> globK(2*numNodes,2*numNodes);
        globK = calcGlobK();

        VectorXd force = VectorXd::Zero(2*numNodes);
        updateForce(u, force);

        // Apply prescribed loads
        applyLoads((*step)->loads, force, loadFactor);
        // Apply prescribed constraints
        applyConstraints((*step)->constraints, globK, force, dispFactor);

        SparseLU<SparseMatrix<double>> linearEquationsSolver(globK);
        VectorXd sol = linearEquationsSolver.solve(force);

        du = sol;
        u += du;

        // Filling output database
        fillOutput(odb, u, *step);

        flag10=1;
    }

}

void LinearSolver::applyLoads(std::vector<Load*>& loads     ,
                                  VectorXd&       force     ,
                            const double&         loadFactor)
{
    // Apply prescribed loads
    for (auto it = loads.begin(); it < loads.end(); ++it)
    {
        std::vector<int>    indices;
        std::vector<double> values;
        if (static_cast<int>((*it)->type) &
            static_cast<int>(Symbol::ConcentratedLoad::FX))
        {
            std::vector<int>& region = ((*it)->region);
            for (unsigned i=0; i < region.size(); ++i)
            {
                region[i] *= 2;
                region[i] += 0;
            }
            indices.insert(indices.end(),region.begin(),region.end());

            std::vector<double> value(region.size(),((*it)->value[0])*loadFactor);
            values.insert(values.end(),value.begin(),value.end());
        }

        if (static_cast<int>((*it)->type) &
            static_cast<int>(Symbol::ConcentratedLoad::FY))
        {
            std::vector<int> region = ((*it)->region);
            for (unsigned i=0; i<region.size(); ++i)
            {
                region[i] *= 2;
                region[i] += 1;
            }
            indices.insert(indices.end(),region.begin(),region.end());

            std::vector<double> value(region.size(),((*it)->value[1])*loadFactor);
            values.insert(values.end(),value.begin(),value.end());
        }

        for (unsigned int k = 0; k < force.size(); ++k)
        {
            for (unsigned int i = 0; i < indices.size(); ++i)
            {
                if (k == indices[i])
                    force(k) += values[i];
            }
        }
    }
}

void LinearSolver::applyConstraints(std::vector<Constraint*>& constraints,
                                        SparseMatrix<double>& globK      ,
                                        VectorXd&             force      ,
                                                const double& dispFactor )
{
    for (auto constraint = constraints.begin();
              constraint < constraints.end()  ; ++constraint)
    {
        std::vector<int> indices;
        std::vector<double> values;

        if (static_cast<int>((*constraint)->type) &
            static_cast<int>(Symbol::DisplacementConstraint::UX))
        {
            std::vector<int> region = ((*constraint)->region);
            for (unsigned int i=0; i<region.size(); ++i)
            {
                region[i] *= 2;
                region[i] += 0;
            }
            indices.insert(indices.end(),region.begin(),region.end());
            std::vector<double> value(region.size(),((*constraint)->value[0])*dispFactor);
            values.insert(values.end(),value.begin(),value.end());
        }

        if (static_cast<int>((*constraint)->type) &
            static_cast<int>(Symbol::DisplacementConstraint::UY))
        {
            std::vector<int> region = ((*constraint)->region);
            for (unsigned int i=0; i<region.size(); ++i)
            {
                region[i] *= 2;
                region[i] += 1;
            }
            indices.insert(indices.end(),region.begin(),region.end());
            std::vector<double> value(region.size(),((*constraint)->value[1])*dispFactor);
            values.insert(values.end(),value.begin(),value.end());
        }

        for (unsigned k=0; k<globK.outerSize(); ++k)
        {
            for (Eigen::SparseMatrix<double>::InnerIterator it(globK,k); it; ++it)
            {
                for (unsigned i=0; i<indices.size(); ++i)
                {
                    if (it.row() == indices[i])
                        it.valueRef() = it.row() == it.col() ? _model->materials.back()->getYoung() : 0.0;
                }
            }
        }

        for (unsigned i=0; i<indices.size(); ++i)
        {
            force(indices[i]) = values[i]*_model->materials.back()->getYoung();
        }

    }
}

void LinearSolver::fillOutput(Odb&             currentODB ,
                              Eigen::VectorXd& disp       ,
                              Step*            currentStep)
{
    ODBFrame tmpFrame;

    const std::vector<Symbol::Output>& tmpVector =
                                               currentStep->getOutputRequest();


    for (auto it  = tmpVector.begin();
              it != tmpVector.end()  ; ++it)
    {
        static Symbol::Output currentSymbol = *it;

        switch (static_cast<int>(currentSymbol))
        {
        case static_cast<int>(Symbol::Output::U) :
        {
            std::vector<double> dataDispl;

            for (int i = 0; i < disp.size(); ++i)
                dataDispl.push_back(disp[i]);

            tmpFrame.getFieldOutput().data[currentSymbol] = dataDispl;
            break;
        }
        default:
        {
            throw except::Exception(Symbol::ExceptionType::NOOUTPUT,
                                    "Output not specified");
            break;
        }
        }
    }

    currentODB.addFrame(currentStep->getName(), tmpFrame);

    _partODBMap[_model->parts[0]->getName()] = currentODB;
}

SparseMatrix<double> LinearSolver::calcGlobK() const
{

    Mesh* mesh   = _model->parts[0]->mesh;
    int numNodes = mesh->nodes.size();

    std::cout.precision(2);
    std::cout.setf(std::ios::showpos);
    std::cout.setf(std::ios::scientific);

    std::vector<T> triplets;

    int*    connect;
    double* coord;
    int     nodesPerElement;
    Matrix<double,2,4> nodesCoordGlob;

    int k,l;

    Matrix<double,2,2> locK;

    if (mesh->elements.size() == 0)
    {
        throw except::Exception(Symbol::ExceptionType::EMPTYMESH,
                                "Mesh is empty");

    }

    for (auto it = (mesh->elements).begin(); it < (mesh->elements).end(); it++)
    {
        connect         = (*it)->getConnect();
        nodesPerElement = (*it)->getType()->getNodesNum();

        for (int i = 0; i < nodesPerElement; i++)
        {
            coord = (mesh->nodes)[connect[i]]->getCoord();
            nodesCoordGlob(0,i) = coord[0];
            nodesCoordGlob(1,i) = coord[1];
        }

        for (int i = 0; i < nodesPerElement; i++)
        {
            k = connect[i];
            for (int j = 0; j < nodesPerElement; j++)
            {
                l = connect[j];
                locK = (*it)->getType()->calcLocK(i, j, nodesCoordGlob);

                triplets.push_back(T(2*k  ,2*l  ,locK(0,0)));
                triplets.push_back(T(2*k  ,2*l+1,locK(0,1)));
                triplets.push_back(T(2*k+1,2*l  ,locK(1,0)));
                triplets.push_back(T(2*k+1,2*l+1,locK(1,1)));

            }
        }
    }

    SparseMatrix<double> globK(2*numNodes, 2*numNodes);

    globK.setFromTriplets(triplets.begin(), triplets.end());

    return globK;
}


void LinearSolver::updateForce(VectorXd &u, VectorXd &force) const
{
    Mesh* mesh = _model->parts[0]->mesh;

    for (auto it = (mesh->elements).begin(); it < (mesh->elements).end(); it++)
    {
        int* connect = (*it)->getConnect();

        Matrix<double,2,4> nodesCoordGlob;
        VectorXd uLoc(8);
        VectorXd forceLoc(8);
        for (int i=0; i<(*it)->getType()->getNodesNum(); i++)
        {
            double* coord = (mesh->nodes)[connect[i]]->getCoord();
            nodesCoordGlob(0,i) = coord[0];
            nodesCoordGlob(1,i) = coord[1];

            uLoc(2*i  ) = u(2*connect[i]  );
            uLoc(2*i+1) = u(2*connect[i]+1);

            forceLoc(2*i  ) = force(2*connect[i]  );
            forceLoc(2*i+1) = force(2*connect[i]+1);
        }

        (*it)->getType()->updateForce(nodesCoordGlob, uLoc, forceLoc);

        // Updating the global force
        for (int i=0; i<(*it)->getType()->getNodesNum(); i++)
        {
            force(2*connect[i]  ) = forceLoc(2*i  );
            force(2*connect[i]+1) = forceLoc(2*i+1);
        }

    }

}

void LinearSolver::update(VectorXd &u, MatrixXd &sigma, VectorXd &force) const
{
    Mesh* mesh = _model->parts[0]->mesh;

    for (auto it = (mesh->elements).begin(); it < (mesh->elements).end(); it++)
    {
        int* connect = (*it)->getConnect();

        Matrix<double,2,4> nodesCoordGlob;
        VectorXd uLoc(8);
        VectorXd forceLoc(8);
        for (int i=0; i<(*it)->getType()->getNodesNum(); i++)
        {
            double* coord = (mesh->nodes)[connect[i]]->getCoord();
            nodesCoordGlob(0,i) = coord[0];
            nodesCoordGlob(1,i) = coord[1];

            uLoc(2*i  ) = u(2*connect[i]  );
            uLoc(2*i+1) = u(2*connect[i]+1);

            forceLoc(2*i  ) = force(2*connect[i]  );
            forceLoc(2*i+1) = force(2*connect[i]+1);
        }

        Eigen::MatrixXd sigmaLoc(3,8);

        (*it)->getType()->update(nodesCoordGlob, uLoc, sigmaLoc, forceLoc);

        // Updating the global force
        for (int i=0; i<(*it)->getType()->getNodesNum(); i++)
        {
            force(2*connect[i]  ) = forceLoc(2*i  );
            force(2*connect[i]+1) = forceLoc(2*i+1);
        }

    }
}

void
LinearSolver::checkLoads(std::vector<Load*>& loads,
                         std::string         stepName)
{
    if (loads.size() == 0)
    {
        std::string message("Loads on step <");
        message += stepName;
        message += "> not specified";
        throw except::Exception(Symbol::ExceptionType::NOLOADS,
                                message);
    }
}

void
LinearSolver::checkConstraints(std::vector<Constraint*>& constraints,
                               std::string               stepName)
{
    if (constraints.size() == 0)
    {
        std::string message("Constraints on step <");
        message += stepName;
        message += "> not specified";
        throw except::Exception(Symbol::ExceptionType::NOCONSTRAINTS,
                                message);
    }
}
