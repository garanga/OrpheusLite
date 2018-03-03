/*
 * importToVtp.hpp
 *
 *  Created on: Mar 24, 2017
 *      Author: pavel
 */

#ifndef TESTIMPORTTOVTP_H_
#define TESTIMPORTTOVTP_H_


#include "includesVtk.h"

#include "SymbolicConstants.hpp"

#include <iostream>
#include <fstream>

void importToVtp(std::string path)
{

    std::ifstream fin;
    fin.open(path.c_str(), std::ios::in | std::ios::binary);

    int currentFileCode = -1;


    vtkSmartPointer<vtkPoints> points =
            vtkSmartPointer<vtkPoints>::New();

    vtkSmartPointer<vtkCellArray> cellArray =
            vtkSmartPointer<vtkCellArray>::New();

    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid =
            vtkSmartPointer<vtkUnstructuredGrid>::New();


    std::string modelName;
    std::string partName;
    int dimension;
    int nodesPerElement;

    int nodesNum;
    int elementsNum;

    std::string current_step;

    std::map<std::string, std::vector<ODBFrame>> frames_map;







    while (1)
    {
        fin >> currentFileCode;

        if (currentFileCode == (int)OrpheusConstants::FileCodes::ENDOFFILE)
            break;



        switch (currentFileCode)
        {

            case (int)OrpheusConstants::FileCodes::MODELNAME:
            {
                fin >> modelName;
                break;
            }

            case (int)OrpheusConstants::FileCodes::PARTNAME:
            {
                fin >> partName;
                break;
            }

            case (int)OrpheusConstants::FileCodes::DIMENSION :
            {
                fin >> dimension;
                break;
            }

            case (int)OrpheusConstants::FileCodes::NODESPERELEMENT :
            {
                fin >> nodesPerElement;
                break;
            }

            case (int)OrpheusConstants::FileCodes::NODES :
            {

                fin >> nodesNum;


                for (int i = 0; i < nodesNum; ++i)
                {
                    double* coord = new double[dimension];
                    for (int j = 0; j < dimension; ++j)
                    {
                        fin >> coord[j];
                    }
                    points->InsertNextPoint(coord[0], coord[1], 0.0);
                    coord = nullptr;
                }

                unstructuredGrid->SetPoints(points);

                break;
            }

            case (int)OrpheusConstants::FileCodes::ELEMENTS :
            {

                fin >> elementsNum;

                for (int i = 0; i < elementsNum; ++i)
                {
                    vtkSmartPointer<vtkQuad> quad =
                            vtkSmartPointer<vtkQuad>::New();

                    int* connectivity = new int[nodesPerElement];
                    for (int j = 0; j < nodesPerElement; ++j)
                    {
                        fin >> connectivity[j];
                    }

                    for (int j = 0; j < nodesPerElement; ++j)
                    {
                        quad->GetPointIds()->SetId(j,connectivity[j]);
                    }

                    connectivity = nullptr;

                    cellArray->InsertNextCell(quad);

                }

                unstructuredGrid->SetCells(VTK_QUAD, cellArray);

                break;

            }

            case (int)OrpheusConstants::FileCodes::STEP :
            {
                std::vector<ODBFrame> vector;

                fin >> current_step;
                frames_map[current_step] = vector;
                break;
            }

            case (int)OrpheusConstants::FileCodes::FRAME :
            {
                ODBFrame current_frame(fin, dimension, 4,
                                       nodesNum , elementsNum       );

                frames_map[current_step].push_back(current_frame);
                break;
            }

            default:
            {

                std::cout << "wrong code!" << std::endl;
                // Exception
                break;

            }

        }



    }

    fin.close();

    std::cout << "Number of points:" << unstructuredGrid->GetNumberOfPoints() << std::endl;
    std::cout << "Number of cells :" << unstructuredGrid->GetNumberOfCells() << std::endl;

    vtkSmartPointer<vtkDoubleArray> data =
            vtkSmartPointer<vtkDoubleArray>::New();
    data->SetNumberOfComponents(2);
    data->SetNumberOfTuples(unstructuredGrid->GetNumberOfPoints());

    int cnt = 0;
    for (int i = 0; i < unstructuredGrid->GetNumberOfPoints(); i+=2)
    {
//        std::cout << frames_map["Step-2"].back().getFieldOutput().data[OrpheusConstants::OutputSymbols::U][i  ] << "\t"
//                  << frames_map["Step-2"].back().getFieldOutput().data[OrpheusConstants::OutputSymbols::U][i+1] << "\t"
//                  << i << std::endl;

        double touple[2];
        touple[0] = frames_map["Step-2"].back().getFieldOutput().data[OrpheusConstants::OutputSymbols::U][i  ];
        touple[1] = frames_map["Step-2"].back().getFieldOutput().data[OrpheusConstants::OutputSymbols::U][i+1];
        data->SetTuple(cnt,touple);
        ++cnt;
    }

    data->SetName("U");

    unstructuredGrid->GetPointData()->AddArray(data);

    // Write file
    vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
            vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
    writer->SetFileName("test.vtu");
    writer->SetInputData(unstructuredGrid);
    writer->SetDataModeToAscii();
    writer->Write();

    // Read and display file for verification that it was written correclty
    vtkSmartPointer<vtkXMLUnstructuredGridReader> reader =
            vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
    reader->SetFileName("test.vtu");
    reader->Update();

    vtkSmartPointer<vtkDataSetMapper> mapper =
            vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkActor> actor =
            vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetRepresentationToWireframe();

    vtkSmartPointer<vtkRenderer> renderer =
            vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow =
            vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    renderWindow->SetSize(600,600);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderer->AddActor(actor);
    renderer->SetBackground(.3, .6, .3); // Background color green

    renderWindow->Render();
    renderWindowInteractor->Start();

}

/* Programable filter

scaleFactor = 1000

input  = self.GetInput ()
output = self.GetOutput()

pdo.ShallowCopy(pdi)

pointsNum = input.GetNumberOfPoints()
newPoints = vtk.vtkPoints()

for i in range(0, pointsNum):
    coord = pdi.GetPoint(i)
    x, y, z = coord[:3]
    dx = input.GetPointData().GetArray(0).GetValue(2*i  )
    dy = inptu.GetPointData().GetArray(0).GetValue(2*i+1)
    dz = 0
    x += scaleFactor*dx
    y += scaleFactor*dy
    z += scaleFactor*dz
    newPoints.InsertPoint(i, x, y, z)

pdo.SetPoints(newPoints)
/*
 */


#endif /* TESTIMPORTTOVTP_H_ */
