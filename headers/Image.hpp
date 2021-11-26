#include <opencv2/core/mat.hpp>
#include <pybind11/numpy.h>

namespace py = pybind11;

#pragma once
class Image {
    public:
        Image(std::string imagePath);
        Image(cv::Mat matrix);
        Image();
        cv::Mat get_matrix();
        py::array get_array();

    private:
        cv::Mat m_matrix;
        py::array m_pyArray;
};