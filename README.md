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
  ```
  image = Image('image.jpg') 
  ```
- write(path) - write an image to path
  ```
  image = Image('image.jpg')
  image.write('image_copy.jpg')
  ```
