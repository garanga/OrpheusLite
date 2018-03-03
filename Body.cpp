/*
 * Body.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: pavel
 */

#include "Body.hpp"

#include "includes.hpp"

#include "triangle.h"
#include "algorithm"
#include <string>

Body::Body(std::string name)
    : mName(name)
{

}

Body::~Body()
{
    for (auto it = mLines.begin(); it != mLines.end(); ++it)
        delete *it;
    for (auto it = mPoints.begin(); it != mPoints.end(); ++it)
        delete *it;
}

void Body::addPoint(double x1, double x2)
{
    Point* point = new Point(x1, x2);
    mPoints.push_back(point);
}

void Body::addLine(int point1No, int point2No)
{
    Line* line = new Line(point1No, point2No);
    mLines.push_back(line);
}

void Body::setLineDivisions(int lineNo, int divisions)
{
    mLines[lineNo]->setDivisions(divisions);
}

std::string Body::getName() const
{
    return mName;
}

int Body::getLinesNum() const
{
    return mLines.size();
}

std::vector<Line*> Body::getLines() const
{
    return mLines;
}

