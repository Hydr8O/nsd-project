#include <opencv2/core/mat.hpp>
#include <pybind11/numpy.h>
#include "../headers/Image.hpp"

namespace py = pybind11;

py::array convertMatToPyArray(cv::Mat);
Image warp_image(Image image, std::vector<cv::Point> cornerPoints);