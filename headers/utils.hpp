#include <opencv2/core/mat.hpp>
#include <pybind11/numpy.h>

namespace py = pybind11;

py::array convertMatToPyArray(cv::Mat);
