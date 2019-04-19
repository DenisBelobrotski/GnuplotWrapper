//
// Created by user on 2019-02-27.
//

#pragma once


#include "Plot.h"


namespace plot
{
    void convertComponentsVectorsToPointsVector(
            std::vector<double> &xComponents, std::vector<double> &yComponents,
            std::vector<Point> &pointsVector) noexcept(false);
}
