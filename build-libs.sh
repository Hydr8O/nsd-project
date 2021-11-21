# Create source directories and built lib directories
mkdir lib-sources
mkdir lib
mkdir lib/leptonica
mkdir lib/tesseract
mkdir lib/opencv

cd lib-sources

# Set path for built directories
LIB_PATH=$(pwd)/../lib

# Install required packages
sudo apt install autoconf libtool libjpeg-dev libpng-dev libtiff-dev -y

# Build Leptonica
git clone https://github.com/DanBloomberg/leptonica
cd leptonica
autoreconf -vi
./configure --prefix $LIB_PATH/leptonica
make
make -j4 install
cd ..

# Build Tesseract
git clone https://github.com/tesseract-ocr/tesseract
cd tesseract
./autogen.sh
export LD_LIBRARY_PATH=$LIB_PATH/leptonica/lib
export LIBLEPT_HEADERSDIR=$LIB_PATH/leptonica/include/leptonica
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$LIB_PATH/leptonica/lib/pkgconfig
LIBLEPT_HEADERSDIR=$LIB_PATH/leptonica/include/leptonica ./configure \
  --prefix=$LIB_PATH/tesseract --with-extra-libraries=$LIB_PATH/leptonica/lib
make
make -j4 install
cd ..

# Build OpenCV
git clone https://github.com/opencv/opencv.git
cd opencv
mkdir build
cd build
rm ../CMakeCache.txt
cmake -D CMAKE_INSTALL_PREFIX=$LIB_PATH/opencv -D WITH_GTK=OFF -D WITH_QT=OFF -D WITH_CUDA=OFF \
 -D ENABLE_AVX=OFF -D WITH_OPENGL=OFF -D WITH_OPENCL=OFF -D WITH_IPP=OFF \
 -D WITH_TBB=ON -D BUILD_TBB=ON -D WITH_EIGEN=OFF -D WITH_V4L=OFF -D WITH_VTK=OFF \
 -D BUILD_TESTS=OFF -D BUILD_PERF_TESTS=OFF -D OPENCV_GENERATE_PKGCONFIG=ON \
 -D WITH_PROTOBUF=OFF -D OPENCV_DNN_OPENCL=OFF -D BUILD_PROTOBUF=OFF \
 -D CMAKE_BUILD_TYPE=RELEASE ..
make -j4
make install