#include <tesseract/baseapi.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <leptonica/allheaders.h>
#include <iostream>
#include "../headers/TextExtractor.hpp"
#include "../headers/Image.hpp"
#include "../headers/utils.hpp"

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

void TextExtractor::extract_text(Image image) {
    float w = 1680.0f;
    float h = 2384.0f;
    cv::Rect cropArea(100, 100, w - 2 * 100, h - 2 * 100);
    cv::Mat matImage = image.get_matrix();
    cv::Mat binaryMatrix = binarise(matImage);
    binaryMatrix = binaryMatrix(cropArea);
    Pix *leptonica_image = matToPix(&binaryMatrix);
    TextExtractor::m_tesseractApi->SetImage(leptonica_image);
    char *outText = TextExtractor::m_tesseractApi->GetUTF8Text();
    printf("OCR output:\n%s", outText);
    delete [] outText;
    pixDestroy(&leptonica_image);
}