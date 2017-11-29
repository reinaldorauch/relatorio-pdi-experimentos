#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Uso: escala-cinza [IMAGEM]" << endl;
    }

    Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);

    if (!image.data) {
        cout << "Erro: Não foi possível abrir a imagem" << endl;
        return 1;
    }

    namedWindow("entrada", WINDOW_AUTOSIZE);
    imshow("entrada", image);

    Mat imagePlanoBits = image;

    int i, j, cinza;
    int r = image.rows;
    int c = image.cols;

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            cinza = imagePlanoBits.at<uchar>(i,j);

            if (cinza < 200) {
                imagePlanoBits.at<uchar>(i,j)= 200;
            }

            imagePlanoBits.at<uchar>(i,j) = cinza;
        }
    }

    imshow("imagePlanoBits", imagePlanoBits);

    waitKey(0);

    return 0;
}