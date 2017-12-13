/**
 * Inverts the image to get a negative
 * @param  image The original image
 * @return       The negative of the image
 */
Mat invertImage(Mat image) {
    Mat newImage = image.clone();
    Vec3b p;

    for (int i = 0; i < newImage.rows; ++i)
    {
        for (int j = 0; j < newImage.cols; ++j)
        {
            p = newImage.at<Vec3b>(i, j);
            newImage.at<Vec3b>(i, j)[0] = 255 - p[0];
            newImage.at<Vec3b>(i, j)[1] = 255 - p[1];
            newImage.at<Vec3b>(i, j)[2] = 255 - p[2];
        }
    }

    return newImage;
}