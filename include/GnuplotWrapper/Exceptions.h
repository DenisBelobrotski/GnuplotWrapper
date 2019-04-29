#pragma once


#include <stdexcept>


namespace plot
{

    class PipeException : public std::runtime_error
    {

    public:
        PipeException();

        explicit PipeException(const char *msg);

    };

    class VectorSizeException : public std::runtime_error
    {

    public:
        VectorSizeException();

        explicit VectorSizeException(const char *msg);

    };

}
