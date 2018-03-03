#include "includes.hpp"

#include <ctime>

//#include "TestImportToVtp.h"

int main()
{

    /*
    std::cout << "To use a part with vtk one should do the following: \n"
              << "1. install vtk \n"
              << "   (the headers shold be in /usr/local/include/vtk-**)"
              << "    the shared libs in /usr/local/lib"
              << "2. add the headers path to Project -> Properties "
              << "3. add the following libs in Project -> Properties:"
              << "   vtkCommonCore-7.1"
              << "   vtkRenderingCore-7.1"
              << "   vtkCommonDataModel-7.1"
              << "   vtkCommonExecutionModel-7.1"
              << "   vtkIOXML-7.1"
              << "   vtkRenderingOpenGL2-7.1"
              << "   vtkInteractionStyle-7.1"
              << "Note, that my vtk version is 7.1"
              << "4. add LD_LIBRARY_PATH = /usr/local/lib to"
              << "   Project -> Properies -> Environment"
              <<std::endl;
     */


    std::string modelName    = "Model-1";
    std::string partName     = "Part-1";
    std::string materialName = "Material-1";
    std::string jobName      = "Job-1";


    Mdb* mdb = new Mdb;

    try
    {

        Model* model = mdb->createModel(modelName);

        // Create part
        Part* part = model->createPart(partName);

        double* sizes     = new double[2];
        sizes[0]     = 10.0; sizes[1]     = 10.0;
        part->setSizes(sizes);

        int*    divisions = new int[2];
        divisions[0] =  21; divisions[1] =  21;
        part->setDivisions(divisions);

        model->createIsotropic(materialName, 200.0e9, 0.25);
        model->setMaterialToPart(materialName, partName);

        part->setElementType(Symbol::ElementType::P4);
        part->createMesh();

        model->createStaticStep("Step-1", 0.0, 0.5, 0.1, 0.0, 0.5);
        StaticStep* step = model->getStatciStep("Step-1");

        // Set Output type
        step->addOutputRequest(Symbol::Output::U);

        std::vector<int> region;
        double *value;

        //---Constraint at node 1----------------------------------------------
        region.push_back(22 -1);

        value = new double[2];
        value[0] = 0.0;
        value[1] = 0.0;

        step->createDisplacementConstraint
            ("Constraint-1"                     ,
             region                             ,
             Symbol::DisplacementConstraint::UXY,
             value                               );

        region.clear();
        //---------------------------------------------------------------------

        //---Constraint at node 3----------------------------------------------
        region.push_back(22*22 - 1);

        value = new double[2];
        value[0] = 0.0;
        value[1] = 0.0;

        step->createDisplacementConstraint
            ("Constraint-2"                     ,
             region                             ,
             Symbol::DisplacementConstraint::UX ,
             value                              );

        region.clear();
        //---------------------------------------------------------------------

        //---Concentrated force at node 0--------------------------------------
        region.push_back(0*22);

        value = new double[2];
        value[0] =    0.0  ;
        value[1] = -200.0e6;

        step->createConcentratedLoad
            ("Load-1"                    ,
             region                      ,
             Symbol::ConcentratedLoad::FY,
             value                       );

        region.clear();
        //---------------------------------------------------------------------

        //---Concentrated force at node 2--------------------------------------
        region.push_back(21*22);

        value = new double[2];
        value[0] =    0.0  ;
        value[1] = +200.0e6;

        step->createConcentratedLoad
            ("Load-2"                    ,
             region                      ,
             Symbol::ConcentratedLoad::FY,
             value                       );

        region.clear();
        //---------------------------------------------------------------------

        // Create new step

        model->createStaticStep("Step-2", 0.5, 1.0, 0.1, 0.5, 1.0);
        step = model->getStatciStep("Step-2");

        // Copy loads and constraints from previous step
        step->copyConstraints(*(model->getStatciStep("Step-1")));
        step->copyLoads      (*(model->getStatciStep("Step-1")));

        // Set Output type
        step->addOutputRequest(Symbol::Output::U);

        mdb->createJob(jobName, model);

        time_t time1;
        time(&time1);

        mdb->getJob(jobName)->submit();
        mdb->getJob(jobName)->saveOdb();

        time_t time2;
        time(&time2);

        std::cout << time2-time1 << "s" << std::endl;

    }

    catch (OrpheusException::Exception& exception)
    {
        std::cout << "Exception occur \n";
        std::cout << exception.what() << std::endl;
    }

    delete mdb;

//    std::cout << "Finish" << std::endl;

    // Test vtk visualization and vtp export
//    importToVtp("Job_1-Output.txt");

    return 0;
}


