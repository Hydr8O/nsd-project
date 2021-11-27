#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <pybind11/numpy.h>
#include "../headers/utils.hpp"
#include "../headers/Image.hpp"

namespace py = pybind11;

py::array convertMatToPyArray(cv::Mat matrix) {
    cv::Mat flat = matrix.reshape(1, matrix.total()*matrix.channels());
    std::vector<uchar> vec = matrix.isContinuous() ? flat : flat.clone();
    return py::array(vec.size(), vec.data());
}

Image warp_image(Image image, std::vector<cv::Point> cornerPoints) {
    cv::Mat warpedImage = image.get_matrix().clone();
    cv::Point2f src[4] = {cornerPoints[0], cornerPoints[1], cornerPoints[2], cornerPoints[3]};
    float w = 1680.0f;
    float h = 2384.0f;
    cv::Point2f dst[4] = {{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h}};
    cv::Mat warpMatrix = cv::getPerspectiveTransform(src, dst);
    cv::warpPerspective(image.get_matrix(), warpedImage, warpMatrix, cv::Point(w, h));
    return warpedImage;
}