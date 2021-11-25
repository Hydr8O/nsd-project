#include <opencv2/core/mat.hpp>
#include <pybind11/numpy.h>

namespace py = pybind11;

#pragma once
class ImagePreprocessor {
    public:
        ImagePreprocessor(std::string imagePath);
        py::array get_gray_image();
        cv::Mat get_blurred_image();
    private:
        cv::Mat m_grayImage;
        cv::Mat m_blurredImage;
};