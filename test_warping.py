import numpy as np
import json
from json import JSONEncoder
from pathlib import Path
from document_warper import DocumentWarper, Image, TextExtractor

TEST_DATA = Path('test_data')

class NumpyArrayEncoder(JSONEncoder):
    def default(self, obj):
        if isinstance(obj, np.ndarray):
            return obj.tolist()
        return JSONEncoder.default(self, obj)

def write_json(data, path):
    with open(path, 'w') as write_file:
        json.dump(data, write_file, cls=NumpyArrayEncoder)


def read_json(path):
    with open(path, 'r') as read_file:
        decodedArray = json.load(read_file)
    return np.asarray(decodedArray)

def test_grayscale():
    image = Image('test.jpg')
    document_warper = DocumentWarper(image)
    gray_image = document_warper.get_gray_image()
    test_gray_data = gray_image.get_array()
    gray_data = read_json(TEST_DATA / 'serialized_gray_image.json')
    assert np.array_equal(test_gray_data, gray_data) == True

def test_blur():
    image = Image('test.jpg')
    document_warper = DocumentWarper(image)
    gray_image = document_warper.get_blurred_image()
    test_blur_data = gray_image.get_array()
    blur_data = read_json(TEST_DATA / 'serialized_blur_image.json')
    assert np.array_equal(test_blur_data, blur_data) == True

def test_edge():
    image = Image('test.jpg')
    document_warper = DocumentWarper(image)
    gray_image = document_warper.get_edge_image()
    test_edge_data = gray_image.get_array()
    edge_data = read_json(TEST_DATA / 'serialized_edge_image.json')
    assert np.array_equal(test_edge_data, edge_data) == True

def test_corner_points():
    image = Image('test.jpg')
    document_warper = DocumentWarper(image)
    gray_image = document_warper.get_corner_point_image()
    test_corner_point_data = gray_image.get_array()
    corner_points_data = read_json(TEST_DATA / 'serialized_corner_point_image.json')
    assert np.array_equal(test_corner_point_data, corner_points_data) == True

def test_warp():
    image = Image('test.jpg')
    document_warper = DocumentWarper(image)
    gray_image = document_warper.get_warped_image()
    test_corner_point_data = gray_image.get_array()
    warp_data = read_json(TEST_DATA / 'serialized_warp_image.json')
    assert np.array_equal(test_corner_point_data, warp_data) == True

image = Image('test_hello.jpg')
warped_image = DocumentWarper(image).get_warped_image()
warped_image.write('warped_ocr.jpg')
extractor = TextExtractor()
extractor.extract_text(warped_image)
