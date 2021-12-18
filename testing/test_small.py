import numpy as np
import json
from json import JSONEncoder
from pathlib import Path
import sys
sys.path.insert(0,"..")
from text_extractor import DocumentWarper, Image, TextExtractor
from testing_constants import CORNER_POINTS, IMAGE_TEST_FRACTION_END, IMAGE_TEST_FRACTION_START, TEST_DATA_PATH, TEST_TEXT

TEST_DATA_PATH = TEST_DATA_PATH / 'test_small'

def read_json(path):
    with open(path, 'r') as read_file:
        decodedArray = json.load(read_file)
    return np.asarray(decodedArray)

def test_grayscale_small():
    image = Image('test_warping.jpg')
    document_warper = DocumentWarper(image)
    gray_image = document_warper.get_gray_image()
    test_gray_data = gray_image.get_array()[IMAGE_TEST_FRACTION_START:IMAGE_TEST_FRACTION_END]
    gray_data = read_json(TEST_DATA_PATH / 'serialized_gray_image_small.json')
    assert np.array_equal(test_gray_data, gray_data) == True

def test_blur_small():
    image = Image('test_warping.jpg')
    document_warper = DocumentWarper(image)
    blur_image = document_warper.get_blurred_image()
    test_blur_data = blur_image.get_array()[IMAGE_TEST_FRACTION_START:IMAGE_TEST_FRACTION_END]
    blur_data = read_json(TEST_DATA_PATH / 'serialized_blur_image_small.json')
    assert np.array_equal(test_blur_data, blur_data) == True

def test_edge_small():
    image = Image('test_warping.jpg')
    document_warper = DocumentWarper(image)
    edge_image = document_warper.get_edge_image()
    test_edge_data = edge_image.get_array()[IMAGE_TEST_FRACTION_START:IMAGE_TEST_FRACTION_END]
    edge_data = read_json(TEST_DATA_PATH / 'serialized_edge_image_small.json')
    assert np.array_equal(test_edge_data, edge_data) == True

def test_corner_points():
    image = Image('test_warping.jpg')
    document_warper = DocumentWarper(image)
    corners = document_warper.get_corner_points()
    assert corners == CORNER_POINTS


def test_warp_small():
    image = Image('test_warping.jpg')
    document_warper = DocumentWarper(image)
    warp_image = document_warper.get_warped_image()
    test_corner_point_data = warp_image.get_array()[IMAGE_TEST_FRACTION_START:IMAGE_TEST_FRACTION_END]
    warp_data = read_json(TEST_DATA_PATH / 'serialized_warp_image_small.json')
    assert np.array_equal(test_corner_point_data, warp_data) == True

def test_ocr():
    image = Image('test_ocr.jpg')
    document_warper = DocumentWarper(image)
    warped_image = document_warper.get_warped_image()
    text_extractor = TextExtractor()
    text = text_extractor.extract_text(warped_image)
    assert text == TEST_TEXT