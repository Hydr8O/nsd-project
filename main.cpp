#include <opencv2/imgcodecs.hpp>
#include <pybind11/pybind11.h>
#include "headers/ImagePreprocessor.hpp"
#include "headers/EdgeDetector.hpp"
#include "headers/ContourDetector.hpp"
namespace py = pybind11;



PYBIND11_MODULE(document_warper, m) {
    py::class_<ImagePreprocessor>(m, "ImagePreprocessor")
        .def(py::init<std::string>())
        .def("get_gray_image", &ImagePreprocessor::get_gray_image)
        .def("get_blurred_image", &ImagePreprocessor::get_blurred_image);
}
// int main(int argc, char** argv) { 
//     cv::Mat image = cv::imread("./test.jpg"); 
//     ImagePreprocessor imagePreprocessor(image);
//     cv::Mat imageBlur = imagePreprocessor.get_blurred_image();
//     EdgeDetector edgeDetector(imageBlur);
//     cv::Mat imageEdge = edgeDetector.get_edge_image();
//     cv::imwrite("edge.jpeg", imageEdge);
//     ContourDetector contourDetector(image, imageEdge);
//     cv::Mat imageContours = contourDetector.get_contours_image();
//     cv::imwrite("output.jpeg", imageContours);
//     return 0; 
// }