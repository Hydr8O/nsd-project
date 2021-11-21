#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

#include "../headers/ContourDetector.hpp"

ContourDetector::ContourDetector(cv::Mat image, cv::Mat imageEdge) {
    cv::Mat imageContour = image.clone();
    std::vector<std::vector<cv::Point>> contours;
    std::vector<std::vector<cv::Point>> rectangularContours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(imageEdge, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    rectangularContours = ContourDetector::find_rectangular_contours(contours);
    int largestContour = ContourDetector::find_largest_contour(rectangularContours);
    cv::drawContours(imageContour, rectangularContours, largestContour, cv::Scalar(255, 0, 255), 5);
    ContourDetector::m_imageContour = imageContour;
}

cv::Mat ContourDetector::get_contours_image() {
    return ContourDetector::m_imageContour;
}

std::vector<std::vector<cv::Point>> ContourDetector::find_rectangular_contours(std::vector<std::vector<cv::Point>> contours) {
    std::vector<std::vector<cv::Point>> rectangularContours;
    for (int i = 0; i < contours.size(); i++) {
        std::vector<cv::Point> currentPoly;
        float perimeter = cv::arcLength(contours[i], true);
        cv::approxPolyDP(contours[i], currentPoly, 0.02 * perimeter, true);
        if (currentPoly.size() == 4) {
            rectangularContours.push_back(contours[i]);
        }
    }
    return rectangularContours;
}

int ContourDetector::find_largest_contour(std::vector<std::vector<cv::Point>> contours) {
    float maxArea = 0;
    int largestContourIndex = 0;
     for (int i = 0; i < contours.size(); i++) {
        float currentArea = cv::contourArea(contours[i]);
        if (currentArea > maxArea) {
            maxArea = currentArea;
            largestContourIndex = i;
        }
    }
    return largestContourIndex;
}
    


