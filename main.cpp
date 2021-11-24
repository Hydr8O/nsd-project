#include <opencv2/imgcodecs.hpp>
#include "headers/ImagePreprocessor.hpp"
#include "headers/EdgeDetector.hpp"
#include "headers/ContourDetector.hpp"

int main(int argc, char** argv) { 
    cv::Mat image = cv::imread("./test.jpg"); 
    ImagePreprocessor imagePreprocessor(image);
    cv::Mat imageBlur = imagePreprocessor.get_blurred_image();
    EdgeDetector edgeDetector(imageBlur);
    cv::Mat imageEdge = edgeDetector.get_edge_image();
    cv::imwrite("edge.jpeg", imageEdge);
    ContourDetector contourDetector(image, imageEdge);
    cv::Mat imageContours = contourDetector.get_contours_image();
    cv::imwrite("output.jpeg", imageContours);
    return 0; 
}