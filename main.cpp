#include <opencv2/imgcodecs.hpp>
#include "headers/ImagePreprocessor.hpp"
#include "headers/EdgeDetector.hpp"
#include "headers/ContourDetector.hpp"

int main(int argc, char** argv) { 
    cv::Mat image = cv::imread("./download.jpeg"); 
    ImagePreprocessor imagePreprocessor(image);
    cv::Mat imageBlur = imagePreprocessor.get_blurred_image();
    EdgeDetector edgeDetector(imageBlur);
    cv::Mat imageEdge = edgeDetector.get_edge_image();
    ContourDetector contourDetector(image, imageEdge);
    cv::Mat imageContours = contourDetector.get_contours_image();
    cv::imwrite("a.jpeg", imageContours);
    return 0; 
}