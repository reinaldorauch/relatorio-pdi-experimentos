/**
 * Reads an image file in color mode
 * @param  path The path of the image file
 * @return      The Mat with the image data
 */
Mat readImageColor(char const path[]) {
    return imread(path, CV_LOAD_IMAGE_COLOR);
}

/**
 * Reads an image file in grayscale mode
 * @param  path The path of the image file
 * @return      The Mat with the image data
 */
Mat readImageGrayscale(char const path[]) {
    return imread(path, CV_LOAD_IMAGE_GRAYSCALE);
}

/**
 * Checks if the Mat image has data
 * @param  image The image mat
 * @return       Boolean if the image has data or not
 */
bool checkImageContents(Mat image) {
    return !!image.data;
}

/**
 * Filtrates the image to enhance the darker points of the image
 * @param  image Original image
 * @return       The filtered image
 */
Mat twoDimFilter(Mat image) {
    Mat result, kernel = Mat::ones(5, 5, CV_32F) / 5.0 * 5.0;
    filter2D(image, result, -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
    return result;
}