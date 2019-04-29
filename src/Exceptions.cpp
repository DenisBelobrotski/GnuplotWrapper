#include "GnuplotWrapper/Exceptions.h"


plot::PipeException::PipeException() : runtime_error("PipeException") {}

plot::PipeException::PipeException(const char *msg) : runtime_error(msg) {}

plot::VectorSizeException::VectorSizeException() : runtime_error("VectorSizeException") {}

plot::VectorSizeException::VectorSizeException(const char *msg) : runtime_error(msg) {}
