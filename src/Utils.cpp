//
// Created by user on 2019-02-27.
//

#include <sstream>

#include <GNUPlotWrapper/GNUPlotWrapper.h>


void plot::convertComponentsVectorsToPointsVector(
        std::vector<double> &xComponents, std::vector<double> &yComponents,
        std::vector<Point> &pointsVector) noexcept(false)
{
    auto xComponentsSize = xComponents.size();
    auto yComponentsSize = yComponents.size();

    if (xComponentsSize != yComponentsSize)
    {
        std::stringstream msgStream;
        msgStream << "Components vectors sizes isn't equal: x size: " << xComponentsSize
                  << ", y size: " << yComponentsSize;

        throw VectorSizeException(msgStream.str().c_str());
    }

    pointsVector.resize(xComponentsSize);

    for (auto i = 0; i < pointsVector.size(); i++)
    {
        pointsVector[i].x = xComponents[i];
        pointsVector[i].y = yComponents[i];
    }
}
