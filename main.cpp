#include <opencv2/imgcodecs.hpp>
#include <pybind11/pybind11.h>
#include <iostream>
#include "headers/ImagePreprocessor.hpp"
#include "headers/EdgeDetector.hpp"
#include "headers/ContourDetector.hpp"
#include "headers/Image.hpp"
namespace py = pybind11;



PYBIND11_MODULE(document_warper, m) {
    py::class_<ImagePreprocessor>(m, "ImagePreprocessor")
        .def(py::init<Image>())
        .def("get_gray_image", &ImagePreprocessor::get_gray_image)
        .def("get_blurred_image", &ImagePreprocessor::get_blurred_image);

    py::class_<Image>(m, "Image")
        .def(py::init<std::string>())
        .def("get_matrix", &Image::get_matrix)
        .def("get_array", &Image::get_array);
}

// int main(int argc, char** argv) { 
//     std::cout << "Hello" << std::endl;
//     // Image image("test.jpg");
//     return 0; 
// }