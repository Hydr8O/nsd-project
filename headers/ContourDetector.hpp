#include <opencv2/core/mat.hpp>

#pragma once
class ContourDetector {
    public:
        ContourDetector(cv::Mat image, cv::Mat imageEdges);
        cv::Mat get_contours_image();
        std::vector<std::vector<cv::Point>> find_rectangular_contours(std::vector<std::vector<cv::Point>> contours);
        int find_largest_contour(std::vector<std::vector<cv::Point>> contours);
    private:
        cv::Mat m_imageContour;
};