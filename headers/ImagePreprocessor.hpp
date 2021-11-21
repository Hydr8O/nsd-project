#include <opencv2/core/mat.hpp>

#pragma once
class ImagePreprocessor {
    public:
        ImagePreprocessor(cv::Mat image);
        cv::Mat get_gray_image();
        cv::Mat get_blurred_image();
    private:
        cv::Mat m_grayImage;
        cv::Mat m_blurredImage;
};