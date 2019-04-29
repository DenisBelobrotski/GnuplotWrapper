#include "GnuplotWrapper/Utils.h"

#include <sstream>
#include <cmath>
#include <cfloat>

#include <GnuplotWrapper/Exceptions.h>


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


void plot::optimizeRangesBounds(plot::AxesRanges& axesRanges, std::vector<plot::Graph>& graphs)
{
    axesRanges.xAxisRange.end = DBL_MIN;
    axesRanges.yAxisRange.end = DBL_MIN;

    axesRanges.xAxisRange.start = DBL_MAX;
    axesRanges.yAxisRange.start = DBL_MAX;

    for (auto& currentGraph : graphs)
    {
        for (auto& currentPoint : currentGraph.points)
        {
            axesRanges.xAxisRange.end = std::max(axesRanges.xAxisRange.end, currentPoint.x);
            axesRanges.yAxisRange.end = std::max(axesRanges.yAxisRange.end, currentPoint.y);

            axesRanges.xAxisRange.start = std::min(axesRanges.xAxisRange.start, currentPoint.x);
            axesRanges.yAxisRange.start = std::min(axesRanges.yAxisRange.start, currentPoint.y);
        }
    }
}
