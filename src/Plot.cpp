//
// Created by Denis Belobrotski on 2019-02-26.
//

#include <sstream>
#include <cmath>

#include <GNUPlotWrapper/GNUPlotWrapper.h>


plot::Plot::Plot()
{
    pipe = nullptr;
    config = nullptr;
    graphs = nullptr;
}


plot::Plot::Plot(PlotConfig *config, std::vector<Graph> *graphs)
{
#ifdef WIN32
    pipe = _popen(GNUPLOT, "w");
#else
    pipe = popen(GNUPLOT, "w");
#endif
    this->config = config;
    this->graphs = graphs;
}


plot::Plot::~Plot()
{
    delete this->config;
    delete this->graphs;

#ifdef WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif
}


void plot::Plot::configPlot()
{
    std::string termMode;
    switch (config->outputType)
    {
        case PlotOutputTypeWindow:
#ifdef WIN32
            termMode = "wxt";
#else
            termMode = "qt";
#endif
            break;
        case PlotOutputTypeVectorSvg:
            termMode = "svg";
            break;
        case PlotOutputTypeRasterPng:
            termMode = "pngcairo";
            break;
        default:
            termMode = "qt";
    }
    fprintf(pipe, "set term %s size %d, %d\n", termMode.c_str(), config->windowWidth, config->windowHeight);
    if (!config->outputFilePath.empty())
    {
        fprintf(pipe, "set output \"%s\"\n", config->outputFilePath.c_str());
    }

    fprintf(pipe, "set title \"%s\"\n", config->title.c_str());
    fprintf(pipe, "set xlabel \"%s\"\n", config->xAxisName.c_str());
    fprintf(pipe, "set ylabel \"%s\"\n", config->yAxisName.c_str());
    if (config->legendFontSize > 0)
    {
        fprintf(pipe, "set key font \", %d\"\n", config->legendFontSize);
    }

    Range xAxisRange = config->axesRanges.xAxisRange;
    Range yAxisRange = config->axesRanges.yAxisRange;
    if (fabs(xAxisRange.end - xAxisRange.start) > 0)
    {
        fprintf(pipe, "set xrange [%lf:%lf]\n", xAxisRange.start, xAxisRange.end);
    }
    if (fabs(yAxisRange.end - yAxisRange.start) > 0)
    {
        fprintf(pipe, "set yrange [%lf:%lf]\n", yAxisRange.start, yAxisRange.end);
    }

    if (config->equalAxes)
    {
        fprintf(pipe, "set size ratio -1\n");
    }
}


void plot::Plot::makeGraphs() noexcept(false)
{
    if (pipe == nullptr)
    {
        throw PipeException("Gnuplot pipe was not opened");
    }
    if (this->graphs->empty())
    {
        throw VectorSizeException("Plot does not contain any graph");
    }

    configPlot();

    auto graphsNum = graphs->size();

    fprintf(pipe, "plot '-' with lines title '%s'", (*graphs)[0].title.c_str());
    for (auto i = 1; i < graphsNum; i++)
    {
        fprintf(pipe, ", '-' with lines title '%s'", (*graphs)[i].title.c_str());
    }
    fprintf(pipe, "\n");

    for (auto &currentGraph : *graphs)
    {
        for (auto &currentPoint : currentGraph.points)
        {
            fprintf(pipe, "%lf %lf\n", currentPoint.x, currentPoint.y);
        }

        fprintf(pipe, "e\n");
        fflush(pipe);
    }
}
