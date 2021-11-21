#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

#include "../headers/EdgeDetector.hpp"

EdgeDetector::EdgeDetector(cv::Mat image) {
    cv::Mat imageCanny, imageEdge;
    cv::Canny(image, imageCanny, 25, 75);
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(imageCanny, imageEdge, kernel);
    EdgeDetector::m_imageEdge = imageEdge;
}

cv::Mat EdgeDetector::get_edge_image() {
    return EdgeDetector::m_imageEdge;
}

