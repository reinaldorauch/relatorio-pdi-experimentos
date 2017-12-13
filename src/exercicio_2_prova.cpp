/**
 * Adiciona ruido de sal e pimenta na imagem
 * @param  image Imagem original
 * @param  pa
 * @param  pb
 * @return       A imagem com ruido sal e pimenta
 */
Mat addSaltPepperNoise(Mat image, float pa, float pb) {
    Mat newImage = image.clone();
    RNG rng;
    int amount1 = newImage.rows * newImage.cols * pa;
    int amount2 = newImage.rows * newImage.cols * pb;

    for(int counter = 0; counter < amount1; ++counter) {
        newImage.at<uchar>(rng.uniform(0,newImage.rows), rng.uniform(0, newImage.cols)) = 0;
    }

    for (int counter = 0; counter < amount2; ++counter) {
        newImage.at<uchar>(rng.uniform(0,newImage.rows), rng.uniform(0,newImage.cols)) = 255;
    }

    return newImage;
}