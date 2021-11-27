#include "./ImagePreprocessor.hpp"
#include "./EdgeDetector.hpp"
#include "./CornerPointExtractor.hpp"
#include "./Image.hpp"

class DocumentWarper {
    public:
        DocumentWarper(Image image);
        Image get_gray_image();
        Image get_blurred_image();
        Image get_edge_image();
        Image get_corner_point_image();
        Image get_warped_image();


    private:
        ImagePreprocessor m_preprocessor;
        EdgeDetector m_edgeDetector;
        CornerPointExtractor m_cornerPointExtractor;
        Image m_warpedImage;
};