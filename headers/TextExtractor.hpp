#include <tesseract/baseapi.h>
#include <opencv2/core/mat.hpp>
#include <leptonica/allheaders.h>
#include "../headers/Image.hpp"

#pragma once
class TextExtractor {
    public:
        TextExtractor();
        ~TextExtractor();
        void extract_text(Image image);
    private:
        tesseract::TessBaseAPI *m_tesseractApi;
};