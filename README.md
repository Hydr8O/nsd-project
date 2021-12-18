# Text Extractor

## Installation

Installation is done by running the script build.sh
```
chmod u+x build.sh
./build.sh
```

## API

### Image
- constructor Image(path_to_image) - reads an image from path_to_image
  ```python
  image = Image('image.jpg') 
  ```
- write(path) - write an image to path
  ```python
  image.write('image_copy.jpg')
  ```
- get_array() - returns an image in a 1D numpy array
  ```python
  numpy_array = image.get_array()
  ```
  
### ImagePreprocessor
- constructor ImagePreprocessor(image)
  ```python
  image = Image('image.jpg')
  preprocessor = ImagePreprocessor(image) 
  ```
- get_gray_image() - returns grayscale image
  ```python
  gray_image = preprocessor.get_gray_image()
  ```
- get_blurred_image() - returns image blurred with Gaussian kernel
  ```python
  blurred_image = preprocessor.get_blurred_image()
  ```
  
### EdgeDetector
- constructor EdgeDetector(image). Image has to be preprocessed by ImagePreprocessor first to work properly.
  ```python
  image = Image('image.jpg')
  preprocessor = ImagePreprocessor(image)
  blurred_image = preprocessor.get_blurred_image()
  edge_detector = EdgeDetector(blurred_image) 
  ```
- get_edge_image() - returns edge image. 
  ```python
  edge_image = edge_detector.get_edge_image()
  ```
 
### CornerPointExtractor
- constructor CornerPointExtractor(image, edge_image)
  ```python
  image = Image('image.jpg')
  edge_image = edge_detector.get_edge_image()
  corner_extractor = CornerPointExtractor(edge_image)
  ```
- get_corner_point_image() - returns image with drawn corner points.
  ```python
  corner_image = corner_extractor.get_corner_point_image()
  ```
  
### DocumentWarper
Implements the whole pipeline. Also has get_gray_image(), get_blurred_image(), get_edge_image(), get_corner_point_image() methods.
- constructor DocumentWarper(image)
  ```python
  image = Image('image.jpg')
  warper = DocumentWarper(image)
  ```
- get_warped_image() - returns warped image with top-down view.
  ```python
  warped_image = warper.get_warped_image()
  ``` 
 
