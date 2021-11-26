#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

#include "../headers/ContourDetector.hpp"
#include "../headers/Image.hpp"

ContourDetector::ContourDetector(Image image, Image imageEdge) {
    cv::Mat imageContour = image.get_matrix().clone();
    cv::Mat imageWarp;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Point> cornerPoints;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(imageEdge.get_matrix(), contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cornerPoints = ContourDetector::find_corner_points(contours);
    cornerPoints = ContourDetector::reorder_points(cornerPoints);
    cv::Point2f src[4] = {cornerPoints[0], cornerPoints[1], cornerPoints[2], cornerPoints[3]};
    float w = 1680.0f;
    float h = 2384.0f;
    cv::Point2f dst[4] = {{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h}};
    cv::Mat warpMatrix = cv::getPerspectiveTransform(src, dst);
    cv::warpPerspective(image.get_matrix(), imageWarp, warpMatrix, cv::Point(w, h));
    ContourDetector::draw_corner_points(imageContour, cornerPoints);
    ContourDetector::m_imageContour = Image(imageWarp);
}

Image ContourDetector::get_contours_image() {
    return ContourDetector::m_imageContour;
}

void ContourDetector::draw_corner_points(cv::Mat image, std::vector<cv::Point> cornerPoints) {
    for (int i = 0; i < cornerPoints.size(); i++) {
        cv::circle(image, cornerPoints[i], 30, cv::Scalar(255, 0, 255), cv::FILLED);
    }
}

std::vector<cv::Point> ContourDetector::find_corner_points(std::vector<std::vector<cv::Point>> contours) {
    std::vector<cv::Point> cornerPoints;
    float maxArea = 0;
    for (int i = 0; i < contours.size(); i++) {
        std::vector<cv::Point> currentPoly;
        float perimeter = cv::arcLength(contours[i], true);
        float area = cv::contourArea(contours[i]);
        cv::approxPolyDP(contours[i], currentPoly, 0.02 * perimeter, true);
        if (currentPoly.size() == 4 && area > maxArea) {
            cornerPoints = {currentPoly[0], currentPoly[1], currentPoly[2], currentPoly[3]};
            maxArea = area;
        }
    }
    return cornerPoints;
}

std::vector<cv::Point> ContourDetector::reorder_points(std::vector<cv::Point> points) {
    std::vector<cv::Point> reorderedPoints(points.size());
    std::vector<float> tempPointsSum(points.size()), tempPointsSub(points.size());

    for (int i = 0; i < points.size(); i++) {
        tempPointsSum[i] = points[i].x + points[i].y;
        tempPointsSub[i] = points[i].x - points[i].y;
    }
    
    reorderedPoints[0] = points[std::min_element(tempPointsSum.begin(), tempPointsSum.end()) - tempPointsSum.begin()];
    reorderedPoints[1] = points[std::max_element(tempPointsSub.begin(), tempPointsSub.end()) - tempPointsSub.begin()];
    reorderedPoints[2] = points[std::min_element(tempPointsSub.begin(), tempPointsSub.end()) - tempPointsSub.begin()];
    reorderedPoints[3] = points[std::max_element(tempPointsSum.begin(), tempPointsSum.end()) - tempPointsSum.begin()];

    return reorderedPoints;
}
    


