#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <pybind11/numpy.h>
#include <iostream>

#include "../headers/Image.hpp"
#include "../headers/utils.hpp"

namespace py = pybind11;

Image::Image(std::string imagePath) {
    Image::m_matrix = cv::imread(imagePath);
    Image::m_pyArray = convertMatToPyArray(m_matrix);
}

Image::Image() {}

Image::Image(cv::Mat matrix) {
    Image::m_matrix = matrix;
    Image::m_pyArray = convertMatToPyArray(matrix);
}

void Image::write(std::string filename) {
    cv::imwrite(filename, m_matrix);
}

cv::Mat Image::get_matrix() {
    return Image::m_matrix;
}

py::array Image::get_array() {
    return Image::m_pyArray;
}