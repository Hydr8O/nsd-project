#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

#include "../headers/ImagePreprocessor.hpp"

ImagePreprocessor::ImagePreprocessor(cv::Mat image) {
    cv::Mat imageGray, imageBlur;
    cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(imageGray, imageBlur, cv::Size(15, 15), 0, 0);
    ImagePreprocessor::m_grayImage = imageGray;
    ImagePreprocessor::m_blurredImage = imageBlur;
}

cv::Mat ImagePreprocessor::get_gray_image() {
    return ImagePreprocessor::m_grayImage;
}

cv::Mat ImagePreprocessor::get_blurred_image() {
    return ImagePreprocessor::m_blurredImage;
}
