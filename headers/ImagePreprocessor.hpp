#include <opencv2/core/mat.hpp>
#include <pybind11/numpy.h>
#include "../headers/Image.hpp"

namespace py = pybind11;

#pragma once
class ImagePreprocessor {
    public:
        ImagePreprocessor(Image image);
        Image get_gray_image();
        Image get_blurred_image();
    private:
        Image m_grayImage;
        Image m_blurredImage;
};