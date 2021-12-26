SOURCE = source

.PHONY: clean, test

SOURCE_FILE_NAME=text_extractor
TESSERACT_INCLUDES=-I./lib/leptonica/include -I./lib/tesseract/include
LIBS=-L./lib/opencv/lib -L./lib/tesseract/lib -L./lib/leptonica/lib
SHARED=-lopencv_core -lopencv_imgcodecs -lopencv_imgproc -ltesseract -llept
PYBIND_INCLUDEDS=-I$(shell python3 -m pybind11 --includes) $(shell python3-config --includes)
TARGET=$(SOURCE_FILE_NAME)$(shell python3-config --extension-suffix)

TARGET: main.o ImagePreprocessor.o EdgeDetector.o CornerPointExtractor.o utils.o Image.o DocumentWarper.o TextExtractor.o
	g++ main.o ImagePreprocessor.o EdgeDetector.o CornerPointExtractor.o utils.o Image.o DocumentWarper.o TextExtractor.o ${LIBS} -I./lib/opencv/include/opencv4 ${PYBIND_INCLUDEDS} -shared -fPIC ${SHARED} -o $(SOURCE_FILE_NAME)$(shell python3-config --extension-suffix) -O3

main.o: main.cpp
	g++ -c -fPIC main.cpp -I./lib/opencv/include/opencv4 ${PYBIND_INCLUDEDS} ${TESSERACT_INCLUDES} -o main.o

ImagePreprocessor.o: ${SOURCE}/ImagePreprocessor.cpp
	g++ -c -fPIC ${SOURCE}/ImagePreprocessor.cpp -I./lib/opencv/include/opencv4 ${PYBIND_INCLUDEDS} ${TESSERACT_INCLUDES} -o ImagePreprocessor.o

EdgeDetector.o: ${SOURCE}/EdgeDetector.cpp
	g++ -c -fPIC ${SOURCE}/EdgeDetector.cpp -I./lib/opencv/include/opencv4 ${PYBIND_INCLUDEDS} -o EdgeDetector.o

CornerPointExtractor.o: ${SOURCE}/CornerPointExtractor.cpp
	g++ -c -fPIC ${SOURCE}/CornerPointExtractor.cpp -I./lib/opencv/include/opencv4 ${PYBIND_INCLUDEDS} -o CornerPointExtractor.o

DocumentWarper.o: ${SOURCE}/DocumentWarper.cpp
	g++ -c -fPIC ${SOURCE}/DocumentWarper.cpp -I./lib/opencv/include/opencv4 ${PYBIND_INCLUDEDS} ${TESSERACT_INCLUDES} -o DocumentWarper.o

TextExtractor.o: ${SOURCE}/TextExtractor.cpp
	g++ -c -fPIC ${SOURCE}/TextExtractor.cpp -I./lib/opencv/include/opencv4 ${TESSERACT_INCLUDES} ${PYBIND_INCLUDEDS} -o TextExtractor.o

utils.o: ${SOURCE}/utils.cpp
	g++ -c -fPIC ${SOURCE}/utils.cpp -I./lib/opencv/include/opencv4 ${PYBIND_INCLUDEDS} ${TESSERACT_INCLUDES} -o utils.o

Image.o: ${SOURCE}/Image.cpp
	g++ -c -fPIC ${SOURCE}/Image.cpp -I./lib/opencv/include/opencv4 ${PYBIND_INCLUDEDS} ${TESSERACT_INCLUDES} -o Image.o

clean:
	rm -rf *.o *.so *.jpg

test:
	cd testing && pytest . && cd -