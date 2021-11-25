#include "../headers/utils.hpp"
#include <opencv2/core/mat.hpp>
#include <pybind11/numpy.h>

namespace py = pybind11;

py::array convertMatToPyArray(cv::Mat matrix) {
    cv::Mat flat = matrix.reshape(1, matrix.total()*matrix.channels());
    std::vector<uchar> vec = matrix.isContinuous() ? flat : flat.clone();
    return py::array(vec.size(), vec.data());
}
