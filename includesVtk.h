/*
 * includesVtk.h
 *
 *  Created on: Mar 28, 2017
 *      Author: pavel
 */

#ifndef INCLUDESVTK_H_
#define INCLUDESVTK_H_


#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

#include "vtkPoints.h"
#include "vtkQuad.h"
#include "vtkCellArray.h"
#include "vtkUnstructuredGrid.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"

#include "vtkXMLUnstructuredGridWriter.h"
#include "vtkXMLUnstructuredGridReader.h"

#include "vtkAlgorithm.h"

#include "vtkDoubleArray.h"
#include "vtkPointData.h"


#endif /* INCLUDESVTK_H_ */
