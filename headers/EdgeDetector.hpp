#include <opencv2/core/mat.hpp>
#include "../headers/Image.hpp"

#pragma once
class EdgeDetector {
    public:
        EdgeDetector(Image image);
        EdgeDetector();
        Image get_edge_image();
    private:
        Image m_imageEdge;
};