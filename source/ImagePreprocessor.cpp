#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <pybind11/numpy.h>
#include "../headers/ImagePreprocessor.hpp"
#include "../headers/utils.hpp"

namespace py = pybind11;


ImagePreprocessor::ImagePreprocessor(std::string imagePath) {
    cv::Mat image = cv::imread(imagePath);
    cv::Mat imageGray, imageBlur;
    cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(imageGray, imageBlur, cv::Size(15, 15), 0, 0);
    ImagePreprocessor::m_grayImage = imageGray;
    ImagePreprocessor::m_blurredImage = imageBlur;
}

py::array ImagePreprocessor::get_gray_image() {
    return convertMatToPyArray(m_grayImage);
}

cv::Mat ImagePreprocessor::get_blurred_image() {
    return ImagePreprocessor::m_blurredImage;
}
