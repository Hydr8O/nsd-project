import numpy as np

from document_warper import DocumentWarper, Image

image = Image("test.jpg")

document_warper = DocumentWarper(image)

gray_image = document_warper.get_gray_image()
warped_image = document_warper.get_warped_image()
warped_image.write('warped.jpg')