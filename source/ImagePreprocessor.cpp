#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <pybind11/numpy.h>
#include "../headers/ImagePreprocessor.hpp"
#include "../headers/utils.hpp"
#include "../headers/Image.hpp"

namespace py = pybind11;


ImagePreprocessor::ImagePreprocessor(Image image) {
    cv::Mat imageGray, imageBlur;
    cv::cvtColor(image.get_matrix(), imageGray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(imageGray, imageBlur, cv::Size(15, 15), 0, 0);
    ImagePreprocessor::m_grayImage = Image(imageGray);
    ImagePreprocessor::m_blurredImage = Image(imageBlur);
}

Image ImagePreprocessor::get_gray_image() {
    return ImagePreprocessor::m_grayImage;
}

Image ImagePreprocessor::get_blurred_image() {
    return ImagePreprocessor::m_blurredImage;
}
