#include <tesseract/baseapi.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <leptonica/allheaders.h>
#include <iostream>
#include "../headers/TextExtractor.hpp"
#include "../headers/Image.hpp"
#include "../headers/utils.hpp"

float const FINAL_WIDTH = 1680.0f;
float const FINAL_HEIGHT = 2384.0f;

TextExtractor::TextExtractor() {
    TextExtractor::m_tesseractApi = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (TextExtractor::m_tesseractApi->Init(NULL, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }
}

TextExtractor::~TextExtractor() {
    TextExtractor::m_tesseractApi->End();
    delete TextExtractor::m_tesseractApi;
}

std::string TextExtractor::extract_text(Image image) {
    float w = FINAL_WIDTH;
    float h = FINAL_HEIGHT;
    cv::Rect cropArea(100, 100, w - 2 * 100, h - 2 * 100);
    cv::Mat matImage = image.get_matrix();
    cv::Mat binaryMatrix = binarise(matImage);
    binaryMatrix = binaryMatrix(cropArea);
    Pix *leptonica_image = matToPix(&binaryMatrix);
    TextExtractor::m_tesseractApi->SetImage(leptonica_image);
    char *outText = TextExtractor::m_tesseractApi->GetUTF8Text();
    std::string result = outText;
    delete [] outText;
    pixDestroy(&leptonica_image);
    return result;
}