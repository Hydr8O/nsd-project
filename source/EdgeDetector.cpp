#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

#include "../headers/EdgeDetector.hpp"
#include "../headers/Image.hpp"

EdgeDetector::EdgeDetector(Image image) {
    cv::Mat imageCanny, imageEdge;
    cv::Canny(image.get_matrix(), imageCanny, 25, 75);
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
    cv::dilate(imageCanny, imageEdge, kernel);
    EdgeDetector::m_imageEdge = Image(imageEdge);
}

EdgeDetector::EdgeDetector() {};

Image EdgeDetector::get_edge_image() {
    return EdgeDetector::m_imageEdge;
}

