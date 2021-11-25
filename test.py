import numpy as np

from document_warper import ImagePreprocessor

preprocessor = ImagePreprocessor("test.jpg")
print(np.array_equal(preprocessor.get_gray_image(), preprocessor.get_gray_image()))