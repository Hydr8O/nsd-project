import numpy as np

from document_warper import Image, ImagePreprocessor

image = Image("test.jpg")

preprocessor = ImagePreprocessor(image)
print(np.array_equal(preprocessor.get_gray_image().get_array(), preprocessor.get_gray_image().get_array()))