import numpy as np
import json
import sys
sys.path.insert(0,"..")
from text_extractor import DocumentWarper, Image, TextExtractor
from testing_constants import CORNER_POINTS, TEST_DATA_PATH, TEST_TEXT

def test_grayscale():
    image = Image('test_ocr.jpg')
    document_warper = DocumentWarper(image)
    gray_image = document_warper.get_gray_image()
    test_gray_data = gray_image.get_array()
    gray_data = np.load(TEST_DATA_PATH / 'gray.npy')
    assert np.array_equal(test_gray_data, gray_data) == True

def test_blur():
    image = Image('test_ocr.jpg')
    document_warper = DocumentWarper(image)
    gray_image = document_warper.get_blurred_image()
    test_blur_data = gray_image.get_array()
    blur_data = np.load(TEST_DATA_PATH / 'blur.npy')
    assert np.array_equal(test_blur_data, blur_data) == True

def test_edge():
    image = Image('test_ocr.jpg')
    document_warper = DocumentWarper(image)
    gray_image = document_warper.get_edge_image()
    test_edge_data = gray_image.get_array()
    edge_data = np.load(TEST_DATA_PATH / 'edge.npy')
    assert np.array_equal(test_edge_data, edge_data) == True


def test_warp():
    image = Image('test_ocr.jpg')
    document_warper = DocumentWarper(image)
    gray_image = document_warper.get_warped_image()
    test_corner_point_data = gray_image.get_array()
    warp_data = np.load(TEST_DATA_PATH / 'warp.npy')
    assert np.array_equal(test_corner_point_data, warp_data) == True

def test_corner_points():
    image = Image('test_ocr.jpg')
    document_warper = DocumentWarper(image)
    corners = document_warper.get_corner_points()
    assert corners == CORNER_POINTS

def test_ocr():
    image = Image('test_ocr.jpg')
    document_warper = DocumentWarper(image)
    warped_image = document_warper.get_warped_image()
    text_extractor = TextExtractor()
    text = text_extractor.extract_text(warped_image)
    assert text == TEST_TEXT