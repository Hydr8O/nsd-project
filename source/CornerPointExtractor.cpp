#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

#include "../headers/CornerPointExtractor.hpp"
#include "../headers/Image.hpp"

CornerPointExtractor::CornerPointExtractor(Image image, Image imageEdge) {
    cv::Mat cornerPointImage = image.get_matrix().clone();
    cv::Mat imageWarp;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Point> cornerPoints;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(imageEdge.get_matrix(), contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cornerPoints = CornerPointExtractor::find_corner_points(contours);
    cornerPoints = CornerPointExtractor::reorder_points(cornerPoints);
    CornerPointExtractor::draw_corner_points(cornerPointImage, cornerPoints);
    CornerPointExtractor::m_cornerPointImage = Image(cornerPointImage);
    CornerPointExtractor::m_cornerPoints = cornerPoints;
}

CornerPointExtractor::CornerPointExtractor() {};

Image CornerPointExtractor::get_corner_point_image() {
    return CornerPointExtractor::m_cornerPointImage;
}

std::vector<cv::Point> CornerPointExtractor::get_corner_points() {
    return CornerPointExtractor::m_cornerPoints;
}

void CornerPointExtractor::draw_corner_points(cv::Mat image, std::vector<cv::Point> cornerPoints) {
    for (int i = 0; i < cornerPoints.size(); i++) {
        cv::circle(image, cornerPoints[i], 30, cv::Scalar(255, 0, 255), cv::FILLED);
    }
}

std::vector<cv::Point> CornerPointExtractor::find_corner_points(std::vector<std::vector<cv::Point>> contours) {
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

std::vector<cv::Point> CornerPointExtractor::reorder_points(std::vector<cv::Point> points) {
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
    


