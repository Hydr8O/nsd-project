#include <opencv2/core/mat.hpp>
#include <leptonica/allheaders.h>
#include <pybind11/numpy.h>
#include "../headers/Image.hpp"

namespace py = pybind11;

py::array convertMatToPyArray(cv::Mat);
Image warp_image(Image image, std::vector<cv::Point> cornerPoints);
Pix *matToPix(cv::Mat *mat);
cv::Mat binarise(cv::Mat image);