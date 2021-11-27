#include "../headers/ImagePreprocessor.hpp"
#include "../headers/DocumentWarper.hpp"
#include "../headers/EdgeDetector.hpp"
#include "../headers/CornerPointExtractor.hpp"
#include "../headers/Image.hpp"
#include "../headers/utils.hpp"

DocumentWarper::DocumentWarper(Image image) {
    DocumentWarper::m_preprocessor = ImagePreprocessor(image);
    DocumentWarper::m_edgeDetector = EdgeDetector(m_preprocessor.get_blurred_image());
    DocumentWarper::m_cornerPointExtractor = CornerPointExtractor(image, m_edgeDetector.get_edge_image());
    DocumentWarper::m_warpedImage = warp_image(image, m_cornerPointExtractor.get_corner_points());
}

Image DocumentWarper::get_gray_image() {
    return DocumentWarper::m_preprocessor.get_gray_image();
}

Image DocumentWarper::get_blurred_image() {
    return DocumentWarper::m_preprocessor.get_blurred_image();
}

Image DocumentWarper::get_edge_image() {
    return DocumentWarper::m_edgeDetector.get_edge_image();
}

Image DocumentWarper::get_corner_point_image() {
    return DocumentWarper::m_cornerPointExtractor.get_corner_point_image();
}

Image DocumentWarper::get_warped_image() {
    return DocumentWarper::m_warpedImage;
}
