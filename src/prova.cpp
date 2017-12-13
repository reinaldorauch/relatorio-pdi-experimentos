#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

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
 * Filters the image to
 * @param  image [description]
 * @return       [description]
 */
Mat twoDimFilter(Mat image) {
    Mat result, kernel = Mat::ones(5, 5, CV_32F) / 5.0 * 5.0;
    filter2D(image, result, -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
    return result;
}

/**
 * Show image in Mat in a named window from opencv
 * @param name  The name of the window
 * @param image The image to show
 */
void showImageOnWindow(std::string const& name, Mat image) {
    namedWindow(name, CV_WINDOW_AUTOSIZE);
    imshow(name, image);
}

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

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        cout << "Uso: prova [IMAGEM]" << endl;
        return 1;
    }

    // Pegando a imagem passada por argumento
    Mat imageGray = readImageGrayscale(argv[1]);

    if (!checkImageContents(imageGray)) {
        cout << "Erro: Não foi possível abrir a imagem cinza" << endl;
        return 1;
    }

    showImageOnWindow("Gray", imageGray);

    Mat imageColor = readImageColor(argv[1]);

    if (!checkImageContents(imageColor)) {
        cout << "Erro: Não foi possível abrir a imagem cor" << endl;
        return 1;
    }

    showImageOnWindow("Color", imageColor);

    showImageOnWindow("2dFilter", twoDimFilter(imageGray));

    showImageOnWindow("Color Histogram", createHistogram(imageColor));

    showImageOnWindow("Inverted image", invertImage(imageGray));

    showImageOnWindow("SaltPepper", addSaltPepperNoise(imageGray, 0.1, 0.1));

    waitKey(0);
    return 0;
}