SOURCE = source

.PHONY: clean

SOURCE_FILE_NAME=document_warper
TARGET = $(SOURCE_FILE_NAME)$(shell python3-config --extension-suffix)

TARGET: main.o ImagePreprocessor.o EdgeDetector.o ContourDetector.o utils.o Image.o
	g++ main.o ImagePreprocessor.o EdgeDetector.o ContourDetector.o utils.o Image.o -L./lib/opencv/lib -I./lib/opencv/include/opencv4 -I$(shell python3 -m pybind11 --includes) $(shell python3-config --includes) -shared -fPIC -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -o $(SOURCE_FILE_NAME)$(shell python3-config --extension-suffix) -O3

main.o: main.cpp
	g++ -c -fPIC main.cpp -I./lib/opencv/include/opencv4 -I$(shell python3 -m pybind11 --includes) $(shell python3-config --includes) -o main.o

ImagePreprocessor.o: ${SOURCE}/ImagePreprocessor.cpp
	g++ -c -fPIC ${SOURCE}/ImagePreprocessor.cpp -I./lib/opencv/include/opencv4 -I./lib/opencv/include/opencv4 -I$(shell python3 -m pybind11 --includes) $(shell python3-config --includes) -o ImagePreprocessor.o

EdgeDetector.o: ${SOURCE}/EdgeDetector.cpp
	g++ -c -fPIC ${SOURCE}/EdgeDetector.cpp -I./lib/opencv/include/opencv4 -I$(shell python3 -m pybind11 --includes) $(shell python3-config --includes) -o EdgeDetector.o

ContourDetector.o: ${SOURCE}/ContourDetector.cpp
	g++ -c -fPIC ${SOURCE}/ContourDetector.cpp -I./lib/opencv/include/opencv4 -I$(shell python3 -m pybind11 --includes) $(shell python3-config --includes) -o ContourDetector.o

utils.o: ${SOURCE}/utils.cpp
	g++ -c -fPIC ${SOURCE}/utils.cpp -I./lib/opencv/include/opencv4 -I./lib/opencv/include/opencv4 -I$(shell python3 -m pybind11 --includes) $(shell python3-config --includes) -o utils.o

Image.o: ${SOURCE}/Image.cpp
	g++ -c -fPIC ${SOURCE}/Image.cpp -I./lib/opencv/include/opencv4 -I./lib/opencv/include/opencv4 -I$(shell python3 -m pybind11 --includes) $(shell python3-config --includes) -o Image.o

clean:
	rm -rf *.o *.so