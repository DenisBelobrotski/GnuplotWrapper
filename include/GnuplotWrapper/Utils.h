#pragma once


#include "Plot.h"


namespace plot
{
    void convertComponentsVectorsToPointsVector(
            std::vector<double> &xComponents, std::vector<double> &yComponents,
            std::vector<Point> &pointsVector) noexcept(false);

    void optimizeRangesBounds(plot::AxesRanges& axesRanges, std::vector<plot::Graph>& graphs);
}
