#include <opencv2/core/mat.hpp>

#pragma once
class EdgeDetector {
    public:
        EdgeDetector(cv::Mat image);
        cv::Mat get_edge_image();
    private:
        cv::Mat m_imageEdge;
};