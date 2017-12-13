/**
 * Gets an Mat image and generates a new Mat with the hitogram image
 * @param  image The original image
 * @return       The histogram of the image
 */
Mat createHistogram(Mat image) {
    // Tamanho de cada pixel para o histograma
    int bins = 256;
    int histSize[] = {bins};
    // cria o espaço para o histograma
    float lranges[] = {0, 256};
    const float* ranges[] = {lranges};
    // cria a matriz para a criação do histograma
    Mat hist;
    int channels[] = {0};
    // cria a matriz para a vizualização do histograma
    int const hist_height = 256;
    Mat3b hist_image = Mat3b::zeros(hist_height, bins);
    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges, true, false);
    double max_val=0;
    minMaxLoc(hist, 0, &max_val);
    // exibição dos valores para cada pixel
    for(int b = 0; b < bins; b++) {
        float const binVal = hist.at<float>(b);
        int const height = cvRound(binVal*hist_height/max_val);
        line(hist_image, Point(b, hist_height-height), Point(b, hist_height), Scalar::all(255));
    }

    return hist_image;
}
