#include <opencv2/core/mat.hpp>

#pragma once
class ContourDetector {
    public:
        ContourDetector(cv::Mat image, cv::Mat imageEdges);
        cv::Mat get_contours_image();
        std::vector<cv::Point> find_corner_points(std::vector<std::vector<cv::Point>> contours);
        int find_largest_contour(std::vector<std::vector<cv::Point>> contours);
        std::vector<cv::Point> reorder_points(std::vector<cv::Point> points);
        void draw_corner_points(cv::Mat image, std::vector<cv::Point> cornerPoints);
    private:
        cv::Mat m_imageContour;
};